// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ABullet();
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* meshA;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* m_Collision;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* m_Movement;

public:	
	void BeginPlay();
	void Tick(float DeltaTime);
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
	void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/// <summary>
	/// Returns the collider component
	/// </summary>
	/// <returns>m_Collision</returns>
	USphereComponent* getColliderComponent() const { return m_Collision; }
	/// <summary>
	/// Returns the movement component
	/// </summary>
	/// <returns>m_Movement</returns>
	UProjectileMovementComponent* getMovementComponent() const { return m_Movement; }

private:
	FVector startLocation;
	FVector endLocation;

protected:
	void MakeCollision();
 	void MakeMovement();
	void MakeMesh();
};
