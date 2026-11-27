// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enemy1_AnimInstanceCPP.generated.h"


class AEnemyControllerCPP;
/**
 * 
 */
UCLASS()
class PROJECTE25D_API UEnemy1_AnimInstanceCPP : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	AEnemyControllerCPP* enemy;
	
	
	UPROPERTY(VisibleAnywhere,blueprintReadOnly)
	bool death;
	
	virtual void NativeUpdateAnimation(float DeltaTime) override; // Update del blueprint anim
	
	virtual void NativeInitializeAnimation() override; // Start del blueprint anim
};
