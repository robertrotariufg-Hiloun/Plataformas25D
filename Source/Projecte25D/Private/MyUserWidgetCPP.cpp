// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidgetCPP.h"

#include "MyGameInstanceCPP.h"

void UMyUserWidgetCPP::UpdateLifeBar()
{
	UMyGameInstanceCPP* gameInstance = Cast<UMyGameInstanceCPP>(GetGameInstance());
	
	if (!IsValid(gameInstance))
	{
		return;
	}
	
	float percent = gameInstance->Health/gameInstance->MaxHealth;
	
	LifeBar->SetPercent(percent);
}

void UMyUserWidgetCPP::UpdateCoinText()
{
	UMyGameInstanceCPP* gameInstance = Cast<UMyGameInstanceCPP>(GetGameInstance());
	
	if (!IsValid(gameInstance))
	{
		return;
	}
	
	CoinText->SetText(FText::AsNumber(gameInstance->colleccionable));
}
	