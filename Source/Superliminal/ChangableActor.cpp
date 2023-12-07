// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangableActor.h"

// Sets default values
AChangableActor::AChangableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChangableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChangableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChangableActor::GetMeshPoints()
{
	MeshPoints.Empty();
	if (StaticMeshComponent)
	{
		UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
		if (StaticMeshComponent->GetStaticMesh()->RenderData)
		{
			if (StaticMeshComponent->GetStaticMesh()->RenderData->LODResources.Num() > 0)
			{
				FPositionVertexBuffer* VertexBuffer = &StaticMesh->RenderData->LODResources[0].VertexBuffers.
					PositionVertexBuffer;
				if (VertexBuffer)
				{
					const int32 VertexCount = VertexBuffer->GetNumVertices();
					for (int32 index = 0; index < VertexCount; index++)
					{
						const FVector worldSpaceVertexLocation = GetActorLocation() + GetTransform().TransformVector(
							VertexBuffer->VertexPosition(index));
						MeshPoints.Add(worldSpaceVertexLocation);
					}
				}
			}
		}
	}
}
