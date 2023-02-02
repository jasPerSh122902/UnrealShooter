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

	UPROPERTY(Editanywhere, Category = "Color")
		FColor LineColor = FColor::Green;
	UPROPERTY(Editanywhere)
		bool LinesPresist = false, IfClicked = false;
	UPROPERTY(Editanywhere)
		float LifeTime = 1.5f, EndMultiply = 100, Thichness = 5.0f;
	UPROPERTY(Editanywhere)
		int DepthPirority = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	FVector LineStart;
	FRotator Rotation;
	FVector LineEnd;
public:	
	/// <summary>
	/// Gets If clicked
	/// </summary>
	bool getIfClicked() {return IfClicked;}
	/// <summary>
	/// Set clicked
	/// </summary>
	/// <bool="clicked"></param>
	void setClicked(bool clicked) { clicked = IfClicked; }
	/// <summary>
	/// Made the trace happen
	/// </summary>
	void DoTrace(FVector location, FRotator rotation, UWorld* currentWorld);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/// <summary>
	/// Gets the Trace
	/// </summary>
	void GetTraceBullet(float multiplyLength,FColor color, bool linePresist,float lifeTime,int proity,float thickness, UWorld* currentWorld, FVector location,FVector endLocation ,FRotator rotation);

};
