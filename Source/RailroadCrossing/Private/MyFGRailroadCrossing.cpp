


#include "MyFGRailroadCrossing.h"
#include "FGRailroadTrackConnectionComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "FGTrainPlatformConnection.h"

AMyFGRailroadCrossing::AMyFGRailroadCrossing() : Super()
{
	this->mRailroadTrack = nullptr;

	if (this->mPlatformConnection0 == nullptr)
	{
		this->mPlatformConnection0 = CreateDefaultSubobject<UFGTrainPlatformConnection>(TEXT("PlatformConnection0"));
		this->mPlatformConnection0->SetMobility(EComponentMobility::Static);
	}
	this->mPlatformConnections.Add(mPlatformConnection0);

	if (this->mPlatformConnection1 == nullptr)
	{
		this->mPlatformConnection1 = CreateDefaultSubobject<UFGTrainPlatformConnection>(TEXT("PlatformConnection1"));
		this->mPlatformConnection1->SetMobility(EComponentMobility::Static);
	}
	this->mPlatformConnections.Add(mPlatformConnection1);


	this->mPlatformConnection0->SetupAttachment(RootComponent);
	this->mPlatformConnection1->SetupAttachment(RootComponent);
}

/// <summary>
/// startTrack: the Track from where to get all connected tracks
/// forward: expects 0 or 1 for forward or reverse
/// </summary>
/// <param name="startTrack"></param>
/// <param name="forward"></param>
/// <returns></returns>
TArray<FTrackConnection> AMyFGRailroadCrossing::GetConnectedTracksInDirection(AFGBuildableRailroadTrack* startTrack, int forward, float distance)
{
	TArray<FTrackConnection> temp;
	UFGRailroadTrackConnectionComponent* currentConnection = startTrack->GetConnection(forward);

	FTrackConnection trackConnection;
	trackConnection.track = startTrack;
	trackConnection.comingFromConnection = currentConnection;

	// add the starting track to the array
	//temp.Add(trackConnection);

	AddTrack(temp, currentConnection, mDistance);

	return temp;
}

void AMyFGRailroadCrossing::AddTrack(TArray<FTrackConnection>& tracks, UFGRailroadTrackConnectionComponent* connection, float remainingDistance)
{
	if (remainingDistance > 0 && connection)
	{
		TArray< UFGRailroadTrackConnectionComponent*> connections = connection->GetConnections();

		for (int i = 0; i < connections.Num(); i++)
		{
			FRailroadTrackPosition trackPosition = connections[i]->GetTrackPosition();

			if (trackPosition.IsValid())
			{
				UFGRailroadTrackConnectionComponent* forward = trackPosition.GetForwardConnection();

				if (forward)
				{
					AFGBuildableRailroadTrack* track = forward->GetTrack();
					
					FTrackConnection trackConnection;
					trackConnection.track = track;
					trackConnection.comingFromConnection = connections[i];

					if (!tracks.Contains(trackConnection))
					{
						float rd = remainingDistance - track->GetLength();

						tracks.Add(trackConnection);
						AddTrack(tracks, forward, rd);
					}
				}
			}
		}
	}
}

void AMyFGRailroadCrossing::GetConnectedTracks(AFGBuildableRailroadTrack* startTrack, TArray<FTrackConnection>& outForwardConnectedTracks, TArray<FTrackConnection>& outReverseConnectedTracks)
{
	outForwardConnectedTracks = GetConnectedTracksInDirection(startTrack, 0, mDistance);
	outReverseConnectedTracks = GetConnectedTracksInDirection(startTrack, 1, mDistance);
}

void AMyFGRailroadCrossing::BeginPlay()
{
	Super::BeginPlay();
}

void AMyFGRailroadCrossing::Factory_Tick(float dt)
{
	Super::Factory_Tick(dt);
}

void AMyFGRailroadCrossing::SetupRailroadTrack()
{
	Super::SetupRailroadTrack();
}

void AMyFGRailroadCrossing::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMyFGRailroadCrossing::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion)
{
	Super::PreSaveGame_Implementation(saveVersion, gameVersion);
}

void AMyFGRailroadCrossing::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion)
{
	Super::PostLoadGame_Implementation(saveVersion, gameVersion);
}

void AMyFGRailroadCrossing::ShowTrackVisualization(AFGBuildableRailroadTrack* track)
{
	track->ShowBlockVisualization();
}

void AMyFGRailroadCrossing::HideTrackVisualization(AFGBuildableRailroadTrack* track)
{
	track->StopBlockVisualization();
}
