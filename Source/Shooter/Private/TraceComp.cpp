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
void UTraceComp::DoTrace(FVector location, FRotator rotation,UWorld* currentWorld)
{
	FVector tempLocation = location;
	FRotator temprotation = rotation;
	FVector tempEndLocation;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Trace");
	tempLocation = FVector(tempLocation.X + (temprotation.Vector().X * 100), tempLocation.Y + (temprotation.Vector().Y * 100), tempLocation.Z + (temprotation.Vector().Z * 100));
	// the start will increate by the rotation
	tempEndLocation = tempLocation + temprotation.Vector();
	// Makes a hit result
	FHitResult hit;
	// If the world return true
	if (currentWorld != NULL)
	{
		// Makes a trace 
		// retruns true if the trace hit
		// else return false
		bool Traced = currentWorld->LineTraceSingleByChannel(hit, tempLocation, tempEndLocation, ECC_PhysicsBody, FCollisionQueryParams(), FCollisionResponseParams());
		// Is the size of the bullet that i spawn
		GetTraceBullet(100, FColor::Orange, false, 1.5f, 0, 5.0f,currentWorld,tempLocation,tempEndLocation,temprotation);
		
		/// <summary>
		/// Is the on collision call
		/// </summary>
		if (Traced && hit.GetActor())
		{
			if (hit.GetActor()->GetFName() == "SelfMadePlayer_0")
			{
				return;
			}
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

void UTraceComp::GetTraceBullet(float multiplyLength,FColor color, bool linePresist,float lifeTime, int proity, float thickness, UWorld* currentWorld, FVector location, FVector endLocation, FRotator rotation)
{
	// Prinst the message to the log
	UE_LOG(LogTemp, Warning, TEXT("Sending ray Trace"))
	// Is the lines end
	endLocation = location + rotation.Vector() * multiplyLength;
	// Draws the line at the current location to the end
	DrawDebugLine(currentWorld, location, endLocation, color,false,lifeTime, proity, thickness);
}