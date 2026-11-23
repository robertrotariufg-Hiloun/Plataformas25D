// Fill out your copyright notice in the Description page of Project Settings.


#include "Punch2Notify.h"

#include "MyCharacterC.h"
#include "PunchEndCpp.h"

void UPunch2Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                          const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AMyCharacterC* playerNotify = Cast<AMyCharacterC>(MeshComp->GetOwner());
	
	if (IsValid(playerNotify))
	{
		if (playerNotify->combo == 2)
		{
			playerNotify->combo = 0;
			playerNotify->IsPunching = false;
		}
	}
}
