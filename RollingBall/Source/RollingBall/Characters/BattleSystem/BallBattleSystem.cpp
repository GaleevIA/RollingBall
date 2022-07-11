
#include "BallBattleSystem.h"
#include <cmath>

float UBallBattleSystem::Clamp(float Value, float Min, float Max)
{
	float ReturnValue = Value;
	
	if (Value < Min)
		ReturnValue = Min;
	else if (Value > Max)
		ReturnValue = Max;

	return ReturnValue;
}

bool UBallBattleSystem::ComparePoints(AActor* A, AActor* B, FVector Center, FVector Arrow)
{
	FVector a = A->GetActorLocation();
	FVector b = B->GetActorLocation();

	FVector NewArrow = FVector(Arrow.X - Center.X, Arrow.Y - Center.Y, Arrow.Z - Center.Z);
	FVector NewVectorA = FVector(a.X - Center.X, a.Y - Center.Y, a.Z - Center.Z);
	FVector NewVectorB = FVector(b.X - Center.X, b.Y - Center.Y, b.Z - Center.Z);
	
	float AngleA = 0;
	float AngleB = 0;
	
	float CosA = atan2(NewArrow.X * NewVectorA.Y - NewArrow.Y * NewVectorA.X, NewArrow.X * NewVectorA.X + NewArrow.Y * NewVectorA.Y);
	float CosB = atan2(NewArrow.X * NewVectorB.Y - NewArrow.Y * NewVectorB.X, NewArrow.X * NewVectorB.X + NewArrow.Y * NewVectorB.Y);
	
	return CosA > CosB;
}

TArray<AActor*> UBallBattleSystem::GetAttackOrder(TArray<AActor*> Enemies, FVector Center, FVector Arrow)
{
	//Не заработало :(
	//std::sort(Enemies.begin(), Enemies.end(), &UBallBattleSystem::ComparePoints);

	int ArrayLength = Enemies.Max();
	
	for (int i = 0; i < ArrayLength; i++)
	{
		for (int j = i + 1; j < ArrayLength; j++)
		{
			if (ComparePoints(Enemies[i], Enemies[j], Center, Arrow))
			{
				AActor* B = Enemies[i];
				Enemies[i] = Enemies[j];
				Enemies[j] = B;
			}
		}
	}

	TArray<AActor*> OrderedEnemies;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	for (AActor* Actor : Enemies)
	{
		if (!(Cast<AEnemy>(Actor))->IsDead())
		{
			FHitResult OutHit;
			GetWorld()->LineTraceSingleByChannel(OutHit, Center, Actor->GetActorLocation(), ECC_Visibility, CollisionParams);

			if (!OutHit.bBlockingHit)
			{
				OrderedEnemies.Add(Actor);
			}
		}
	}
	
	return OrderedEnemies;
}
