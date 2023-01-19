// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>
#include <Shooter/Public/SelfMadePlayer.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
AProjectileBullet::AProjectileBullet()
{
	MakeCollision();
	MakeMesh();
	MakeMovement();
	// Die after 3 secomponents
	InitialLifeSpan = 3.0f;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileBullet::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap begin");
	// If the other actor that was collided with is not Its self
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Were in boys");
		// This is for ricishay off of a object
		Movement->AddForce( BounceOff * 30);
		// increase the scale
		this->SetActorScale3D(FVector(2, 2, 5));
	}
}

void AProjectileBullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End start");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End");
		//GEngine->ClearOnScreenDebugMessages();
	}
}

// Called when the game starts or when spawned
void AProjectileBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBullet::MakeCollision()
{
	// Sets a sphere as the base collider
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Circle"));
	// Set the radius
	Collision->InitSphereRadius(50.0f);
	Collision->BodyInstance.SetCollisionProfileName("Trigger");
	// Makes it so it has collision
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBullet::OnOverLapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AProjectileBullet::OnOverlapEnd);
	// Makes player unable to walk on object
	Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Collision->CanCharacterStepUpOn = ECB_No;
	// Makes the root comp to the collider
	Collision->SetupAttachment(RootComponent);
}

void AProjectileBullet::MakeMovement()
{
	// Makes a default movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Walk"));
	Movement->UpdatedComponent = Collision;
	// set the movements speed
	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 10000.f;
	// Allows for rotations
	Movement->bRotationFollowsVelocity = true;
	// Allows for bounce
	Movement->bShouldBounce = true;
}

void AProjectileBullet::MakeMesh()
{
	// Make a default sub object of mesh
	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	// Allow all to see it
	MeshA->SetOnlyOwnerSee(false);
	// Attach it to something
	MeshA->SetupAttachment(Collision);
	// Shadows
	MeshA->bCastDynamicShadow = false;
	// Case a shadow
	MeshA->CastShadow = false;
	// Set the place it is in
	MeshA->SetRelativeLocation(Collision->GetComponentLocation());
	// Set the mesh to a preset assest
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	// Make the mesh asset in to a pointer of asset
	UStaticMesh* Asset = MeshAsset.Object;
	// Set the staticMesh
	MeshA->SetStaticMesh(Asset);
}

// Called every frame
void AProjectileBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}