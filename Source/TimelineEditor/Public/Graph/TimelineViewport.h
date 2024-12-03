// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "SEditorViewport.h"

struct FTimelineViewportRequiredArgs
{
};

class STimelineViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(STimelineViewport) 
	{}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FTimelineViewportRequiredArgs& InRequiredArgs);
	virtual ~STimelineViewport() override;

protected:
	// Viewport client
	TSharedPtr<class FTimelineViewportClient> ViewportClient;

	// The preview scene that we are viewing
	TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;
protected:
	
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
};
