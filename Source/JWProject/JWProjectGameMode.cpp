// Copyright Epic Games, Inc. All Rights Reserved.

#include "JWProjectGameMode.h"
#include "JWProjectHUD.h"
#include "CharHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharHealthComponent.h"

#include "UObject/ConstructorHelpers.h"

AJWProjectGameMode::AJWProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Player/BP_JWProjectCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	

	// use our custom HUD class
	HUDClass = AJWProjectHUD::StaticClass();

	

}

void AJWProjectGameMode::BeginPlay()
{
	Super:: BeginPlay();

	AJWProjectCharacter* ProjChar = Cast <AJWProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (ProjChar)
	{
		ProjChar->ActorWasDestroy.AddDynamic(this, &AJWProjectGameMode::TimerToSpawn);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("ProjChar is NOT NULL")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("ProjChar is NULL")));

	

}

void AJWProjectGameMode::TimerToSpawn(AJWProjectCharacter* DeathChar)
{
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AJWProjectGameMode::SpawnActorAfterDeath, 1.0f, false, 2.0f);
	
	//ADD DEATH WIDGET

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Timer was started")));
}

void AJWProjectGameMode::SpawnActorAfterDeath()
{
	FTransform Transform;
	FVector Location(483.0f, -99.0f, 235.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	

	
	if (DefaultPawnClass != NULL)
	{
		AJWProjectCharacter* SpawnedActor = GetWorld()->SpawnActor<AJWProjectCharacter>(DefaultPawnClass, Location, Rotation, SpawnParams);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(SpawnedActor);
		//SpawnedActor->CharHealthComponent->CharHealth = 100.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health  = %d"),SpawnedActor->CharHealthComponent->CharHealth));
	}
	//ADD HEALTH AFTER SPAWN
	
	 
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Actor was spawned")));

}



