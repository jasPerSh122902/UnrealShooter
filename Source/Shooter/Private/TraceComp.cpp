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
	//Made temp varables 
	FVector tempLocation = location;
	FRotator tempRotation = rotation;
	FVector tempEndLocation;
	const FVector temp;
	// adding the location and the rotation together
	tempLocation = FVector(tempLocation.X + (tempRotation.Vector().X * 100), tempLocation.Y + (tempRotation.Vector().Y * 100), tempLocation.Z + (tempRotation.Vector().Z * 100));
	// the start will increate by; the rotation
	// will make the ray be at a agle around the center of the screen
	 //tempEndLocation = tempLocation * (tempRotation.Vector() * 100000);
	tempEndLocation = tempLocation + (tempRotation.Vector() * 100000);
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
		GetTraceBullet(100, FColor::Orange, false, 1.5f, 0, 5.0f,currentWorld,tempLocation,tempEndLocation,tempRotation);
		
		/// <summary>
		/// Is the on collision call
		/// </summary>
		if (Traced && hit.GetActor())
		{
			// if the actor hit is player
			if (hit.GetActor()->GetFName() == "SelfMadePlayer_0")
				return;//return
			
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
	// Draws the line at the current location to the end
	DrawDebugLine(currentWorld, location, endLocation, color,false,lifeTime, proity, thickness);
}