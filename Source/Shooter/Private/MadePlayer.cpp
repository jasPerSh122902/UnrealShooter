// Fill out your copyright notice in the Description page of Project Settings.


#include "MadePlayer.h"

// Sets default values
AMadePlayer::AMadePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMadePlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMadePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMadePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

