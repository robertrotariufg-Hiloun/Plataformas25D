// Fill out your copyright notice in the Description page of Project Settings.


#include "Punch3EndNotify.h"
#include "MyCharacterC.h"

void UPunch3EndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	Super::Notify(MeshComp, Animation, EventReference);
	
	AMyCharacterC* playerNotify = Cast<AMyCharacterC>(MeshComp->GetOwner());
	
	if (IsValid(playerNotify))
	{
		if (playerNotify->combo == 3)
		{
			playerNotify->combo = 0;
			playerNotify->IsPunching = false;
		}
	}
}
