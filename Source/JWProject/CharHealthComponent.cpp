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


	CharHealth = 100.0f;
	// ...
}


// Called when the game starts
void UCharHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCharHealthComponent::TakeDamage);

	AJWProjectCharacter* ProjChar = Cast <AJWProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	

	if (GetOwner() == ProjChar)
	{
		ProjChar->SendObjectInfo.AddDynamic(this, &UCharHealthComponent::UseObjectInfo); // Delegate func name??? 
	}
}


// Called every frame
void UCharHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	
	AJWProjectCharacter* MyChar = Cast <AJWProjectCharacter>(DamagedActor);

	CharHealth -= Damage;

	
	if (MyChar)
	{
		if (CharHealth < 0.0f)
		{
			CharHealth = 0.0f;
		}

		if (CharHealth == 0.0f )
		{
			MyChar->Destroy();
		}
	}
}

void UCharHealthComponent::UseObjectInfo(FObjectInfo ObjectInfo)
{
	CharHealth += ObjectInfo.InventoryItemInfo.HealthKitPower;
	if (CharHealth > 100.0f)
	{
		CharHealth = 100.0f;
	}
}


