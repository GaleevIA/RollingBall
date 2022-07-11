// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBall/Characters/Enemy.h"
#include "EnemiesManager.generated.h"

UCLASS()
class ROLLINGBALL_API AEnemiesManager : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<AEnemy*> Enemies;

};
