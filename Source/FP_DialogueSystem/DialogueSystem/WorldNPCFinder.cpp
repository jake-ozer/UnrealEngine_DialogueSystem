// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/WorldNPCFinder.h"

#include "NPCCharacter.h"
#include "Kismet/GameplayStatics.h"

ANPCCharacter* UWorldNPCFinder::GetNPCFromID(FString NpcId, UWorld* World)
{
	TArray<AActor*> NPCActors;
	UGameplayStatics::GetAllActorsOfClass(World, ANPCCharacter::StaticClass(), NPCActors);
	
	for (AActor* Actor : NPCActors)
	{
		if (ANPCCharacter* NPC = Cast<ANPCCharacter>(Actor))
		{
			if (NpcId == NPC->NPC_ID)
			{
				return NPC;
			}
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Failed to find NPC with NPC_ID: %s"), *NpcId);
	return nullptr;
}
