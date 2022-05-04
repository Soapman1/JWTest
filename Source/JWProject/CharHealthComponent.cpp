// Fill out your copyright notice in the Description page of Project Settings.


#include "CharHealthComponent.h"

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

	// ...
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCharHealthComponent::TakeDamage);
}


// Called every frame
void UCharHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	CharHealth -= Damage;
}


