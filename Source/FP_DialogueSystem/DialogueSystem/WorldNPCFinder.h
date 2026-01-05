// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NPCCharacter.h"
#include "WorldNPCFinder.generated.h"

/**
 * 
 */
UCLASS()
class FP_DIALOGUESYSTEM_API UWorldNPCFinder : public UObject
{
	GENERATED_BODY()
	
	public:
		ANPCCharacter* GetNPCFromID(FString NpcId, UWorld* World);
};
