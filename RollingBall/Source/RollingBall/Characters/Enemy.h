
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class ROLLINGBALL_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	AEnemy();
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() { return bIsDead; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetDamage();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;
	
private:
	bool bIsDead = false;
};
