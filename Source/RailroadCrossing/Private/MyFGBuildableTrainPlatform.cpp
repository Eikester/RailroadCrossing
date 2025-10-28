


#include "MyFGBuildableTrainPlatform.h"
#include "FGRailroadTrackConnectionComponent.h"
#include <FGRailroadVehicle.h>
#include <FGRailroadFunctionLibrary.h>
#include <Engine.h>
#include <FGTrain.h>
#include "Components/SplineComponent.h"
#include <FGSplineMeshGenerationLibrary.h>

void AMyFGBuildableTrainPlatform::Factory_Tick(float dt)
{
	Super::Factory_Tick(dt);
}

/// <summary>
/// startTrack: the Track from where to get all connected tracks
/// forward: expects 0 or 1 for forward or reverse
/// </summary>
/// <param name="startTrack"></param>
/// <param name="forward"></param>
/// <returns></returns>
TArray<AFGBuildableRailroadTrack*> AMyFGBuildableTrainPlatform::GetConnectedTracksInDirection(AFGBuildableRailroadTrack* startTrack, int forward, float distance)
{
	TArray<AFGBuildableRailroadTrack*> temp;
	UFGRailroadTrackConnectionComponent* currentConnection;

	// add the starting track to the array
	temp.Add(startTrack);

	// get the next track
	currentConnection = startTrack->GetConnection(forward)->GetNext();

	AddTrack(temp, currentConnection, mDistance);

	return temp;
}

void AMyFGBuildableTrainPlatform::AddTrack(TArray<AFGBuildableRailroadTrack*>& tracks, UFGRailroadTrackConnectionComponent* connection, float remainingDistance)
{
	if(remainingDistance > 0 && connection)
	{
		TArray< UFGRailroadTrackConnectionComponent*> connections = connection->GetConnections();
	
		for (int i = 0; i < connections.Num(); i++)
		{
			AFGBuildableRailroadTrack* track = connections[i]->GetTrack();
			FRailroadTrackPosition trackPosition = connections[i]->GetTrackPosition();

			if (trackPosition.IsValid())
			{
				UFGRailroadTrackConnectionComponent* forward = trackPosition.GetForwardConnection();

				if (forward)
				{
					track = forward->GetTrack();

					if (!tracks.Contains(track))
					{
						float rd = remainingDistance - track->GetLength();

						tracks.Add(track);
						AddTrack(tracks, forward, rd);
					}
				}
			}
		}
	}
}

void AMyFGBuildableTrainPlatform::GetConnectedTracks(AFGBuildableRailroadTrack* startTrack, TArray<AFGBuildableRailroadTrack*>& outForwardConnectedTracks, TArray<AFGBuildableRailroadTrack*>& outReverseConnectedTracks)
{
	outForwardConnectedTracks = GetConnectedTracksInDirection(startTrack, 0, mDistance);
	outReverseConnectedTracks = GetConnectedTracksInDirection(startTrack, 1, mDistance);
}


