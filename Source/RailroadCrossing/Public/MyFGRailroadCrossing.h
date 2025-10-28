

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableTrainPlatform.h"
#include "MyFGRailroadCrossing.generated.h"

USTRUCT(BlueprintType)
struct FTrackConnection
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	AFGBuildableRailroadTrack* track;
	UPROPERTY(BlueprintReadWrite)
	UFGRailroadTrackConnectionComponent* comingFromConnection;

	bool operator==(const FTrackConnection& other) const
	{
		return this->track == other.track;
	}
};

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API AMyFGRailroadCrossing : public AFGBuildableTrainPlatform
{
	GENERATED_BODY()
	
	virtual void Factory_Tick(float dt) override;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Railroad Crossing")
	float mDistance = 12000; // one foundation is 800cm so this would be 15 Foundations or 10 Traintracks at min Length

	TArray<FTrackConnection> GetConnectedTracksInDirection(AFGBuildableRailroadTrack* startTrack, int forward, float distance);
	void AddTrack(TArray<FTrackConnection>& tracks, UFGRailroadTrackConnectionComponent* connection, float remainingDistance);

	UFUNCTION(BlueprintCallable, Category = "Railroad Crossing")
	void GetConnectedTracks(AFGBuildableRailroadTrack* startTrack, TArray<FTrackConnection>& outForwardConnectedTracks, TArray<FTrackConnection>& outReverseConnectedTRacks);

	UFUNCTION(BlueprintCallable, Category = "Railroad Crossing")
	void ShowTrackVisualization(AFGBuildableRailroadTrack* track);

	UFUNCTION(BlueprintCallable, Category = "Railroad Crossing")
	void HideTrackVisualization(AFGBuildableRailroadTrack* track);
};
