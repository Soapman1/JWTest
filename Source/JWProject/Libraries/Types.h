// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Types.generated.h"



UENUM(BlueprintType)
enum class EObjectType : uint8
{
	NoneType UMETA(DispayName = "None"),
	WeaponType UMETA(DisplayName = "Weapon"),
	AmmoType UMETA(DisplayName = "Ammo"),
	ConsumableType UMETA(DisplayName = "Consumables")
	
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	NoneType UMETA(DisplayName = "None"),
	GunType UMETA(DisplayName = "Gun"),
	ShotGunType UMETA(DisplayName = "ShotGun")
};

UENUM(BlueprintType)
enum class EConsumableType : uint8
{
	NoneType UMETA (DispayName = "None"),
	FirstAidType UMETA (DispayName = "FirstAid"),
	SpeedUpType UMETA (DispayName = "SpeedUp")
};

USTRUCT(BlueprintType)
struct FProjectileInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		TSubclassOf<class AJWProjectProjectile> Projectile = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		UStaticMesh* ProjectileStaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		FTransform ProjectileStaticMeshOffset = FTransform();
		


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		float ProjectileDamage = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		float ProjectileLifeTime = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		float ProjectileInitSpeed = 2000.0f;
	//Sound when hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		USoundBase* HitSound = nullptr;

};

USTRUCT(BlueprintType)
struct FInventoryInfo
{
	GENERATED_BODY()

		//Health kit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
		int32 HealthKitCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
		float HealthKitPower = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
		EConsumableType ConsumableType = EConsumableType::FirstAidType;


	//Ammo kit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
		EWeaponType WeaponType = EWeaponType::GunType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
		int32 AmmoKitCount = 0;
};

USTRUCT(BlueprintType)
struct FObjectInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TSubclassOf<class AActor> ObjectClass = nullptr;

	


	//Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float RateOfFire = 0.5f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		int32 NumberProjectileByShot = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ")
		USoundBase* SoundFireWeapon = nullptr;
	
	//Projectile	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile ")
		FProjectileInfo ProjectileSetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace ")
		float WeaponDamage = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace ")
		float DistacneTrace = 2000.0f;
	//one decal on all?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect ")
		UDecalComponent* DecalOnHit = nullptr;

	//Consumable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Type")
		EObjectType ObjectType = EObjectType::ConsumableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FInventoryInfo InventoryItemInfo;

};


USTRUCT(BlueprintType)
struct FAdditionalWeaponInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
		int32 Round = 10;


};



UCLASS()
class JWPROJECT_API UTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
