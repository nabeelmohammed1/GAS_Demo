// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h" // Required for EGameplayEffectReplicationMode
#include "GASDemoCharacter.generated.h"

UCLASS()
class GAS_DEMO_API AGASDemoCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASDemoCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	class UDemoAttributeSet* DemoAttributeSet;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartingAbilities;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void GrantStartingAbilities();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void RemoveAbilities(TArray<struct FGameplayAbilitySpecHandle> AbilityHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void SendAbilitiesChangedEvent();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GAS")
	void ServerSendGameplayEventToSelf(FGameplayEventData EventData);
};