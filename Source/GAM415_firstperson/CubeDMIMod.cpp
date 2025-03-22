// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "GAM415_firstpersonCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating subobject 
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	//Set up attachments Root comp is boxComp and the cube mesh is being attached to the root which is the boxComp
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverLapBegin);

	if (baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMat);
	}
	
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults)
{
	// If other actor is = to first person char then set the insatnce to the player char
	AGAM415_firstpersonCharacter* overlappedActor = Cast<AGAM415_firstpersonCharacter>(OtherActor);

	//If overlapped actor is valid set three float var to a random float and range between 0 1 
	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranOpacity = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f); // Random opacity value

		// set a vector 4 to the random values 
		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);
		if (dmiMat)
		{
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);
			dmiMat->SetScalarParameterValue("Opacity", ranOpacity); // Set opacity parameter

			if (colorP)
			{
				UNiagaraComponent* particalComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

				particalComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor);
			}

		}
	}
}

