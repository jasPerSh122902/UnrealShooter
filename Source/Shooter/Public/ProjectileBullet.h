// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Shooter/Public/Bullet.h>
#include "ProjectileBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class ASelfMadePlayer;

UCLASS()
class SHOOTER_API AProjectileBullet : public ABullet 
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		USphereComponent* m_Collision;
		UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* meshA;
		UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* m_Movement;
		UPROPERTY(EditAnywhere)
		FVector bounceOff;
public:	
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
	// Sets default values for this actor's properties
	AProjectileBullet();
	virtual void Tick(float DeltaTime) override;
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
		virtual void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// <summary>
	/// Makes the collision
	/// </summary>
	void MakeCollision();
	/// <summary>
	/// Makes the movement
	/// </summary>
	void MakeMovement();
	/// <summary>
	/// Makes the Mesh
	/// </summary>
	void MakeMesh();

};
