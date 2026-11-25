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
class UAnimMontage;
class USphereComponent;
class UMyUserWidgetCPP;

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
	
	int combo;
	bool Isjumping;
	float horizontal;
	bool IsPunching;
	bool Death = false;
	
	FTimerHandle timer;
	FTimerHandle timer1;
	
	
	UPROPERTY(EditAnywhere,Category = Component)
		float damage;
	
	UPROPERTY(EditAnywhere,Category = Component)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,Category = Component)
		USphereComponent* punchLeftCollider;
	UPROPERTY(EditAnywhere,Category = Component)
		USphereComponent* punchRightCollider;
	UPROPERTY(EditAnywhere,Category = Component)
		USphereComponent*ScreamCollider;
	
	UPROPERTY(EditAnywhere,Category = Input)
	UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere,Category = Input)
	UInputAction* moveAction;
	UPROPERTY(EditAnywhere,Category = Input)
    	UInputAction* jumpAction;
    UPROPERTY(EditAnywhere,Category = Input)
    	UInputAction* punchAction;
    UPROPERTY(EditAnywhere,Category = Input)
    	UInputAction* pauseAction;
	
		
    UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* punch1Montage;
	UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* punch2Montage;
	UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* punch3Montage;
	UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* punch4Montage;
	UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* screamMontage;
	UPROPERTY(EditAnywhere,Category = Anim)
		UAnimMontage* hitMontage;
	

	UPROPERTY(EditAnywhere,Category = UI)
		UMyUserWidgetCPP* gameplayWidget;
	UPROPERTY(EditAnywhere,Category = UI)
		TSubclassOf<UMyUserWidgetCPP> myUserWidgetClass;
		
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move ( const FInputActionValue& _value);
	void Jumping ( const FInputActionValue& _value);
	void Punching ( const FInputActionValue& _value);
	void ContinueCombo();
	void Pausing ( const FInputActionValue& _value);
	void StopMovement ();
	
	UFUNCTION()
	void OnPunchBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* otherActor,UPrimitiveComponent* 
		otherOverlappedComponent,int otherBodyIndex, bool fromSweep,const FHitResult& sweepResult);

	void ActivateColliders();
	void DeactivateColliders();
	
	void TakeDamage(float _damage);
	
	void ReturnInput();
	void ReturnCombo();
	
};
