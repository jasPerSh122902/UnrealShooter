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
		FVector lineStart;
	UPROPERTY(Editanywhere)
		FRotator rotation;
	UPROPERTY(Editanywhere, Category = "EndPoint")
		FVector LineEnd;
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
	/// <summary>
/// Called when it hits somthing
/// </summary>
	UFUNCTION()
		void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	bool getIfClicked() {return IfClicked;}
	void setClicked(bool clicked) { clicked = IfClicked; }
	bool DoTrace(FHitResult* Hit, FCollisionQueryParams* params);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/// <summary>
	/// Gets the Trace
	/// </summary>
	void GetTraceBullet(float multiplyLength,FColor color, bool linePresist,float lifeTime,int proity,float thickness);

private:
	ACharacter* MyCharactor;

};
