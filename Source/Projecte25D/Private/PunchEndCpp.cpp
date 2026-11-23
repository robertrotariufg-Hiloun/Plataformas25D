// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchEndCpp.h"

#include "MyCharacterC.h"

void UPunchEndCpp::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                          const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AMyCharacterC* playerNotify = Cast<AMyCharacterC>(MeshComp->GetOwner());
	
	if (IsValid(playerNotify))
	{
		if (playerNotify->combo == 1)
		{
			playerNotify->combo = 0;
			playerNotify->IsPunching = false;
		}
	}
}
