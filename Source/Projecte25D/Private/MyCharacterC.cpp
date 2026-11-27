// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterC.h"

#include "EnemyControllerCPP.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyGameInstanceCPP.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyGameModeBaseCPP.h"
#include "MySoundManagerCPP.h"
#include "MyUserWidgetCPP.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AMyCharacterC::AMyCharacterC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	
	punchLeftCollider = CreateDefaultSubobject<USphereComponent>("Left Punch");
	punchRightCollider = CreateDefaultSubobject<USphereComponent>("Right Punch");
	
	const FAttachmentTransformRules attacmentRules = FAttachmentTransformRules(EAttachmentRule :: SnapToTarget, EAttachmentRule :: SnapToTarget, EAttachmentRule::KeepWorld, false);
	
	punchLeftCollider->AttachToComponent(GetMesh(), attacmentRules, "LeftHand");
	punchRightCollider->AttachToComponent(GetMesh(), attacmentRules, "RightHand");
	punchLeftCollider->SetSphereRadius(35);
	punchRightCollider->SetSphereRadius(35);
	
}

// Called when the game starts or when spawned
void AMyCharacterC::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* playerController = Cast <APlayerController>(Controller);
	UMySoundManagerCPP* audiomanager = GetGameInstance()->GetSubsystem<UMySoundManagerCPP>();

	if (!IsValid(playerController))
	{
		return;
	}
	IsPunching = false;
	UEnhancedInputLocalPlayerSubsystem* subsytem = 
		ULocalPlayer :: GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	
	if (!IsValid(subsytem))
	{
		return;
	}
	
	subsytem->AddMappingContext(mappingContext, 0);
	
	//UE_Log(LogTemp, Log, TEXT("Antonio va a pescar")); Log consola
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, TEXT("Begin Player "));//Esto aparece en las builds
	
	if (IsValid(punchLeftCollider) && IsValid(punchRightCollider))
	{
		punchLeftCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterC::OnPunchBeginOverlap);
		punchRightCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterC::OnPunchBeginOverlap);
	}
	
	gameplayWidget = CreateWidget<UMyUserWidgetCPP>(playerController, myUserWidgetClass);
	
	if (IsValid(gameplayWidget))
	{
		gameplayWidget->AddToViewport();
		
		GetWorld()->GetTimerManager().SetTimer(timer,gameplayWidget, &UMyUserWidgetCPP::UpdateLifeBar, 0.2f );
		GetWorld()->GetTimerManager().SetTimer(timer1,gameplayWidget, &UMyUserWidgetCPP::UpdateCoinText, 0.2f );

	}
	
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

#pragma region // === MOVE & JUMP ===
void AMyCharacterC::Move(const FInputActionValue& _value)
{
	if (combo >=1)
	{
		return;
	}
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
	if (Death|| IsPunching|| Isjumping)
	{
		return;
	}
		Jump();
		Isjumping = true;
			
		UMySoundManagerCPP* audiomanager = GetGameInstance()->GetSubsystem<UMySoundManagerCPP>();
	
		if (!IsValid(audiomanager))
		{
			return;
		}
	
		audiomanager->PlaySFX(jumpSFX);

}
#pragma endregion

#pragma region //=== ATTACK ===
void AMyCharacterC::Punching(const FInputActionValue& _value)
{
	if (Death==true || Isjumping == true) return;

	if (IsPunching )
	{
		combo = FMath::Min(combo + 1, 3);

		
		return;
	}

	combo = 1;
	currentstep = 1;
	IsPunching = true;
	PlayComboStep(1);
		
}
void AMyCharacterC::PlayComboStep(int step)
{
	UAnimMontage* montage = nullptr;
	
	switch (step)
	{
	case 1:
		montage = punch1Montage;
		break;
	case 2:
		montage = punch2Montage;
		break;
	case 3:
		montage = punch3Montage;
		break;
	default:
		break;
	}
	if (!IsValid(montage))
	{
		combo = 0;
		IsPunching = false;
		currentstep = 0;
		return;
	}
	PlayAnimMontage(montage);
	GetWorld()->GetTimerManager().SetTimer(comboTimer, this,
		&AMyCharacterC::ContinueCombo, montage->GetPlayLength());
	
}

void AMyCharacterC::ContinueCombo()
{
	if (Death==true) return;

	if (combo > currentstep)
	{
		currentstep++;
		PlayComboStep(currentstep);
	}
	
	else
	{
		combo = 0;
		currentstep = 0;
		IsPunching = false;
	}
		
}
void AMyCharacterC::OnPunchBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherOverlappedComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	
	AEnemyControllerCPP* enemycontroller = Cast<AEnemyControllerCPP>(otherActor);
	
	if(IsValid(enemycontroller))
	{
		enemycontroller->TakeDamage(damage);
	}
	
	
}

void AMyCharacterC::ActivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMyCharacterC::DeactivateColliders()
{
	punchLeftCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	punchRightCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

		
#pragma endregion 

void AMyCharacterC::Pausing(const FInputActionValue& _value)
{
	
}

void AMyCharacterC::StopMovement()
{
	horizontal = 0;
}


#pragma region // === TAKE DAMAGE ===
void AMyCharacterC::TakeDamage(float _damage)
{
	
	UMyGameInstanceCPP*  myGameInstance = Cast<UMyGameInstanceCPP>(GetGameInstance());
	if (!IsValid(myGameInstance))
	{
		return;
	}
	myGameInstance->Health -= _damage;
	gameplayWidget->UpdateLifeBar();
	
	APlayerController* pc = Cast<APlayerController>(Controller);
	
	if (myGameInstance->Health <= 0)
	{
		//muerte
		Death = true;
		ReturnCombo();
	}
	else
	{
		ReturnCombo();
		PlayAnimMontage(hitMontage);
		GetWorld()->GetTimerManager().SetTimer(takeDamageTimer, this,&AMyCharacterC :: ReturnInput, hitMontage->GetPlayLength() );
	}
		//HACER LA UI Y QUE SE ACTUALIZE AL RECIBIR DAÑO 	
	
}

void AMyCharacterC::ReturnInput()
{
	APlayerController* pc = Cast<APlayerController>(Controller);
	EnableInput(pc);
}

void AMyCharacterC::ReturnCombo()
{
	GetWorld()->GetTimerManager().ClearTimer(comboTimer);
	combo = 0;
	currentstep = 0;
	IsPunching = false;
	
	DeactivateColliders();
	
}
#pragma endregion




