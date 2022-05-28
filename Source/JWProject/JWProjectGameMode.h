// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JWProjectGameMode.generated.h"

UCLASS(minimalapi)
class AJWProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

	
public:
	AJWProjectGameMode();

	
	FTimerHandle TimerHandle;

	UFUNCTION()
		void TimerToSpawn();

	UFUNCTION()
		void SpawnActorAfterDeath();

	

	
};



