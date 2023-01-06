// Fill out your copyright notice in the Description page of Project Settings.

#include <Shooter/Public/Bullet.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Engine.h>


// Sets default values
ABullet::ABullet()
{

	

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
		
	}
}

void ABullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Overlap End");
	if ((OtherActor != this) && (OtherActor->GetFName() != "SelfMadePlayer_0"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Death");
		
	}
}