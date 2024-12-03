// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
#include "TimelineAssetFactory.generated.h"

/**
 * 
 */
UCLASS(HideCategories = Object)
class TIMELINEEDITOR_API UTimelineAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
