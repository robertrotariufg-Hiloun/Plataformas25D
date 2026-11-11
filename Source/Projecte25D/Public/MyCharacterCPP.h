// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacterCPP.generated.h"

UCLASS()
class PROJECTE25D_API AMyCharacterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;// es como el start Unity

public:	

	UCameraComponent* Camera;	


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* miInputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* moveAction;

	// Called every frame
	virtual void Tick(float DeltaTime) override; // Es el Update 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue & value)
	{
		float inputValue = value.Get<float>();
		AddMovementInput (FVector(inputValue, 0 , 0))
	}
};
