// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "EditorViewportClient.h"
#include "SAssetEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FAntAssetEditorToolkit;
class FAdvancedPreviewScene;
class FEditorViewportClient;
class SEditorViewport;

class STimelineAssetEditorViewport : public SAssetEditorViewport, public ICommonEditorViewportToolbarInfoProvider, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(STimelineAssetEditorViewport) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual TSharedRef<SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("STimelineAssetEditorViewport");
	}

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	
private:
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<FEditorViewportClient> EditorViewportClient;
	TWeakPtr<FAntAssetEditorToolkit> AntAssetEditorToolkitPtr;
};

class FTimelineViewportClient : public FEditorViewportClient
{
public:
	FTimelineViewportClient(FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget);

	// FEditorViewportClient interface
	virtual FSceneInterface* GetScene() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	// End of FEditorViewportClient interface
};
