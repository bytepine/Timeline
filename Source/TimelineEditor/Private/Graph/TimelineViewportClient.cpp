// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "Graph/TimelineViewportClient.h"
#include "AdvancedPreviewScene.h"

void STimelineAssetEditorViewport::Construct(const FArguments& InArgs)
{
	PreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
	PreviewScene->SetFloorVisibility(false);

	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<SEditorViewport> STimelineAssetEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> STimelineAssetEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void STimelineAssetEditorViewport::OnFloatingButtonClicked()
{
	
}

void STimelineAssetEditorViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	
}

TSharedRef<FEditorViewportClient> STimelineAssetEditorViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FTimelineViewportClient(PreviewScene.Get(), SharedThis(this)));
	EditorViewportClient->SetRealtime(true);
	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> STimelineAssetEditorViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}

FTimelineViewportClient::FTimelineViewportClient(FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget)
	: FEditorViewportClient(nullptr, InPreviewScene, InEditorViewportWidget)
{
	SetViewMode(VMI_Lit);

	// Always composite editor objects after post processing in the editor
	EngineShowFlags.SetCompositeEditorPrimitives(true);
	EngineShowFlags.DisableAdvancedFeatures();

	// Setup defaults for the common draw helper.
	DrawHelper.bDrawPivot = false;
	DrawHelper.bDrawWorldBox = false;
	DrawHelper.bDrawKillZ = false;
	DrawHelper.bDrawGrid = true;
	DrawHelper.GridColorAxis = FColor(70, 70, 70);
	DrawHelper.GridColorMajor = FColor(40, 40, 40);
	DrawHelper.GridColorMinor = FColor(20, 20, 20);
	DrawHelper.PerspectiveGridSize = UE_OLD_HALF_WORLD_MAX1;
	bDrawAxes = false;
}

FSceneInterface* FTimelineViewportClient::GetScene() const
{
	return PreviewScene->GetScene();
}

FLinearColor FTimelineViewportClient::GetBackgroundColor() const
{
	return FLinearColor(0.8f, 0.85f, 0.85f);
}
