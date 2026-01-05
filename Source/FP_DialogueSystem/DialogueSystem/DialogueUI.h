// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestInstance.h"
#include "Blueprint/UserWidget.h"
#include "DialogueUI.generated.h"

/**
 * 
 */
UCLASS()
class FP_DIALOGUESYSTEM_API UDialogueUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void CacheQuestInstance(UQuestInstance* QuestInstance);
	
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	TArray<FDialogueChoice> GetAllRelevantDialogueChoicesForNPC(FString NpcId); 
	
private:
	//The list of quest instances cached only for the lifetime of the menu
	TArray<UQuestInstance*> CachedQuestInstances;
	
};
