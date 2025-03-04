// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_PlayTimelineAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimelineWaitSimpleDelegate);

class UTimelineAsset;

/**
 * 
 */
UCLASS()
class TIMELINE_API UAbilityTask_PlayTimelineAndWait : public UAbilityTask
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FTimelineWaitSimpleDelegate	OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FTimelineWaitSimpleDelegate	OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FTimelineWaitSimpleDelegate	OnCancelled;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="PlayTimelineAndWait",
	HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PlayTimelineAndWait* CreatePlayTimepineAndWaitProxy(UGameplayAbility* OwningAbility,
		FName TaskInstanceName, UTimelineAsset* TimelineToPlay, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true);

protected:
	UPROPERTY()
	TObjectPtr<UTimelineAsset> TimelineToPlay;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	bool bStopWhenAbilityEnds;
};
