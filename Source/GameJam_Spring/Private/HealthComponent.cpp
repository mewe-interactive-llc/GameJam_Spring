// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StartingHealth = MaxHealth;
	StartingShield = MaxShield;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingShield = StartingShield == 0 ? MaxShield : StartingShield;
	StartingHealth = StartingHealth == 0 ? MaxHealth : StartingHealth; // if the starting health is = 0 use the max health if not use max health
	CurrentHealth = StartingHealth;
	CurrentShield = StartingShield;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnPlayerTakeDamage);
	}

	// ...

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetCurrentShield()
{
	return CurrentShield;
}

bool UHealthComponent::GetIsDead()
{
	return CurrentHealth <= 0;
}

void UHealthComponent::OnPlayerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentShield > 0)
	{

		CurrentShield -= Damage;
		CurrentShield = FMath::Clamp<float>(CurrentShield, 0, MaxShield);
		OnShieldChanged.Broadcast(CurrentShield);
		
	}
	else if (CurrentShield <= 0 && CurrentHealth > 0)
	{
		CurrentHealth -= Damage;

		CurrentHealth = FMath::Clamp<float>(CurrentHealth, 0, MaxHealth);

		OnHealthChanged.Broadcast(CurrentHealth);
	}
	
	

	

	if (GetIsDead())
	{
		OnPlayerDied.Broadcast();
	}
}

