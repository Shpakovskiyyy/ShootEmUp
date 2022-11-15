// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Player/SEUBaseCharacter.h"
#include "SEUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class SHOOTEMUP_API ASEUPlayerCharacter : public ASEUBaseCharacter
{
    GENERATED_BODY()

public:
    ASEUPlayerCharacter(const FObjectInitializer& ObjInit);

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual bool IsRunning() const override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CameraCollisionComponent;

    virtual void BeginPlay() override;

    virtual void OnDeath() override;

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();

    UFUNCTION()
    void OnCameraCollisionBeginOverlap
    (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap
    (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void CheckCameraOverlap();
    
};
