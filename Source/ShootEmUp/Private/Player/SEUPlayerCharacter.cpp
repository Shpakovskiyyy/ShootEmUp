// Shoot Em Up. Educational Project

#include "Player/SEUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Weapon/SEUWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

ASEUPlayerCharacter::ASEUPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector{ 0.f, 100.f, 80.f };

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASEUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASEUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASEUPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASEUPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASEUPlayerCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASEUPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASEUPlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASEUPlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USEUWeaponComponent::StartShooting);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USEUWeaponComponent::StopShooting);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USEUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USEUWeaponComponent::Reload);

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &USEUWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &USEUWeaponComponent::Zoom, false);
}

bool ASEUPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASEUPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollisionComponent);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASEUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASEUPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASEUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASEUPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.f;
    if (!Amount) return;

    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASEUPlayerCharacter::MoveRight(float Amount)
{
    if (!Amount) return;

    AddMovementInput(GetActorRightVector(), Amount);
}

void ASEUPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ASEUPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void ASEUPlayerCharacter::OnCameraCollisionBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void ASEUPlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void ASEUPlayerCharacter::CheckCameraOverlap()
{
    const bool ToHideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(ToHideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for(auto Child : MeshChildren)
    {
        const auto ChildGeometry = Cast<UPrimitiveComponent>(Child);
        if(ChildGeometry)
        {
            ChildGeometry->SetOwnerNoSee(ToHideMesh);
        }
    }
}
