// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScriptActorCpp.h"

#include "EngineUtils.h"

void AMyLevelScriptActorCpp::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AActor> actors(GetWorld()); actors; ++actors)
	{
		if (actors->ActorHasTag("Meta"))
		{
			winTrigger = actors->FindComponentByClass<UBoxComponent>();
		}
	}
	
	if (IsValid(winTrigger))
	{
		winTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMyLevelScriptActorCpp::Win);

	}
}

void AMyLevelScriptActorCpp::Win(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int bodyIndex, bool isSweep, const FHitResult& sweepResult)
{
	
	
}
