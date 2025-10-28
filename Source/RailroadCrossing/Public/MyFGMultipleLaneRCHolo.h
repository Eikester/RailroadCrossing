

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "MyFGMultipleLaneRCHolo.generated.h"

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API AMyFGMultipleLaneRCHolo : public AFGBuildableHologram
{
	GENERATED_BODY()
	
	int mMaxStepCount = 2;
	int mCurrentStep = 0;

	TArray<FVector> mPoints;

	bool IsValidHitResult(const FHitResult& hitResult) const;
	void CheckValidPlacement();
	void SetHologramLocationAndRotation(const FHitResult& hitResult);
	bool DoMultiStepPlacement(bool isInputFromARelease);
	virtual void ConfigureComponents(class AFGBuildable* inBuildable) const;
};
