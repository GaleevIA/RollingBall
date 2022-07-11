
#include "BallPawn.h"

#include <thread>
#include <xutility>

#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/CollisionProfile.h"
#include "Environment/Wall.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Lumin/CAPIShims/LuminAPIImpl.h"

ABallPawn::ABallPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetSimulatePhysics(true);

	RootComponent = MeshComponent;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->bUsePawnControlRotation = 0;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->SetupAttachment(MeshComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(SpringArmComponent);

	BattleSystem = CreateDefaultSubobject<UBallBattleSystem>(TEXT("Battle system"));
	BattleSystem->SetMobility(EComponentMobility::Stationary);
}

void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	ignoreActors.Init(this, 1);
	
	seekClass = AEnemy::StaticClass();
}

void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPushStarted)
	{
		PushTime += DeltaTime;

		if (PushTime >= MaxPushTime)
		{
			EndPush();
		}
	}
}

void ABallPawn::Turn(float Value)
{
	FRotator NewRotator = FRotator(0.0f, DefaultTurnAngle * Value * GetWorld()->DeltaTimeSeconds, 0.0f);

	SpringArmComponent->AddRelativeRotation(NewRotator, false, 0, ETeleportType::None);
}

void ABallPawn::StartPush()
{
	bIsPushStarted = true;
}

void ABallPawn::EndPush()
{
	float PushForce = FMath::Min(PushTime, MaxPushTime) * DefaultPushForce;
	
	MeshComponent->AddImpulse(ArrowComponent->GetForwardVector() * PushForce * MeshComponent->GetMass());
	
	bIsPushStarted = false;
	PushTime = 0.0f;
}

void ABallPawn::Attack()
{
	OnAttack();
}

void ABallPawn::OnAttack_Implementation()
{
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), AttackRadius, traceObjectTypes, seekClass, ignoreActors, TargetEnemies))
	{
		TargetEnemies = BattleSystem->GetAttackOrder(TargetEnemies, GetActorLocation(), SpringArmComponent->GetForwardVector());
	}
}
