// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstanceCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTE25D_API UMyGameInstanceCPP : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = PlayerParameters)
	float Health;
	UPROPERTY(EditAnywhere, Category = PlayerParameters)
	float MaxHealth;
	UPROPERTY(EditAnywhere, Category = PlayerParameters)
	int colleccionable;
	
	//
	//UFUNCTION(BlueprintCallable)
	//virtual void Init() override; //Se ejecuta al iniciar el game instance
};
