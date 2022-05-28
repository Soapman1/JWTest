// Copyright Epic Games, Inc. All Rights Reserved.

#include "JWProjectCharacter.h"
#include "JWProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "JWGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AJWProjectCharacter

AJWProjectCharacter::AJWProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	
	// Create bullet location
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FirstPersonCameraComponent);
	FP_MuzzleLocation->SetRelativeLocation(FVector(108.0f, 11.0f, -24.0f));
	FP_MuzzleLocation->SetRelativeRotation(FRotator(25.0f, -21.0f, -2.0f));

	//Event begin overlap	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AJWProjectCharacter::BeginOverlap);

	CharHealthComponent = CreateDefaultSubobject<UCharHealthComponent>(TEXT("CharHealth"));
	CharHealthComponent->GetOwner()->AddOwnedComponent(CharHealthComponent);

}


void AJWProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	
	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	
	Mesh1P->SetHiddenInGame(false, true);

	if(CharHealthComponent)
		CharHealthComponent->SetCharHealth(100.0f);

	

}


void AJWProjectCharacter::Destroyed()
{
	Super::Destroyed();

		
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Actor was destroyed")));
	AJWProjectGameMode* myGM = Cast <AJWProjectGameMode>(UGameplayStatics::GetGameMode(this));
	if (myGM)
	{
		myGM->TimerToSpawn();
	}

			
}




//////////////////////////////////////////////////////////////////////////
// Input




void AJWProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJWProjectCharacter::OnFire);

	
	
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AJWProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJWProjectCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJWProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJWProjectCharacter::LookUpAtRate);
}

void AJWProjectCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ObjectByPick = Cast <APickUpObject>(OtherActor);
		if (ObjectByPick)
		{
		CheckObject(ObjectByPick->ObjectType, ObjectByPick->WeaponType, ObjectByPick->ConsumableType, ObjectByPick->ObjectName);
		}
		
	}
}





//Init weapon in hands
void AJWProjectCharacter::InitWeapon(EWeaponType WeaponType, FName ObjectName)
{

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	UJWGameInstance* myGI = Cast <UJWGameInstance> (GetGameInstance());
	

	if (myGI)
	{
		if (myGI->GetObjectInfoByName(ObjectName, ObjectInfo))
		{
			if (ObjectInfo.ObjectClass)
			{
				FVector SpawnLocation = FVector(0);
				FRotator SpawnRotation = FRotator(0);

				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				SpawnParams.Owner = GetOwner();
				SpawnParams.Instigator = GetInstigator();

				
				APickUpObject* myWeapon = Cast <APickUpObject>(GetWorld()->SpawnActor(ObjectInfo.ObjectClass, &SpawnLocation, &SpawnRotation, SpawnParams));
				if (myWeapon)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("myWeapon - %s"), *myWeapon->GetName()));
					FAttachmentTransformRules Rule(EAttachmentRule::SnapToTarget, false);
					myWeapon->AttachToComponent(Mesh1P, Rule, FName("RightSocket"));
					CurrentWeapon = myWeapon;
					bCanFire = true;

					
				}
				
			}
			
		}
		else
		{
			//Debug message
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("InitWeapon - Weapon not found in table -NULL"));
			//UE_LOG(LogTemp, Warning, TEXT("ATPSCharacter::InitWeapon - Weapon not found in table -NULL"));
		}
	}

	
}

void AJWProjectCharacter::InitConsumable(EConsumableType ConsumableType, FName ObjectName)
{
	UJWGameInstance* myGI = Cast <UJWGameInstance>(GetGameInstance());

	if (myGI)
	{
		if (myGI->GetObjectInfoByName(ObjectName, ObjectInfo))
		{
			if (ObjectInfo.ObjectClass)
			{
				switch (ConsumableType)
				{
				case EConsumableType::FirstAidType:
					CharHealthComponent->SetCharHealth(CharHealthComponent->GetCharHealth() + ObjectInfo.InventoryItemInfo.HealthKitPower);
					if (CharHealthComponent->GetCharHealth() > 100.f)
						CharHealthComponent->SetCharHealth(100.0f);
					break;
				case EConsumableType::SpeedUpType:
					SprintStart(ObjectInfo.InventoryItemInfo.SpeedUpPower);
					GetWorldTimerManager().SetTimer(TimerHandle, this, &AJWProjectCharacter::SprintEnd, ObjectInfo.InventoryItemInfo.SpeedPowerTime, false, 2.0f);
				default:
					break;
				}
			}
		}
	}

}

float AJWProjectCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	
	CharHealthComponent->SetCharHealth(CharHealthComponent->GetCharHealth() - DamageAmount);

	if (CharHealthComponent->GetCharHealth() == -0.1f || CharHealthComponent->GetCharHealth() == 0.1f)
	{
		this->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Life is = %f"), CharHealthComponent->GetCharHealth()));
	}
	

	if ((CharHealthComponent->GetCharHealth()) < 0.0f)
	{
		CharHealthComponent->SetCharHealth(0.0f);
	}
	

	return DamageAmount;
}

void AJWProjectCharacter::RespawnCharacter()
{
	//Respawn Logic
	//Look in GM

}

void AJWProjectCharacter::RespawnCharacter_BP_Implementation(UAnimMontage* Anim)
{
	//in BP
}

void AJWProjectCharacter::OnFire()
{
	if (bCanFire)
	{
		// try and fire a projectile
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AJWProjectProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			}

			FHitResult HitResult;

			if (HitResult.GetActor())
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), ObjectInfo.WeaponDamage , GetInstigatorController(), this, NULL);
			}

		}

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}


	}
	
	
}


void AJWProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AJWProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AJWProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJWProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJWProjectCharacter::SprintStart(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * Value;
}

void AJWProjectCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}


//Check overlapped object
void AJWProjectCharacter::CheckObject(EObjectType ObjectType, EWeaponType WeaponType, EConsumableType ConsumableType, FName ObjectName)
{
	switch (ObjectType)
	{
	case EObjectType::WeaponType:
	{
		InitWeapon(WeaponType, ObjectName);
		break;
	}
	case EObjectType::ConsumableType:
	{
		// add to inventory or immediately add to char
		InitConsumable(ConsumableType, ObjectName);
		break;
	}
	case EObjectType::AmmoType:
	{
		// add to inventory or immediately add to char
		break;
	}
	default:
		break;

	}
}


