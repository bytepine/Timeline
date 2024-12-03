// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Asset/TimelineAssetFactory.h"
#include "TimelineAsset.h"

UTimelineAssetFactory::UTimelineAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UTimelineAsset::StaticClass();
	
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

bool UTimelineAssetFactory::ConfigureProperties()
{
	return Super::ConfigureProperties();
}

UObject* UTimelineAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UTimelineAsset* NewTimelineAsset = NewObject<UTimelineAsset>(InParent, Class, Name, Flags | RF_Transactional, Context);
	
	return NewTimelineAsset;
}
