// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TimelineAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, hideCategories = Object)
class TIMELINE_API UTimelineAsset : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayRate;
};
