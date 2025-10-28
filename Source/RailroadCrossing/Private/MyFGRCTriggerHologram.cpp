


#include "MyFGRCTriggerHologram.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGConstructDisqualifier.h"

bool AMyFGRCTriggerHologram::IsValidHitResult(const FHitResult& hitResult) const
{
	return true;
}

void AMyFGRCTriggerHologram::CheckValidPlacement()
{
	Super::CheckValidPlacement();
}

void AMyFGRCTriggerHologram::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	AActor* hitActor = hitResult.GetActor();
	mTrack = Cast<AFGBuildableRailroadTrack>(hitActor);

	if (IsValid(mTrack) && hitActor)
	{
		FRotator rotator = FRotator(0, (GetScrollRotateValue() / 10 * 180) % 360, 0);
		
		FVector position = FVector(hitResult.Location.X, hitResult.Location.Y, hitResult.Location.Z);
		position = hitResult.Location.GridSnap(mGridSnapSize);
		FVector offset = FVector(0, 0, 200);

		USplineComponent* spline = mTrack->GetSplineComponent();

		FVector splinePointPosition = spline->FindLocationClosestToWorldLocation(position, ESplineCoordinateSpace::World);
		FRotator splinePointRotation = spline->FindRotationClosestToWorldLocation(position, ESplineCoordinateSpace::World);
		
		SetActorLocationAndRotation(splinePointPosition + offset, splinePointRotation.Quaternion() * rotator.Quaternion());
	}
	else
	{
		mTrack = nullptr;
		Super::SetHologramLocationAndRotation(hitResult);

		AddConstructDisqualifier(UFGCDMustHaveRailRoadTrack::StaticClass());
	}
}
