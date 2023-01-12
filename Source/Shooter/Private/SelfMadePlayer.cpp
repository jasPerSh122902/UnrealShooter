// Fill out your copyright notice in the Description page of Project Settings.


#include <Shooter/Public/SelfMadePlayer.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/InputSettings.h>
#include <Components/CapsuleComponent.h>
#include <Shooter/Public/ProjectileBullet.h>
#include <MotionControllerComponent.h>
#include <Shooter/Public/TraceComp.h>

// Sets default values
ASelfMadePlayer::ASelfMadePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(CamLocation); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	TraceComp = CreateDefaultSubobject<UTraceComp>(TEXT("TraceComp"));
	TraceComp->AddToRoot();
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

void ASelfMadePlayer::OnFire()
{
	UWorld* World = GetWorld();
	FRotator SpawnRotation = GetControlRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	FVector SpawnLocation = ((MeshA != nullptr) ? MeshA->GetComponentLocation() : GetActorLocation());
	// Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	// spawn the projectile at the muzzle
	World->SpawnActor<AProjectileBullet>(SpawnLocation, SpawnRotation, ActorSpawnParams);

	
}

void ASelfMadePlayer::OnFireRay()
{
	TraceComp->GetTraceBullet();
}

void ASelfMadePlayer::MoveX(float value)
{
	if (value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ASelfMadePlayer::MoveY(float value)
{
	if (value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), value);
	}
}

// Called to bind functionality to input
void ASelfMadePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/// <summary>
	/// Binds the jump to Space
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	/// <summary>
	/// Binds the axis movement to the WASD keys
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAxis("MoveForward", this, &ASelfMadePlayer::MoveY);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASelfMadePlayer::MoveX);
	/// <summary>
	/// Bind fire event
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASelfMadePlayer::OnFire);
	PlayerInputComponent->BindAction("RayCast", IE_Pressed, this, &ASelfMadePlayer::OnFireRay);
	/// <summary>
	/// Binds the rotation of the charactor to the mouse
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}