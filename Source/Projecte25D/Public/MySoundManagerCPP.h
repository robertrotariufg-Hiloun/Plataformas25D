// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySoundManagerCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTE25D_API UMySoundManagerCPP : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		UAudioComponent* audioComponent;
	
	void PlaySFX(USoundBase* SFX);
	void PlayMusic(USoundBase* Music);
	void StopMusic();
	
};
