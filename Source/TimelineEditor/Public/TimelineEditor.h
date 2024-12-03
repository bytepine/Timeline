#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"
#include "IAssetTypeActions.h"

class FTimelineAssetEditor;
class UTimelineAsset;

class FTimelineEditorModule : public IModuleInterface
{
public:
    static EAssetTypeCategories::Type TimelineAssetCategory;
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
private:
    void RegisterAssets();
    void UnregisterAssets();

public:
private:
    TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetActions;
public:
public:
    static TSharedRef<FTimelineAssetEditor> CreateFlowAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UTimelineAsset* TimelineAsset);
};
