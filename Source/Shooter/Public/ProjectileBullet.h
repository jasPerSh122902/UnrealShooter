// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOTER_API AProjectileBullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Collider)
		USphereComponent* Collision;
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* MeshA;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* Movement;
	UPROPERTY(EditAnywhere, Category = Bounce)
		FVector BounceOff = FVector(0, 10, 10);
;
	FVector startLocation;
	
public:	
	/// <summary>
	/// Returns the collider component
	/// </summary>
	/// <returns>m_Collision</returns>
	USphereComponent* getColliderComponent() const { return Collision; }
	/// <summary>
	/// Returns the movement component
	/// </summary>
	/// <returns>m_Movement</returns>
	UProjectileMovementComponent* getMovementComponent() const { return Movement; }
	// Sets default values for this actor's properties
	AProjectileBullet();
	/// <summary>
	/// Called when it hits somthing
	/// </summary>
	UFUNCTION()
		 void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	UFUNCTION()
		 void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) ;
	// Called every frame
	 void Tick(float DeltaTime) ;
	// Called when the game starts or when spawned
	 void BeginPlay() ;

protected:

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
