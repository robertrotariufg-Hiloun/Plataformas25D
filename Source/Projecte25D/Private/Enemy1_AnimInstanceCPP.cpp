// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1_AnimInstanceCPP.h"

#include "EnemyControllerCPP.h"

void UEnemy1_AnimInstanceCPP::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	if (!IsValid(enemy)) return;
	
	death = enemy->death;
}

void UEnemy1_AnimInstanceCPP::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	enemy = Cast<AEnemyControllerCPP>(TryGetPawnOwner());
}
