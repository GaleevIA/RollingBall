
#pragma once

#include "CoreMinimal.h"
#include "BattleSystem/BallBattleSystem.h"
#include "GameFramework/Pawn.h"
#include "BallPawn.generated.h"

UCLASS(Abstract, Blueprintable)
class ROLLINGBALL_API ABallPawn : public APawn
{
	GENERATED_BODY()

public:
	ABallPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Turn(float Value);
	void StartPush();
	void EndPush();
	void Attack();

	UFUNCTION(BlueprintCallable)
    float GetPushTime() { return PushTime; };

	UPROPERTY(BlueprintReadWrite)
	bool bIsInputDisabled = false;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBallBattleSystem* BattleSystem;

	UFUNCTION(BlueprintNativeEvent, Category = "Rolling Ball | Battle system")
	void OnAttack();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rolling Ball Pawn")
	float DefaultTurnAngle = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rolling Ball Pawn")
	float DefaultPushForce = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rolling Ball Pawn")
	float MaxPushTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rolling Ball Pawn")
	float AttackRadius = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rolling Ball Pawn")
	float AttackSpeed = 0.1f;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> TargetEnemies;
	
private:
	bool bIsPushStarted = false;
	float PushTime;

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	TArray<AActor*> ignoreActors;
	UClass* seekClass;
};
