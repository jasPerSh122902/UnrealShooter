// Fill out your copyright notice in the Description page of Project Settings.

#include <Shooter/Public/Wall.h>
#include <Components/BoxComponent.h>
#include <Engine/Engine.h>

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	m_Collision->InitBoxExtent(Size);
	m_Collision->BodyInstance.SetCollisionProfileName("Trigger");
	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &AWall::OnOverLapBegin);
	m_Collision->OnComponentEndOverlap.AddDynamic(this, &AWall::OnOverlapEnd);

	m_Collision->SetupAttachment(RootComponent);

	meshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	meshA->CastShadow = false;
	meshA->SetupAttachment(m_Collision);
	meshA->SetRelativeLocation(m_Collision->GetComponentLocation());
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAssest(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	UStaticMesh* Asset = MeshAssest.Object;
	meshA->SetStaticMesh(Asset);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

void AWall::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "start Collision walls");
}

void AWall::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "End Collision walls");
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


