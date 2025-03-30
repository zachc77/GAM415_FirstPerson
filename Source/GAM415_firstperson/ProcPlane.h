// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

class UProceduralMeshComponent;

UCLASS()
class GAM415_FIRSTPERSON_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// calls create mesh before loading in and playing 
	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		// Array of vectors called Vertices
	UPROPERTY(EditAnywhere)
		TArray<FVector> Vertices;

		//Array of ints called triangles
	UPROPERTY(EditAnywhere)
		TArray<int> Triangles;

		//UV array for applying mat
	UPROPERTY(EditAnywhere)
		TArray<FVector2D> UV0;

	UFUNCTION()
		void CreateMesh();

	UPROPERTY(EditAnywhere)
		UMaterialInterface* PlaneMat;
	
		//
	private:
		UProceduralMeshComponent* procMesh;
};
