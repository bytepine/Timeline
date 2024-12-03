#include "Graph/TimelineGraphEditor.h"
#include "Asset/TimelineAssetEditor.h"

#define LOCTEXT_NAMESPACE "TimelineGraphEditor"

void STimelineGraphEditor::Construct(const FArguments& InArgs, const TSharedPtr<FTimelineAssetEditor> InAssetEditor)
{
	TimelineAssetEditor = InAssetEditor;
	TimelineAsset = TimelineAssetEditor.Pin()->GetTimelineAsset();

	AssetDetailsView = InArgs._AssetDetailsView;
	TrackDetailsView = InArgs._TrackDetailsView;

	BindGraphCommands();
	
	// SGraphEditor::FArguments Arguments;
	// Arguments._AdditionalCommands = CommandList;
	// Arguments._Appearance = GetGraphAppearanceInfo();
	// Arguments._AutoExpandActionMenu = true;
	//
	// SGraphEditor::Construct(Arguments);
}

void STimelineGraphEditor::BindGraphCommands()
{
	CommandList = MakeShareable(new FUICommandList);
}

FGraphAppearanceInfo STimelineGraphEditor::GetGraphAppearanceInfo() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = GetCornerText();

	return AppearanceInfo;
}

FText STimelineGraphEditor::GetCornerText() const
{
	return LOCTEXT("AppearanceCornerText_TimelineAsset", "TIMELINE");
}

#undef LOCTEXT_NAMESPACE
