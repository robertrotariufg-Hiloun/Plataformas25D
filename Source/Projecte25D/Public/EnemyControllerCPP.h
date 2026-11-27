
#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h" 
#include "EnemyControllerCPP.generated.h"

class USphereComponent;

UCLASS()
class PROJECTE25D_API AEnemyControllerCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyControllerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	FTimerHandle timer;
	bool IsPunching;
	bool death;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health;
	
	UPROPERTY(VisibleAnywhere, Category=Parameters)
		UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleAnywhere, Category=Parameters)
		USphereComponent* punchCollider;
	
	UPROPERTY(VisibleAnywhere, Category=Anim)
		UAnimMontage* attackAnimMontage;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void  WatchPawn(APawn* Pawn);
	
	UFUNCTION()
	void  MoveCompleted (FAIRequestID aiID, EPathFollowingResult::Type result);
	
	UFUNCTION()
	void OnPunchBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* otherActor,UPrimitiveComponent* 
		otherOverlappedComponent,int otherBodyIndex, bool fromSweep,const FHitResult& sweepResult);

	void TakeDamage(float damage);
	void Combat();
};
