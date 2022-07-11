

#include "BallController.h"
#include "BallPawn.h"

void ABallController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBallPawn = Cast<ABallPawn>(InPawn);
}

void ABallController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Turn", this, &ABallController::Turn);
	InputComponent->BindAction("Push", EInputEvent::IE_Pressed, this, &ABallController::StartPush);
	InputComponent->BindAction("Push", EInputEvent::IE_Released, this, &ABallController::EndPush);
	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ABallController::Attack);
}

void ABallController::Turn(float Value)
{
	if (CachedBallPawn.IsValid() && Value != 0 && !CachedBallPawn->bIsInputDisabled)
	{
		CachedBallPawn->Turn(Value);
	}
}

void ABallController::StartPush()
{
	if (CachedBallPawn.IsValid() && !CachedBallPawn->bIsInputDisabled)
	{
		CachedBallPawn->StartPush();
	}
}

void ABallController::EndPush()
{
	if (CachedBallPawn.IsValid() && !CachedBallPawn->bIsInputDisabled)
	{
		CachedBallPawn->EndPush();
	}
}

void ABallController::Attack()
{
	if (CachedBallPawn.IsValid() && !CachedBallPawn->bIsInputDisabled)
	{
		CachedBallPawn->Attack();
	}
}
