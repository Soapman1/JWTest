// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JWProjectCharacter.h"
#include "JWProjectGameMode.generated.h"

UCLASS(minimalapi)
class AJWProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

public:
	AJWProjectGameMode();

	TSubclassOf <APawn> CharacterBP;

	FTimerHandle TimerHandle;

	UFUNCTION()
		void TimerToSpawn(AJWProjectCharacter* DeathChar);

	UFUNCTION()
		void SpawnActorAfterDeath();

	

	
};



