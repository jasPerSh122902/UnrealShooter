// Fill out your copyright notice in the Description page of Project Settings.

#include <Shooter/Public/Bullet.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>
#include <Shooter/PlayerBehaviour/SelfMadePlayer.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ABullet::ABullet()
{
	MakeCollision();
	MakeMesh();
	MakeMovement();
	// Die after 3 secomponents
	InitialLifeSpan = 3.0f;
	//setOwner("SelfMadePlayer");
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	startLocation = GetActorLocation();
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap begin");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Were in boys");
		meshA->AddRadialForce(GetActorLocation(), 10.f, 10.f, ERadialImpulseFalloff::RIF_Constant);
	}
}

void ABullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Death");
		Destroy();
	}
}

void ABullet::MakeCollision()
{
	// Sets a sphere as the base collider
	m_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Circle"));
	m_Collision->InitSphereRadius(50.0f);
	m_Collision->BodyInstance.SetCollisionProfileName("Trigger");
	// Makes it so it has collision
	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverLapBegin);
	m_Collision->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
	// Makes player unable to walk on object
	m_Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	m_Collision->CanCharacterStepUpOn = ECB_No;
	// Makes the root comp to the collider
	m_Collision->SetupAttachment(RootComponent);

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASelfMadePlayer::StaticClass(), ActorsToFind);

	for (AActor* player : ActorsToFind)
	{
		ASelfMadePlayer* playercast = Cast<ASelfMadePlayer>(player);
		if (playercast)
		{
			setOwner(playercast);
		}
	}
}

void ABullet::MakeMovement()
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

void ABullet::MakeMesh()
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
