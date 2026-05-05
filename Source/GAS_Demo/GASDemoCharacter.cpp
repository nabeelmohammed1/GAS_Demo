// Fill out your copyright notice in the Description page of Project Settings.


#include "GASDemoCharacter.h"
#include "DemoAtrribute.h"	
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AGASDemoCharacter::AGASDemoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	DemoAttributeSet = CreateDefaultSubobject<UDemoAttributeSet>(TEXT("DemoAttributeSet"));

	// ... (Rest of your movement/capsule config)
}

void AGASDemoCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AGASDemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGASDemoCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantStartingAbilities();
	}
}

void AGASDemoCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* AGASDemoCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASDemoCharacter::GrantStartingAbilities()
{
	if (!AbilitySystemComponent || !HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility>& Ability : StartingAbilities)
	{
		if (Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this));
		}
	}
	SendAbilitiesChangedEvent();
}

void AGASDemoCharacter::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority()) return;

	for (FGameplayAbilitySpecHandle Handle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(Handle);
	}
	SendAbilitiesChangedEvent();
}

void AGASDemoCharacter::SendAbilitiesChangedEvent()
{
	FGameplayTag EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventTag, FGameplayEventData());
}

void AGASDemoCharacter::ServerSendGameplayEventToSelf_Implementation(FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

void AGASDemoCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
void AGASDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) { Super::SetupPlayerInputComponent(PlayerInputComponent); }