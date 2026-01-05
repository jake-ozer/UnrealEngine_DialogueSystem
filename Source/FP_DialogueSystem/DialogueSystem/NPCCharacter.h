// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class FP_DIALOGUESYSTEM_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dialogue System")
	FString NPC_ID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dialogue System")
	FString NPC_DisplayName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dialogue System")
	TArray<FString> NPC_Greeting;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
