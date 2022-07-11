
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BallController.generated.h"

UCLASS()
class ROLLINGBALL_API ABallController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual  void SetupInputComponent() override;

private:
	void Turn(float Value);
	void StartPush();
	void EndPush();
	void Attack();
	
	TSoftObjectPtr<class ABallPawn> CachedBallPawn;
};


