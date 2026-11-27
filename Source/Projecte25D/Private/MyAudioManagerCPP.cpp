// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAudioManagerCPP.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMyAudioManagerCPP::AMyAudioManagerCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyAudioManagerCPP::PlaySFX(USoundBase* sfx,const UObject* _location, float _volume)
{
	UGameplayStatics::PlaySound2D(_location,sfx,_volume );
}

void AMyAudioManagerCPP::PlayMusic(USoundBase* sfx, float volume)
{
	
}

// Called when the game starts or when spawned
void AMyAudioManagerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyAudioManagerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

