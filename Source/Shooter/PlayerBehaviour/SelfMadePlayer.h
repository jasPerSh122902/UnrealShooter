// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SelfMadePlayer.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class SHOOTER_API ASelfMadePlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = " Mesh ")
	USkeletalMeshComponent* MeshA;
	/// <summary>
	/// Camera
	/// </summary>
	UPROPERTY(VisibleAnywhere,  Category = " Camera " )
	UCameraComponent* CameraComponent;
public:
	/// </summary>
	/// Sets default values for this character's properties
	/// /// </summary>
	ASelfMadePlayer();
protected:
	/// </summary>
	/// Called when the game starts or when spawned
	/// </summary>
	virtual void BeginPlay() override;
public:	
	/// </summary>
	/// Called every frame
	/// </summary>
	virtual void Tick(float DeltaTime) override;
	/// <summary>
	/// Move on the X
	/// </summary>
	/// <param name="value">is the input</param>
	void MoveX(float value);
	/// <summary>
	/// Move on the Y
	/// </summary>
	/// <param name="value">is the input</param>
	void MoveY(float value);
	/// <summary>
	///  Called to bind functionality to input
	/// </summary>
	/// <param name="PlayerInputComponent">input</param>
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere,  Category = "Camera")
	float BaseLookUpRate;
	UPROPERTY(VisibleAnywhere)
	FVector CamLocation;
};
