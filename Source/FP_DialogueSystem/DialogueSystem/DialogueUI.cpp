// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/DialogueUI.h"

void UDialogueUI::CacheQuestInstance(UQuestInstance* QuestInstance)
{
	this->CachedQuestInstances.Add(QuestInstance);
}

TArray<FDialogueChoice> UDialogueUI::GetAllRelevantDialogueChoicesForNPC(FString NpcId)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
		FString::Printf(TEXT("Getting all relevant dialogue choices for %s"), *NpcId));
	
	//return an array of all relevant dialogue choices for this specific NPC
	TArray<FDialogueChoice> RelevantChoices;
	for (auto Quest : this->CachedQuestInstances)
	{
		for (auto Choice : Quest->GetAllQuestCurrentChoices())
		{
			if (Choice.NpcId == NpcId)
			{
				RelevantChoices.Add(Choice);
			}
		}
	}
	
	return RelevantChoices;
}
