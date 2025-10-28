

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "MyFGRCTriggerHologram.generated.h"

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API AMyFGRCTriggerHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
	
	AFGBuildableRailroadTrack* mTrack = nullptr;

	bool IsValidHitResult(const FHitResult& hitResult) const;
	void CheckValidPlacement();
	void SetHologramLocationAndRotation(const FHitResult& hitResult);
};
