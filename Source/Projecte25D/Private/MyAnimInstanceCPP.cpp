// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstanceCPP.h"

#include "Kismet/GameplayStatics.h"

void UMyAnimInstanceCPP::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	
	if (IsValid(prota))
	{
		horizontal = FMath:: Abs(prota->horizontal);
		jumping = prota->Isjumping;
	}
}

void UMyAnimInstanceCPP::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	prota = Cast<AMyCharacterC>(TryGetPawnOwner());
	
}
