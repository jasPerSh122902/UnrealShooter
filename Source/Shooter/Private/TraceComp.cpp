// Fill out your copyright notice in the Description page of Project Settings.
#include "TraceComp.h"
#include <Engine/Engine.h>
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
// Sets default values for this component's properties
UTraceComp::UTraceComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTraceComp::BeginPlay()
{
	Super::BeginPlay();
	MyCharactor = Cast<ACharacter>(GetOwner());
}

// Called every frame
void UTraceComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTraceComp::GetTraceBullet()
{
	// Prinst the message to the log
	UE_LOG(LogTemp, Warning, TEXT("Sending ray Trace"))
	// Get the player controlls and get the location and rotation of the player
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(OUT location,OUT rotation);
	// Is the lines end
	LineEnd = location + rotation.Vector() * EndMultiply;
	// Draws the line at the current location to the end
	DrawDebugLine(GetWorld(),location,LineEnd,FColor::Green,false,1.5f,0,5.0f);
}