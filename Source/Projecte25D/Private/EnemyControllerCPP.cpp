// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControllerCPP.h"

#include "AIController.h"
#include "MyCharacterC.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemyControllerCPP::AEnemyControllerCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	punchCollider = CreateDefaultSubobject<USphereComponent>("PunchCollider");
	
	const FAttachmentTransformRules attacmentRules = FAttachmentTransformRules(EAttachmentRule :: SnapToTarget, EAttachmentRule :: SnapToTarget, EAttachmentRule::KeepWorld, false);

	punchCollider->AttachToComponent(GetMesh(), attacmentRules, "RightHand");
	punchCollider->SetSphereRadius(32);

}

// Called when the game starts or when spawned
void AEnemyControllerCPP::BeginPlay()
{
	Super::BeginPlay();
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyControllerCPP::WatchPawn);
	
	AAIController* aiController = Cast<AAIController>(GetController());
	if (IsValid(aiController))
	{
		aiController->ReceiveMoveCompleted.AddDynamic(this,&AEnemyControllerCPP ::MoveCompleted);
	}
}

// Called every frame
void AEnemyControllerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyControllerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyControllerCPP::WatchPawn(APawn* Pawn)
{
	AMyCharacterC* player = Cast<AMyCharacterC>(Pawn);
	
	if (IsValid(player))
	{
		AAIController* aiController = Cast<AAIController>(GetController());
		if (IsValid(aiController))
		{
			aiController->MoveToActor(Pawn, 100);
		}
	}
}

void AEnemyControllerCPP::MoveCompleted(FAIRequestID aiID, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Success");
		IsPunching = true;
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Failure");
		IsPunching = false;
	}
}

void AEnemyControllerCPP::OnPunchBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherOverlappedComponent, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	
	AMyCharacterC* player = Cast<AMyCharacterC>(otherActor);
	
	if (IsValid(player))
	{
		player->TakeDamage(damage);
	}
}

void AEnemyControllerCPP::TakeDamage(float _damage)
{
	
}

void AEnemyControllerCPP::Combat()
{
	PlayAnimMontage(attackAnimMontage);
	//GetWorld()->GetTimerManager().SetTimer(timer, this, &AEnemyControllerCPP :: MoveCompleted, attackAnimMontage)
}

