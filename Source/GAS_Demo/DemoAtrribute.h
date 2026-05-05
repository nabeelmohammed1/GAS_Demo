// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DemoAtrribute.generated.h"

/**
 * 
 */
UCLASS()
class GAS_DEMO_API UDemoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:	
	UDemoAttributeSet();
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UDemoAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UDemoAttributeSet, MaxHealth);

	//Stamina Attribute
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS_BASIC(UDemoAttributeSet, Stamina);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(UDemoAttributeSet, MaxStamina);


	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Health, OldHealth);
	}

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxHealth, OldMaxHealth);
	}

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, Stamina, OldStamina);
	}

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UDemoAttributeSet, MaxStamina, OldMaxStamina);
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
