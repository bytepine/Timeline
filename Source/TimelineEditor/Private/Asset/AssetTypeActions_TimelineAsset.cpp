// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "Asset/AssetTypeActions_TimelineAsset.h"
#include "TimelineEditor.h"
#include "TimelineAsset.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_TimelineAsset"

FText FAssetTypeActions_TimelineAsset::GetName() const
{
	return LOCTEXT("FAssetTypeActions_TimelineAsset", "Timeline Asset");
}

uint32 FAssetTypeActions_TimelineAsset::GetCategories()
{
	return FTimelineEditorModule::TimelineAssetCategory;
}

UClass* FAssetTypeActions_TimelineAsset::GetSupportedClass() const
{
	return UTimelineAsset::StaticClass();
}

FColor FAssetTypeActions_TimelineAsset::GetTypeColor() const
{
	return FColor(200, 0, 255);
}

void FAssetTypeActions_TimelineAsset::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UTimelineAsset* TimelineAsset = Cast<UTimelineAsset>(*ObjIt))
		{
			const FTimelineEditorModule* TimelineEditorModule = &FModuleManager::LoadModuleChecked<FTimelineEditorModule>("TimelineEditor");
			TimelineEditorModule->CreateFlowAssetEditor(Mode, EditWithinLevelEditor, TimelineAsset);
		}
	}
}

void FAssetTypeActions_TimelineAsset::PerformAssetDiff(UObject* OldAsset, UObject* NewAsset,
	const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision) const
{
	UE_LOG(LogBlueprint, Log, TEXT("FAssetTypeActions_TimelineAsset::PerformAssetDiff"));
}

#undef LOCTEXT_NAMESPACE
