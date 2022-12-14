// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class ASelfMadePlayer;

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ABullet();
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* meshA;
	UPROPERTY(EditAnywhere)
	USphereComponent* m_Collision;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* m_Movement;
	UPROPERTY(EditAnywhere)
	ASelfMadePlayer* m_Owner;

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
	UFUNCTION()
	USphereComponent* getColliderComponent() const { return m_Collision; }
	/// <summary>
	/// Gets the owner
	/// </summary>
	/// <returns>the owner</returns>
	UFUNCTION()
	ASelfMadePlayer* getOwner() { return m_Owner; }
	/// <summary>
	/// set owner
	/// </summary>
	/// <FString="owner"></param>
	//UFUNCTION()
	//void setOwner(ASelfMadePlayer* owner) { m_Owner = owner; }
	/// <summary>
	/// Returns the movement component
	/// </summary>
	/// <returns>m_Movement</returns>
	UFUNCTION()
	UProjectileMovementComponent* getMovementComponent() const { return m_Movement; }
	/// <summary>
	/// Gets the owner
	/// </summary>
	/// <returns>the owner</returns>
	ASelfMadePlayer* getOwner() { return m_Owner; }
	void setOwner(ASelfMadePlayer* owner) { m_Owner = owner; }
	
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

private:
	FVector startLocation;
	FVector endLocation;
};
