// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Libraries/Types.h"
#include "Engine/DataTable.h"
#include "Objects/PickUpObject.h"
#include "JWProjectGameMode.h"
#include "JWProjectCharacter.h"
#include "JWGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JWPROJECT_API UJWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	//Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectSetting")
		UDataTable* ObjectInfoTable = nullptr;

	UFUNCTION(BlueprintCallable)
		bool GetObjectInfoByName(FName ObjectName, FObjectInfo& OutInfo);

};
