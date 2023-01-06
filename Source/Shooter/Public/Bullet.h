// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class ASelfMadePlayer;

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()



	UPROPERTY(EditAnywhere)
		ASelfMadePlayer* m_Owner;
public:
	// Sets default values for this actor's properties
	ABullet();
	void BeginPlay();
	void Tick(float DeltaTime);
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
		virtual void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// Gets the owner
	/// </summary>
	/// <returns>the owner</returns>
	ASelfMadePlayer* getOwner() { return m_Owner; }
	void setOwner(ASelfMadePlayer* owner) { m_Owner = owner; }

private:
	FVector startLocation;
	FVector endLocation;
};

