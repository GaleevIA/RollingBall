// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBall/Characters/Enemy.h"
#include "Bridge.generated.h"

UCLASS()
class ROLLINGBALL_API ABridge : public AActor
{
	GENERATED_BODY()

public:
	ABridge();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bIsTriggerable = false;
	
	UFUNCTION(BlueprintCallable)
	void CheckTrigger();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<AEnemy*> TriggerArray;

private:
	bool bIsTriggered = false;

	void ChangeState(bool State);
};
