// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "Toolkits/AssetEditorToolkit.h"

class STimelineAssetEditorViewport;
class FEditorViewportTabContent;
class STimelineGraphEditor;
class UTimelineAsset;
class IDetailsView;

class TIMELINEEDITOR_API FTimelineAssetEditor : public FAssetEditorToolkit, public FEditorUndoClient, public FGCObject, public FNotifyHook
{
public:
	/**	The tab ids for all the tabs used */
	static const FName GraphTab;
	static const FName AssetDetailsTab;
	static const FName TrackDetailsTab;
	static const FName ViewportTab;
public:
	FTimelineAssetEditor();
	virtual ~FTimelineAssetEditor() override;

	UTimelineAsset* GetTimelineAsset() const { return TimelineAsset; }
	
	/** Edits the specified FlowAsset object */
	void InitTimelineAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);

	// FGCObject
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("FTimelineAssetEditor");
	}
	
	// IToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	
	// FAssetEditorToolkit
	virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;
	virtual void PostRegenerateMenusAndToolbars() override;
	virtual void SaveAsset_Execute() override;
	virtual void SaveAssetAs_Execute() override;

protected:
	virtual void CreateToolbar();
	virtual void BindToolbarCommands();
	virtual void CreateWidgets();
	virtual void CreateGraphWidget();

	static bool CanEdit();
private:
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_Graph(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_TrackDetails(const FSpawnTabArgs& Args) const;
	
protected:
	/** The Flow Asset being edited */
	TObjectPtr<UTimelineAsset> TimelineAsset;

	TSharedPtr<IDetailsView> AssetDetailsView;
	TSharedPtr<STimelineAssetEditorViewport> ViewportView;
	TSharedPtr<IDetailsView> TrackDetailsView;
	TSharedPtr<STimelineGraphEditor> GraphEditor;
	TSharedPtr<FEditorViewportTabContent> ViewportTabContent;
};
