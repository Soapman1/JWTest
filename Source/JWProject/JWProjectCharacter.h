// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Libraries/Types.h"
#include "Objects/PickUpObject.h"
#include "CharHealthComponent.h"
//#include "JWProjectGameMode.h"
#include "JWProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendObjectInfo, FObjectInfo, ObjectInfo, EConsumableType, ConsumableName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDestroyedActor, AJWProjectCharacter*, DeathActor);

UCLASS(config=Game)
class AJWProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	

	
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	

	

public:
	AJWProjectCharacter();

	UPROPERTY(EditAnywhere, Category = "PickUpObject")
		APickUpObject* ObjectByPick;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		APickUpObject* CurrentWeapon;

	FSendObjectInfo SendObjectInfo;
	FDestroyedActor ActorWasDestroy;
	FTimerHandle TimerHandle;
	
		

protected:
	virtual void BeginPlay();
	
	void Destroyed() override;

	

public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		UCharHealthComponent* CharHealthComponent;

	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		FVector GunOffset;

	
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
		TSubclassOf<class AJWProjectProjectile> ProjectileClass;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		USoundBase* FireSound;

	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
		bool bCanFire = false;

	UPROPERTY()
		FObjectInfo ObjectInfo;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		UAnimMontage* DeathAnim = nullptr;

		
	UFUNCTION()
		void InitWeapon(EWeaponType WeaponType, FName ObjectName);

	UFUNCTION()
		void InitConsumable(EConsumableType ConsumableType, FName ObjectName);

	UFUNCTION()
		float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
		void RespawnCharacter();

	UFUNCTION(BlueprintNativeEvent)
		void RespawnCharacter_BP(UAnimMontage* Anim);


protected:
	
	/** Fires a projectile. */
	void OnFire();

	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
		void CheckObject(EObjectType ObjectType, EWeaponType WeaponType, EConsumableType ConsumableType,  FName ObjectName);

	UFUNCTION(BlueprintCallable)
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
	UFUNCTION()
		void SprintStart(float Value);

	UFUNCTION()
		void SprintEnd();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface



public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

