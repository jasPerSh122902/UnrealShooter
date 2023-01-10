// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RayCastBullet.generated.h"

UCLASS()
class SHOOTER_API ARayCastBullet : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		FVector MaxDistance;

public:	
	// Sets default values for this actor's properties
	ARayCastBullet();
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
	void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool DoTrace(FHitResult* Hit, FCollisionQueryParams* params);
};
