// Fill out your copyright notice in the Description page of Project Settings.
#include "TraceComp.h"
#include <Engine/Engine.h>
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
// Sets default values for this component's properties
UTraceComp::UTraceComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTraceComp::BeginPlay()
{
	Super::BeginPlay();
	MyCharactor = Cast<ACharacter>(GetOwner());
}

void UTraceComp::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FCollisionQueryParams ParamsCall = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
	DoTrace(OtherActor->ReceiveHit(OverlappedComp,OtherActor,OtherComp,false,OtherActor->GetActorLocation(),SweepResult.Normal,lineStart,SweepResult), &ParamsCall);
}

void UTraceComp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

bool UTraceComp::DoTrace(FHitResult* Hit, FCollisionQueryParams* params)
{
	if (getIfClicked() == true)
	{
		if (Hit->Actor.Get()->GetFName() != "SelfMadePlayer_0")
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Trace");
			lineStart = GetOwner()->GetActorLocation();
			rotation = GetOwner()->GetActorRotation();

			LineEnd = lineStart + (rotation.Vector() * EndMultiply);
			params->bTraceComplex = true;
			params->bReturnPhysicalMaterial = false;

			bool Traced = GetWorld()->LineTraceSingleByChannel
			(
				*Hit, lineStart, LineEnd, ECC_PhysicsBody, *params
			);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Traced value" + Traced);
			GetTraceBullet(100, FColor::Orange, false, 1.5f, 0, 5.0f);
			setClicked(false);
			return Traced;
		}
	}
}

// Called every frame
void UTraceComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UTraceComp::GetTraceBullet(float multiplyLength,FColor color, bool linePresist,float lifeTime, int proity, float thickness)
{
	
	// Prinst the message to the log
	UE_LOG(LogTemp, Warning, TEXT("Sending ray Trace"))
	// Get the player controlls and get the location and rotation of the player
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(OUT lineStart,OUT rotation);
	// Is the lines end
	LineEnd = lineStart + rotation.Vector() * multiplyLength;

	// Draws the line at the current location to the end
	DrawDebugLine(GetWorld(),lineStart,LineEnd, color,false,lifeTime, proity, thickness);
}