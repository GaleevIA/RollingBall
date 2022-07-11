
#include "Enemy.h"

AEnemy::AEnemy()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

void AEnemy::GetDamage_Implementation()
{
	bIsDead = true;

	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
