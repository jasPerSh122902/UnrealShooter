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
	m_Movement->bRotationFollowsVelocity = true;
	m_Movement->bShouldBounce = true;
}

void ABullet::MakeMesh()
{
	meshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	meshA->SetOnlyOwnerSee(false);
	meshA->SetupAttachment(m_Collision);
	meshA->bCastDynamicShadow = false;
	meshA->CastShadow = false;
	meshA->SetRelativeLocation(m_Collision->GetComponentLocation());
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;
	meshA->SetStaticMesh(Asset);
}
