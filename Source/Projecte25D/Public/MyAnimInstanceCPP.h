// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterC.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstanceCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTE25D_API UMyAnimInstanceCPP : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	AMyCharacterC* prota;
	
	UPROPERTY(VisibleAnywhere,blueprintReadOnly)
	float horizontal;
	UPROPERTY(VisibleAnywhere,blueprintReadOnly)
	bool jumping;
	UPROPERTY(VisibleAnywhere,blueprintReadOnly)
    bool death;
	
	virtual void NativeUpdateAnimation(float DeltaTime) override; // Update del blueprint anim
	
	virtual void NativeInitializeAnimation() override; // Start del blueprint anim
	
};
