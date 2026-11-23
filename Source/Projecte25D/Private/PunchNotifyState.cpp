// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchNotifyState.h"
#include "MyCharacterC.h"

void UPunchNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	//se ejecuta cuando empieza notifystate
	AMyCharacterC* myCharacter = Cast<AMyCharacterC>(MeshComp->GetOwner());
	if (IsValid(myCharacter))
	{
		myCharacter->ActivateColliders();
	}
}

void UPunchNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//se ejecuta cuando termina notifystate
	AMyCharacterC* myCharacter = Cast<AMyCharacterC>(MeshComp->GetOwner());
	if (IsValid(myCharacter))
	{
		myCharacter->DeactivateColliders();
	}
}

void UPunchNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	//se ejecuta cada frame que  notifystate este activo

}
