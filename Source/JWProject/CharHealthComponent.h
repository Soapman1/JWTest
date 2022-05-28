// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Libraries/Types.h"
#include "CharHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JWPROJECT_API UCharHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharHealthComponent();

	FObjectInfo ObjectInformation;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CharHealth = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCharHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCharHealth(float HealthValue);



	
		
};
