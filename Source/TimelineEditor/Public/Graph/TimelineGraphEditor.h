// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "GraphEditor.h"
#include "TimelineAsset.h"

class FTimelineAssetEditor;

class TIMELINEEDITOR_API STimelineGraphEditor : public SGraphEditor
{
public:
	SLATE_BEGIN_ARGS(STimelineGraphEditor)
	{
	}
		
	SLATE_ARGUMENT(TSharedPtr<IDetailsView>, AssetDetailsView)
	SLATE_ARGUMENT(TSharedPtr<IDetailsView>, TrackDetailsView)
	SLATE_END_ARGS()
protected:
	TWeakObjectPtr<UTimelineAsset> TimelineAsset;
	
	TSharedPtr<IDetailsView> AssetDetailsView;
	TSharedPtr<IDetailsView> TrackDetailsView;
	TWeakPtr<FTimelineAssetEditor> TimelineAssetEditor;

	TSharedPtr<FUICommandList> CommandList;
	
public:
	void Construct(const FArguments& InArgs, const TSharedPtr<FTimelineAssetEditor> InAssetEditor);

	virtual void BindGraphCommands();
	
	virtual FGraphAppearanceInfo GetGraphAppearanceInfo() const;
	virtual FText GetCornerText() const;
};
