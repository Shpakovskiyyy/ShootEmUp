// Shoot Em Up. Educational Project

#include "Menu/UI/SEULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USEULevelItemWidget::SetLevelData(const FLevelData& NewLevelItemData)
{
    LevelItemData = NewLevelItemData;

    if(LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(LevelItemData.LevelDisplayName));
    }
    if(LevelThumbnail)
    {
        LevelThumbnail->SetBrushFromTexture(LevelItemData.LevelThumbnail);
    }
}

void USEULevelItemWidget::SetSelected(bool IsSelected)
{
    if(LevelThumbnail)
    {
        LevelThumbnail->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USEULevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USEULevelItemWidget::OnLevelItemSelected);
        LevelSelectButton->OnHovered.AddDynamic(this, &USEULevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USEULevelItemWidget::OnLevelItemUnhovered);
    }
}

void USEULevelItemWidget::OnLevelItemSelected()
{
    OnLevelSelected.Broadcast(LevelItemData);
}

void USEULevelItemWidget::OnLevelItemHovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USEULevelItemWidget::OnLevelItemUnhovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
