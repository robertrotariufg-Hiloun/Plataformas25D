// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class PROJECTE25D_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override; 
	
public:
	UPROPERTY(meta =(BindWidget))
		UButton* PlayButton;
	
	UPROPERTY(meta =(BindWidget))
		UButton* ExitButton;
	
	UFUNCTION()
	void PlayButtonClicked();
	
	UFUNCTION()
	void ExitButtonClicked();
};
