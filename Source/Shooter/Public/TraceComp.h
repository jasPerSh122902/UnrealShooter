// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComp.generated.h"

class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UTraceComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraceComp();
	UPROPERTY(Editanywhere, Category = "StartPoint")
		FVector location;
	UPROPERTY(Editanywhere)
		FRotator rotation;
	UPROPERTY(Editanywhere, Category = "EndPoint")
		FVector LineEnd;
	UPROPERTY(Editanywhere , Category = "multipler")
		float EndMultiply = 100;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/// <summary>
	/// Gets the Trace
	/// </summary>
	void GetTraceBullet();

private:
	ACharacter* MyCharactor;

};
