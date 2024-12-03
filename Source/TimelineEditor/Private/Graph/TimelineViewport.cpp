#include "Graph/TimelineViewport.h"

#include "Graph/TimelineViewportClient.h"

void STimelineViewport::Construct(const FArguments& InArgs, const FTimelineViewportRequiredArgs& InRequiredArgs)
{
	
}

STimelineViewport::~STimelineViewport()
{
	SEditorViewport::Construct(
	SEditorViewport::FArguments()
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.AddMetaData<FTagMetaData>(TEXT("Timeline.Viewport"))
	);
}

TSharedRef<FEditorViewportClient> STimelineViewport::MakeEditorViewportClient()
{
	// ViewportClient = MakeShareable(new FTimelineViewportClient(PreviewScenePtr.Pin().ToSharedRef()));

	return ViewportClient.ToSharedRef();
}
