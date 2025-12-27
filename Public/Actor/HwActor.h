// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HwActor.generated.h"

UCLASS()
class HW5_API AHwActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHwActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Move();
	void Turn();
	void ActionResult();
	void RandomEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	uint32 PrintCount = 0;
	uint32 EventCount = 0;
	UPROPERTY()
	FVector FirstLocation;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"))
	int8 Probability = 50;
	float TotalDistance = 0;
	
	float AccumulatedTime = 0.f;
	float ActionInterval = 1.0f; 
};
