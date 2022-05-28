// Copyright Epic Games, Inc. All Rights Reserved.

#include "JWProjectGameMode.h"
#include "JWProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "JWGameInstance.h"
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

	
}

void AJWProjectGameMode::TimerToSpawn()
{
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AJWProjectGameMode::SpawnActorAfterDeath, 1.0f, false, 2.0f);
	
	//ADD DEATH WIDGET

	
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
		
	}
	
	
}



