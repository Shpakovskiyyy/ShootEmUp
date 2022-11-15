// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUCoreTypes.h"
#include "SEULevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTEMUP_API USEULevelItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& NewLevelItemData);
    FLevelData GetLevelData() const { return LevelItemData; }

    void SetSelected(bool IsSelected);
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelThumbnail = nullptr;
    
    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelItemData;

    UFUNCTION()
    void OnLevelItemSelected();

    UFUNCTION()
    void OnLevelItemHovered();

    UFUNCTION()
    void OnLevelItemUnhovered();
    
};
