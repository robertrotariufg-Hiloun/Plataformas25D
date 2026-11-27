// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoundManagerCPP.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"



void UMySoundManagerCPP::PlaySFX(USoundBase* _SFX)
{
	 UGameplayStatics:: PlaySound2D(this,_SFX);
}

void UMySoundManagerCPP::PlayMusic(USoundBase* Music)
{
	audioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), Music, 1, 1,0);
}

void UMySoundManagerCPP::StopMusic()
{
	if (audioComponent)
	{
		audioComponent->Stop();
	}
}
