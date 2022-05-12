// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpObject.h"

// Sets default values
APickUpObject::APickUpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetGenerateOverlapEvents(false);
	BoxCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUpObject::OnOverlapBegin);
	BoxCollision->SetupAttachment(StaticMesh);

	


}

// Called when the game starts or when spawned
void APickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (bIsPickable)
	{
		BoxCollision->SetGenerateOverlapEvents(true);
		
	}


	if (SkeletalMesh && !SkeletalMesh->SkeletalMesh)
	{
		SkeletalMesh->DestroyComponent(true);
	}

	if (StaticMesh && !StaticMesh->GetStaticMesh())
	{
		StaticMesh->DestroyComponent();
	}
}

// Called every frame
void APickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
		PickedObject.Broadcast(ObjectType, WeaponType, ConsumableType, ObjectName);
		Destroy();

	}
}

