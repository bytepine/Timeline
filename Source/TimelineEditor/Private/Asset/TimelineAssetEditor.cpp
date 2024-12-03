// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "Asset/TimelineAssetEditor.h"
#include "EditorViewportTabContent.h"
#include "Graph/TimelineGraphEditor.h"
#include "TimelineAsset.h"
#include "Graph/TimelineViewportClient.h"

#define LOCTEXT_NAMESPACE "TimelineAssetEditor"

const FName FTimelineAssetEditor::GraphTab(TEXT("Graph"));
const FName FTimelineAssetEditor::AssetDetailsTab(TEXT("AssetDetails"));
const FName FTimelineAssetEditor::TrackDetailsTab(TEXT("TrackDetails"));
const FName FTimelineAssetEditor::ViewportTab(TEXT("Viewport"));

FTimelineAssetEditor::FTimelineAssetEditor()
	: TimelineAsset(nullptr)
{
	
}

FTimelineAssetEditor::~FTimelineAssetEditor()
{
	GEditor->UnregisterForUndo(this);
}

void FTimelineAssetEditor::InitTimelineAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
	TimelineAsset = CastChecked<UTimelineAsset>(ObjectToEdit);
	
	// Support undo/redo
	TimelineAsset->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	BindToolbarCommands();
	CreateToolbar();
	CreateWidgets();
	
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("TimelineAssetEditor_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.15f)
			->AddTab(AssetDetailsTab, ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.7f)
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.6f)
				->SetHideTabWell(true)
				->AddTab(ViewportTab, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.4f)
				->SetHideTabWell(true)
				->AddTab(GraphTab, ETabState::OpenedTab)
			)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.15f)
			->AddTab(TrackDetailsTab, ETabState::OpenedTab)
		)
	);
	
	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, TEXT("TimelineEditorApp"), StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, ObjectToEdit, false);

	RegenerateMenusAndToolbars();
}

void FTimelineAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(TimelineAsset);
}

FName FTimelineAssetEditor::GetToolkitFName() const
{
	return FName("TimelineEditor");
}

FText FTimelineAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "TimelineAsset Editor");
}

FString FTimelineAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "TimelineAsset").ToString();
}

FLinearColor FTimelineAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FTimelineAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_TimelineAssetEditor", "Timeline Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(ViewportTab, FOnSpawnTab::CreateSP(this, &FTimelineAssetEditor::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));
	
	InTabManager->RegisterTabSpawner(GraphTab, FOnSpawnTab::CreateSP(this, &FTimelineAssetEditor::SpawnTab_Graph))
			.SetDisplayName(LOCTEXT("GraphTab", "Graph"))
			.SetGroup(WorkspaceMenuCategoryRef)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));
	
	InTabManager->RegisterTabSpawner(AssetDetailsTab, FOnSpawnTab::CreateSP(this, &FTimelineAssetEditor::SpawnTab_AssetDetails))
			.SetDisplayName(LOCTEXT("AssetDetailsTab", "AssetDetails"))
			.SetGroup(WorkspaceMenuCategoryRef)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(TrackDetailsTab, FOnSpawnTab::CreateSP(this, &FTimelineAssetEditor::SpawnTab_TrackDetails))
			.SetDisplayName(LOCTEXT("TrackDetailsTab", "TrackDetails"))
			.SetGroup(WorkspaceMenuCategoryRef)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FTimelineAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(ViewportTab);
	InTabManager->UnregisterTabSpawner(GraphTab);
	InTabManager->UnregisterTabSpawner(AssetDetailsTab);
	InTabManager->UnregisterTabSpawner(TrackDetailsTab);
}

void FTimelineAssetEditor::InitToolMenuContext(FToolMenuContext& MenuContext)
{
	FAssetEditorToolkit::InitToolMenuContext(MenuContext);
}

void FTimelineAssetEditor::PostRegenerateMenusAndToolbars()
{
	
}

void FTimelineAssetEditor::SaveAsset_Execute()
{
	FAssetEditorToolkit::SaveAsset_Execute();
}

void FTimelineAssetEditor::SaveAssetAs_Execute()
{
	FAssetEditorToolkit::SaveAssetAs_Execute();
}

void FTimelineAssetEditor::CreateToolbar()
{
	
}

void FTimelineAssetEditor::BindToolbarCommands()
{
	
}

void FTimelineAssetEditor::CreateWidgets()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	// AssetDetails View
	{
		FDetailsViewArgs AssetDetailsArgs;
		AssetDetailsArgs.bHideSelectionTip = true;
		AssetDetailsArgs.bShowPropertyMatrixButton = false;
		AssetDetailsArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
		AssetDetailsArgs.NotifyHook = this;
		
		AssetDetailsView = PropertyModule.CreateDetailView(AssetDetailsArgs);
		AssetDetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateStatic(&FTimelineAssetEditor::CanEdit));
		AssetDetailsView->SetObject(TimelineAsset);
	}

	// TrackDetails View
	{
		FDetailsViewArgs TrackDetailsArgs;
		TrackDetailsArgs.bHideSelectionTip = true;
		TrackDetailsArgs.bShowPropertyMatrixButton = false;
		TrackDetailsArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Show;
		TrackDetailsArgs.NotifyHook = this;

		TrackDetailsView = PropertyModule.CreateDetailView(TrackDetailsArgs);
		TrackDetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateStatic(&FTimelineAssetEditor::CanEdit));
	}
	
	// Graph
	CreateGraphWidget();
	// GraphEditor->OnSelectionChangedEvent.BindRaw(this, &FFlowAssetEditor::OnSelectedNodesChanged);
}

void FTimelineAssetEditor::CreateGraphWidget()
{
	SAssignNew(GraphEditor, STimelineGraphEditor, SharedThis(this))
		.AssetDetailsView(AssetDetailsView)
		.TrackDetailsView(TrackDetailsView);

	ViewportView = SNew(STimelineAssetEditorViewport);
}

bool FTimelineAssetEditor::CanEdit()
{
	return GEditor->PlayWorld == nullptr;
}

TSharedRef<SDockTab> FTimelineAssetEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == ViewportTab);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("Viewport", "Viewport"));

	if (ViewportView.IsValid())
	{
		SpawnedTab->SetContent(ViewportView.ToSharedRef());
	}
	
	return SpawnedTab;
}

TSharedRef<SDockTab> FTimelineAssetEditor::SpawnTab_Graph(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == GraphTab);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("Graph", "Graph"));

	if (GraphEditor.IsValid())
	{
		SpawnedTab->SetContent(GraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FTimelineAssetEditor::SpawnTab_AssetDetails(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == AssetDetailsTab);

	return SNew(SDockTab)
		.Label(LOCTEXT("AssetDetails", "AssetDetails"))
		[
			AssetDetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FTimelineAssetEditor::SpawnTab_TrackDetails(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == TrackDetailsTab);

	return SNew(SDockTab)
		.Label(LOCTEXT("TrackDetails", "TrackDetails"))
		[
			TrackDetailsView.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE
