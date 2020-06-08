// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class UDamageType;
class AController;
class AActor;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldChanged, float, Shield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);




UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEJAM_SPRING_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float StartingHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shields")
		float MaxShield = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shields")
		float StartingShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shields")
	float CurrentShield;



	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "Shield")
		float GetCurrentShield();

	UFUNCTION(BlueprintPure, Category = "Health")
		bool GetIsDead();

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Shield")
		FOnShieldChanged OnShieldChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnPlayerDied OnPlayerDied;



private:
	

	UFUNCTION()
		void OnPlayerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};