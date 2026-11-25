// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayButtonClicked);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitButtonClicked);
}

void UMainMenuWidget::PlayButtonClicked()
{
	UGameplayStatics :: OpenLevel(this, "1");
	
}

void UMainMenuWidget::ExitButtonClicked()
{
	UKismetSystemLibrary:: QuitGame(this, nullptr, EQuitPreference::Quit, false );
}
