// Fill out your copyright notice in the Description page of Project Settings.


#include "CharHealthComponent.h"
#include "JWProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharHealthComponent::UCharHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	
	// ...
}


// Called when the game starts
void UCharHealthComponent::BeginPlay()
{
	Super::BeginPlay();

			
}


// Called every frame
void UCharHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UCharHealthComponent::GetCharHealth()
{
	return CharHealth;
}

void UCharHealthComponent::SetCharHealth(float HealthValue)
{
	CharHealth = HealthValue;
}



