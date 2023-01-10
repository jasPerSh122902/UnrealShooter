// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>
#include <Shooter/Public/Bullet.h>
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
	//ABullet::OnOverLapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap begin");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Were in boys");
		//meshA->AddRadialForce(GetActorLocation(), 1000.f, 1000.f, ERadialImpulseFalloff::RIF_Constant);
	}
}

void AProjectileBullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ABullet::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Death");
		//Destroy();
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
	m_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Circle"));
	m_Collision->InitSphereRadius(50.0f);
	m_Collision->BodyInstance.SetCollisionProfileName("Trigger");
	// Makes it so it has collision
	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBullet::OnOverLapBegin);
	m_Collision->OnComponentEndOverlap.AddDynamic(this, &AProjectileBullet::OnOverlapEnd);
	// Makes player unable to walk on object
	m_Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	m_Collision->CanCharacterStepUpOn = ECB_No;
	// Makes the root comp to the collider
	m_Collision->SetupAttachment(RootComponent);
}

void AProjectileBullet::MakeMovement()
{
	// Makes a default movement
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Walk"));
	m_Movement->UpdatedComponent = m_Collision;
	// set the movements speed
	m_Movement->InitialSpeed = 3000.f;
	m_Movement->MaxSpeed = 3000.f;
	// Allows for rotations
	m_Movement->bRotationFollowsVelocity = true;
	// Allows for bounce
	m_Movement->bShouldBounce = true;
}

void AProjectileBullet::MakeMesh()
{
	// Make a default sub object of mesh
	meshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	// Allow all to see it
	meshA->SetOnlyOwnerSee(false);
	// Attach it to something
	meshA->SetupAttachment(m_Collision);
	// Shadows
	meshA->bCastDynamicShadow = false;
	// Case a shadow
	meshA->CastShadow = false;
	// Set the place it is in
	meshA->SetRelativeLocation(m_Collision->GetComponentLocation());
	// Set the mesh to a preset assest
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	// Make the mesh asset in to a pointer of asset
	UStaticMesh* Asset = MeshAsset.Object;
	// Set the staticMesh
	meshA->SetStaticMesh(Asset);
}

// Called every frame
void AProjectileBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}