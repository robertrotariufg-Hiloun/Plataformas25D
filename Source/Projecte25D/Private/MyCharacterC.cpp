// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterC.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMyCharacterC::AMyCharacterC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacterC::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* playerController = Cast <APlayerController>(Controller);
	if (!IsValid(playerController))
	{
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* subsytem = 
		ULocalPlayer :: GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	
	if (!IsValid(subsytem))
	{
		return;
	}
	
	subsytem->AddMappingContext(mappingContext, 0);
	
	//UE_Log(LogTemp, Log, TEXT("Antonio va a pescar")); Log consola
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, TEXT("Begin Player "));//Esto aparece en las builds
	
}

// Called every frame
void AMyCharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetCharacterMovement()->IsFalling()== false)
	{
		Isjumping = false;
	}

}

// Called to bind functionality to input
void AMyCharacterC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!IsValid(enhancedComponent))
	{
		return;
	}
	enhancedComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMyCharacterC::Move);
	enhancedComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &AMyCharacterC::Jumping);
	enhancedComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &AMyCharacterC::StopMovement);
	enhancedComponent->BindAction(punchAction, ETriggerEvent::Started, this, &AMyCharacterC::Punching);
	enhancedComponent->BindAction(pauseAction, ETriggerEvent::Started, this, &AMyCharacterC::Pausing);

}

void AMyCharacterC::Move(const FInputActionValue& _value)
{
	horizontal = _value.Get<float>();
	AddMovementInput(FVector(horizontal,0,0));
	if (horizontal < 0 )
	{
		GetMesh()->SetRelativeRotation(FRotator(0,-270, 0));
		
	}
	else if (horizontal > 0)
	{
		GetMesh()->SetRelativeRotation(FRotator(0,-90, 0));

	}
	
	
}

void AMyCharacterC::Jumping(const FInputActionValue& _value)
{
	if (combo < 1 || Isjumping == false)
	{
		Jump();
		Isjumping = true;
	}
}



void AMyCharacterC::Punching(const FInputActionValue& _value)
{
	
}

void AMyCharacterC::Pausing(const FInputActionValue& _value)
{
	
}

void AMyCharacterC::StopMovement()
{
	horizontal = 0;
}


