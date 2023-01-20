// Fill out your copyright notice in the Description page of Project Settings.
#include "TraceComp.h"
#include <Engine/Engine.h>
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
// Sets default values for this component's properties
UTraceComp::UTraceComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTraceComp::BeginPlay() {Super::BeginPlay();}
void UTraceComp::DoTrace()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Trace");
	// set the start line
	LineStart = GetOwner()->GetActorLocation();
	// set the rotation equal to the components rotation
	Rotation = GetOwner()->FindComponentByClass<UCameraComponent>()->GetComponentRotation();
	// the start will increate by the rotation
	LineStart = FVector(LineStart.X + (Rotation.Vector().X * 100), LineStart.Y + (Rotation.Vector().Y * 100), LineStart.Z + (Rotation.Vector().Z * 100));
	LineEnd = LineStart + (Rotation.Vector() * EndMultiply);
	// Makes a hit result
	FHitResult hit;
	// If the world return true
	if (GetWorld())
	{
		// Makes a trace 
		// retruns true if the trace hit
		// else return false
		bool Traced = GetWorld()->LineTraceSingleByChannel(hit, LineStart , LineEnd, ECC_PhysicsBody, FCollisionQueryParams(), FCollisionResponseParams());
		// Is the size of the bullet that i spawn
		GetTraceBullet(100, FColor::Orange, false, 1.5f, 0, 5.0f);
		
		/// <summary>
		/// Is the on collision call
		/// </summary>
		if (Traced && hit.GetActor())
		{
			// Make a Frotator
			FRotator hitrotation;
			// Set the rotator 
			hitrotation.Vector().Set(30000.f, 30.f, 300.f);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Traced value" + hit.GetActor()->GetFName().ToString());
			// Makes the hit actor rotate
			hit.GetActor()->SetActorRelativeRotation(hitrotation * 9, false, &hit,ETeleportType::ResetPhysics);
		}
	}
}

// Called every frame
void UTraceComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {Super::TickComponent(DeltaTime, TickType, ThisTickFunction);}

void UTraceComp::GetTraceBullet(float multiplyLength,FColor color, bool linePresist,float lifeTime, int proity, float thickness)
{
	// Prinst the message to the log
	UE_LOG(LogTemp, Warning, TEXT("Sending ray Trace"))
	// Is the lines end
	LineEnd = LineStart + Rotation.Vector() * multiplyLength;
	// Draws the line at the current location to the end
	DrawDebugLine(GetWorld(),LineStart,LineEnd, color,false,lifeTime, proity, thickness);
}