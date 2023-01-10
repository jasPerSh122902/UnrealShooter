// Fill out your copyright notice in the Description page of Project Settings.

#include "RayCastBullet.h"
#include <Engine/Engine.h>
// Sets default values
ARayCastBullet::ARayCastBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARayCastBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ARayCastBullet::DoTrace(FHitResult* Hit, FCollisionQueryParams* params)
{
	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	FVector Start = Loc;

	FVector End = Loc + (Rot.Vector() * MaxDistance);
	params->bTraceComplex = true;
	params->bReturnPhysicalMaterial = false;

	bool Traced = GetWorld()->LineTraceSingleByChannel
	(
		*Hit, Start, End, ECC_PhysicsBody, *params
	);
	return Traced;
}


void ARayCastBullet::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ARayCastBullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ARayCastBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitCall(ForceInit);
	FCollisionQueryParams ParamsCall = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
	DoTrace(&HitCall, &ParamsCall);
}

