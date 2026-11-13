// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h" //<-- Incluye todo lo de camera/cameracomponent
#include "GameFramework/Character.h"
#include "MyCharacterC.generated.h"

//class UCameraComponent; <-- Referencia blanda solo incluye ese componente
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
struct FInputActionValue;

UCLASS()// <-- se le llama Macro
class PROJECTE25D_API AMyCharacterC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere,Category = Component)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere,Category = Input)
	UInputMappingContext* mappingContext;
	
	UPROPERTY(EditAnywhere,Category = Input)
	UInputAction* moveAction;
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move ( const FInputActionValue& _value);
	
};
