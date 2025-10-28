

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "MyFGRailroadCrossingTrigger.generated.h"

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API AMyFGRailroadCrossingTrigger : public AFGBuildableFactory
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Railroad Crossing Trigger")
	bool IsRailroadCrossingOnPath(AMyFGBuildableTrainPlatform* RailroadCrossing, AFGTrain* train);
};
