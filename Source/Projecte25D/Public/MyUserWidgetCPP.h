// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyUserWidgetCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTE25D_API UMyUserWidgetCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LifeBar;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoinText;
	
	void UpdateLifeBar();
	void UpdateCoinText();
};
