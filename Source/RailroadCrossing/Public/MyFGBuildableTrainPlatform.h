

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableTrainPlatform.h"
#include "MyFGBuildableTrainPlatform.generated.h"

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API AMyFGBuildableTrainPlatform : public AFGBuildableTrainPlatform
{
	GENERATED_BODY()
	
public:
	virtual void Factory_Tick(float dt) override;

	UPROPERTY(BlueprintReadWrite, Category = "Railroad Crossing")
	float mDistance = 12000; // one foundation is 800cm so this would be 15 Foundations or 10 Traintracks at min Length

	TArray< AFGBuildableRailroadTrack*> GetConnectedTracksInDirection(AFGBuildableRailroadTrack* startTrack, int forward, float distance);
	void AddTrack(TArray<AFGBuildableRailroadTrack*>& tracks, UFGRailroadTrackConnectionComponent* connection, float remainingDistance);

	UFUNCTION(BlueprintCallable, Category = "Railroad Crossing")
	void GetConnectedTracks(AFGBuildableRailroadTrack* startTrack, TArray<AFGBuildableRailroadTrack*> &outForwardConnectedTracks, TArray<AFGBuildableRailroadTrack*> &outReverseConnectedTRacks);
};
