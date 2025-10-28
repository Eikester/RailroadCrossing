
#include "MyFGMultipleLaneRCHolo.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "FGSplineBuildableInterface.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGConstructDisqualifier.h"

bool AMyFGMultipleLaneRCHolo::IsValidHitResult(const FHitResult& hitResult) const
{
	return true;
}

void AMyFGMultipleLaneRCHolo::CheckValidPlacement()
{
	Super::CheckValidPlacement();
}

void AMyFGMultipleLaneRCHolo::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	AActor* hitActor = hitResult.GetActor();
	AFGBuildableRailroadTrack* mTrack = Cast<AFGBuildableRailroadTrack>(hitActor);

	if (IsValid(mTrack) && hitActor)
	{
		FVector position = FVector(hitResult.Location.X, hitResult.Location.Y, hitResult.Location.Z);
		position = hitResult.Location.GridSnap(mGridSnapSize);
		FVector offset = FVector(0, 0, 0);

		mPoints.Insert(position, mCurrentStep);

		SetActorLocationAndRotation(position + offset, FVector::ForwardVector.Rotation());
	}
	else
	{
		Super::SetHologramLocationAndRotation(hitResult);
		AddConstructDisqualifier(UFGCDMustHaveRailRoadTrack::StaticClass());
	}
}

bool AMyFGMultipleLaneRCHolo::DoMultiStepPlacement(bool isInputFromARelease)
{
	Super::DoMultiStepPlacement(isInputFromARelease);

	mCurrentStep++;

	return mCurrentStep == mMaxStepCount;
}

void AMyFGMultipleLaneRCHolo::ConfigureComponents(AFGBuildable* inBuildable) const
{
	Super::ConfigureComponents(inBuildable);

	USplineComponent* sc = inBuildable->GetComponentByClass<USplineComponent>();

	if (sc)
	{
		sc->ClearSplinePointsData();

		for (int i = 0; i < 2; i++)
		{
			FSplinePointData data = FSplinePointData();
			data.Location = mPoints[i] - inBuildable->GetActorLocation();

			FVector direction = mPoints[1] - mPoints[0];

			if (i == 0)
			{
				data.ArriveTangent = FVector(0, 0, 0);
				data.LeaveTangent = direction;
			}
			else
			{
				data.ArriveTangent = direction;
				data.LeaveTangent = FVector(0, 0, 0);
			}

			UE_LOG(LogTemp, Warning, TEXT("Point %d, %s"), i, *data.Location.ToString());

			sc->AddSplinePointFromData(data, ESplineCoordinateSpace::Local, true);
		}
	}
}
