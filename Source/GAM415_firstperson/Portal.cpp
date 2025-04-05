// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "GAM415_firstpersonCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");

	//to change the spawning from tp
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	//make box comp root comp
	RootComponent = boxComp;
	// attach mesh to boxcomp
	mesh->SetupAttachment(boxComp);
	//attach scenecapture to mesh
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// disable coll for mesh
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	//
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);
	//
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool BFromSweep, const FHitResult& SweepResults)
{
	//cast to player char?
	AGAM415_firstpersonCharacter* playerChar = Cast<AGAM415_firstpersonCharacter>(OtherActor);
	
	// if cast to playerchar is valid
	if (playerChar)
	{
		if (OtherPortal)
		{
			//if is teleporting is false 
			if (!playerChar->isTeleporting)
			{
				//set isteleporting to true 
				playerChar->isTeleporting = true;
				//get loc of other portal
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				//set player loc to the other loc
				playerChar->SetActorLocation(loc);

				// set timer to so we can set teleporting to flase so teleporting is allowed again
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);

			}
		}
	}
}

void APortal::SetBool(AGAM415_firstpersonCharacter* playerChar)
{
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

