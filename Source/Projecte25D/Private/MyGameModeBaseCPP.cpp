// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBaseCPP.h"

AMyGameModeBaseCPP::AMyGameModeBaseCPP()
{
	
	static ConstructorHelpers ::FClassFinder<APawn> PlayerPawn (TEXT("/Game/BluePrintCPP/BP_MyCharacter"));
	
	if (PlayerPawn.Class != NULL)
	{
		DefaultPawnClass = PlayerPawn.Class;
		
	}
}
