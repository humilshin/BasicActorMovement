// Fill out your copyright notice in the Description page of Project Settings.

#include "HW5/Public/Actor/HwActor.h"

// Sets default values
AHwActor::AHwActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHwActor::BeginPlay()
{
	Super::BeginPlay();
	FirstLocation = GetActorLocation();
}

// Called every frame
void AHwActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AccumulatedTime += DeltaTime;
	
	if (AccumulatedTime >= ActionInterval)
	{
		AccumulatedTime = 0.f;
		TotalDistance += Move();
		Turn();
		ActionResult();
	}
}

float AHwActor::Move()
{
	const FVector Offset(
		FMath::FRandRange(-50.f, 50.f),
		FMath::FRandRange(-50.f, 50.f),
		FMath::FRandRange(-50.f, 50.f)
	);
	const FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + Offset);
	return Offset.Size();
}

void AHwActor::Turn()
{
	const float RandomPitch = FMath::FRandRange(0.f, 360.f);
	const float RandomYaw = FMath::FRandRange(0.f, 360.f);
	const float RandomRoll = FMath::FRandRange(0.f, 360.f);
	
	FRotator const RandomRotation(RandomPitch, RandomYaw, RandomRoll);
	SetActorRotation(RandomRotation);
}

void AHwActor::RandomEvent()
{
	if (FMath::RandRange(1, 100) <= Probability)
	{
		EventCount++;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Random Event Triggered : #%d"), EventCount));
		}
	} 
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Random Event Failed")));
		}
	}
}

void AHwActor::ActionResult()
{
	PrintCount++;
	const FVector CurrentLocation = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Current Location #%d X : %f Y : %f Z : %f") ,PrintCount ,CurrentLocation.X ,CurrentLocation.Y ,CurrentLocation.Z));
	}
	
	if (PrintCount % 10 == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Total Distance : %f"), TotalDistance));
		}
		RandomEvent();
	}
	
}


