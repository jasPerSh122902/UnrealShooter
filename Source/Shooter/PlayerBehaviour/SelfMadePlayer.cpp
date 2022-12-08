// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBehaviour/SelfMadePlayer.h"

// Sets default values
ASelfMadePlayer::ASelfMadePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelfMadePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelfMadePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelfMadePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

