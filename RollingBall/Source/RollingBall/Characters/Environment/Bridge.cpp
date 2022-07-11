// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge.h"

// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

void ABridge::BeginPlay()
{
	Super::BeginPlay();

	if (bIsTriggerable)
	{
		ChangeState(false);
	}
}

void ABridge::CheckTrigger()
{
	for (AEnemy* Enemy : TriggerArray)
	{
		if (!Enemy->IsDead())
		{
			return;
		}
	}

	bIsTriggered = true;

	ChangeState(true);
}

void ABridge::ChangeState(bool State)
{
	Mesh->SetVisibility(State);

	if (State)
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	else
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

