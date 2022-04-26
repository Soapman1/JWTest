// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "JWProject/Libraries/Types.h"
#include "PickUpObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPickedObject, EObjectType, ObjectType, EWeaponType, WeaponType, FName, ObjectName);

UCLASS()
class JWPROJECT_API APickUpObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FPickedObject PickedObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		bool bIsPickable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		FName ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Type")
		EObjectType ObjectType = EObjectType::WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Type")
		EWeaponType WeaponType = EWeaponType::GunType;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxCollision")
		UBoxComponent* BoxCollision;

	UFUNCTION(BlueprintCallable)
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
