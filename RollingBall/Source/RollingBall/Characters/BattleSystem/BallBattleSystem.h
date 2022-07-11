
#pragma once

#include "CoreMinimal.h"
#include "RollingBall/Characters/Enemy.h"
#include "BallBattleSystem.generated.h"

UCLASS()
class ROLLINGBALL_API UBallBattleSystem : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	TArray<AActor*> GetAttackOrder(TArray<AActor*> Enemies, FVector Center, FVector Arrow);

private:
	bool ComparePoints(AActor* A, AActor* B, FVector Center, FVector Arrow);

	float Clamp(float Value, float Min, float Max);
};
