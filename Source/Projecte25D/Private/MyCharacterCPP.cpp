// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterCPP.h"

class UEnhancedInputLocalPlayerSubsystem;

// Sets default values
AMyCharacterCPP::AMyCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>("MyCamera");
	camera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* playerController = Cast <AplayerController>(Controller);
	
	if (IsValid(playerController))
	{
		UEnhancedInputLocalPlayerSubsystem* subsytem = playerController->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		
		if (IsValid(subsytem))
		{
			subsytem->AddMapingContext(miInputMapping,1)
		}
	}
	
}

// Called every frame
void AMyCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(enhancedComponent))
	{
		return;
	}
	enhancedComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, )

}

