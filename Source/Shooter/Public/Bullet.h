// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();
	 void BeginPlay();
	 void Tick(float DeltaTime);
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
		 void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		 void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	FVector startLocation;
	FVector endLocation;
};

