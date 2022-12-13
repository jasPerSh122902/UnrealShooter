// Fill out your copyright notice in the Description page of Project Settings.

#include <Shooter/Public/Bullet.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Sets a sphere as the base collider
	m_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("m_Collision"));
	m_Collision->InitSphereRadius(50.0f);
	m_Collision->BodyInstance.SetCollisionProfileName("Projectile");
	// Makes it so it has collision
	m_Collision->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	// Makes player unable to walk on object
	m_Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	m_Collision->CanCharacterStepUpOn = ECB_No;
	// Makes the root comp to the collider
	RootComponent = m_Collision;
	meshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshA"));
	meshA->SetOnlyOwnerSee(false);
	meshA->SetupAttachment(m_Collision);
	meshA->bCastDynamicShadow = false;
	meshA->CastShadow = false;
	meshA->SetRelativeLocation(m_Collision->GetComponentLocation());
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;
	meshA->SetStaticMesh(Asset);
	// Makes a default movement
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("m_Movement"));
	m_Movement->UpdatedComponent = m_Collision;
	// set the movements speed
	m_Movement->InitialSpeed = 3000.f;
	m_Movement->MaxSpeed = 3000.f;
	m_Movement->bRotationFollowsVelocity = true;
	m_Movement->bShouldBounce = true;
	// Die after 3 secomponents
	InitialLifeSpan = 3.0f;
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != this)
		Destroy();
}