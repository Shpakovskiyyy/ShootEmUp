// Shoot Em Up. Educational Project

#include "Pickups/SEUBasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASEUBasePickup::ASEUBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASEUBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);

    GenerateRotationYaw();
}

void ASEUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if(GivePickupTo(Pawn))
    {
        PickupTaken();
    }
}

void ASEUBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorWorldRotation(FRotator(0.f, RotationYaw, 0.f));
}

bool ASEUBasePickup::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ASEUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASEUBasePickup::PickupTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASEUBasePickup::Respawn, RespawnTime);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), TakenSound, GetActorLocation());
}

void ASEUBasePickup::Respawn()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap );

    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ASEUBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}
