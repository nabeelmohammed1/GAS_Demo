// Fill out your copyright notice in the Description page of Project Settings.


#include "GASDemoCharacter.h"

// Sets default values
AGASDemoCharacter::AGASDemoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGASDemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGASDemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

