


#include "StaticFunctions.h"

void UStaticFunctions::SortByDistance(AActor* source, TArray<AActor*> inArray, TArray<AActor*>& outArray)
{
	inArray.Sort([source](const AActor& A, const AActor& B)
		{
			float distanceA = A.GetDistanceTo(source);
			float distanceB = B.GetDistanceTo(source);

			return distanceA > distanceB;
		});

	outArray = inArray;
}

void UStaticFunctions::SortByDistanceVector(FVector source, TArray<FVector> inArray, TArray<FVector>& outArray)
{
	inArray.Sort([source](const FVector& A, const FVector& B)
		{
			float distanceA = FVector::Distance(source, A);
			float distanceB = FVector::Distance(source, B);

			return distanceA < distanceB;
		});

	outArray = inArray;
}
