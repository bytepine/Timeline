// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Abilities/Tasks/AbilityTask_PlayTimelineAndWait.h"
#include "TimelineAsset.h"
#include "AbilitySystemGlobals.h"

UAbilityTask_PlayTimelineAndWait* UAbilityTask_PlayTimelineAndWait::CreatePlayTimepineAndWaitProxy(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UTimelineAsset* TimelineToPlay, float Rate,
	FName StartSection, bool bStopWhenAbilityEnds)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UAbilityTask_PlayTimelineAndWait* MyObj = NewAbilityTask<UAbilityTask_PlayTimelineAndWait>(OwningAbility, TaskInstanceName);
	MyObj->TimelineToPlay = TimelineToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	
	return MyObj;
}
