

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticFunctions.generated.h"

/**
 * 
 */
UCLASS()
class RAILROADCROSSING_API UStaticFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void SortByDistance(AActor* source, TArray<AActor*> inArray, TArray<AActor*>& outArray);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void SortByDistanceVector(FVector source, TArray<FVector> inArray, TArray<FVector>& outArray);
};
