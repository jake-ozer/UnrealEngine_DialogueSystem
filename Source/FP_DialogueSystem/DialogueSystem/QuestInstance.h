// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestInstance.generated.h"

//forward declaration to prevent circular dependency
class AQuestInitializer;

USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 NodeId;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> NodeTags;
	
	UPROPERTY(BlueprintReadWrite)
	FString NpcId;
	
	UPROPERTY(BlueprintReadWrite)
	FString NpcName;
	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerSentence;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> NpcResponse;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> NextNodeIds;
	
	UPROPERTY(BlueprintReadWrite)
	FString OpenTangentId;
	
	UPROPERTY(BlueprintReadWrite)
	FString CurrentTangentId;
	
	UPROPERTY(BlueprintReadWrite)
	FString CloseTangentId;
	
	UPROPERTY(BlueprintReadWrite)
	UQuestInstance* OwningQuestInstance;
};

USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()

	//A list of ALL dialogue choices for any given quests
	UPROPERTY(BlueprintReadWrite)
	TArray<FDialogueChoice> QuestDialogueChoices;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FP_DIALOGUESYSTEM_API UQuestInstance : public UActorComponent
{
	GENERATED_BODY()
	
	public:
		/**
		 * Pseudo-Constructor that goes on to store quest data and initialize the quest with starting values
		 * 
		 * @param JsonPath 
		 * @param World 
		 * @param QuestInitializer 
		 */
		UFUNCTION(BlueprintCallable, Category="DialogueSystem", meta=(ToolTip = "Call this function to initialize a quest from a JSON file path."))
		void CreateQuestInstance(FString JsonPath, UWorld* World, AQuestInitializer* QuestInitializer);

		/**
		 * Called by Multicast delegate any time DialogueUI is opened
		 * 
		 */
		UFUNCTION()
		void OnDialogueOpened(UDialogueUI* DialogueUIMenu);
			
		UFUNCTION(BlueprintCallable, Category="DialogueSystem", meta=(ToolTip = ""))
		TArray<FDialogueChoice> GetAllQuestCurrentChoices();
			
	
		UFUNCTION(BlueprintCallable, Category="DialogueSystem", meta=(ToolTip = "Call this function when a dialogue choice is chosen to load the next set of choices"))
		void AdvanceQuestFromDialogueChoice(FDialogueChoice PickedChoice);
		
	
	protected:
		//the QuestInitializer that created this quest
		AQuestInitializer* InstanceQuestInitializer;
	
		//All data for this quest (nodes, links, etc)
		FQuestData InstanceQuestData;
		
		//The current dialogue choices that should be displayed based on our quest stage
		TArray<FDialogueChoice> QuestCurrentChoices;

		/**
		 * Parses a JSON file for quest data, and loads it into this->InstanceQuestData
		 * 
		 * @param JsonPath 
		 * @return 
		 */
		FQuestData ParseJsonForQuestData(const FString& JsonPath);
	
		/**
		 * Helper function whose implementation decides how the initial dialogue option is chosen 
		 */
		void AssignStartingQuestDialogueChoice();
	
		/**
		 * Searches this->InstanceQuestData for a FDialogueChoice pointer from a NodeId
		 * 
		 * @param NodeId 
		 * @return 
		 */
		FDialogueChoice GetDialogueChoiceFromNodeId(int32 NodeId);
		
		/**
		 * Searches this->InstanceQuestData for all FDialogueChoice pointer from a specific tag
		 * 
		 * @param Tag
		 * @return 
		 */
		TArray<FDialogueChoice> GetAllDialogueChoicesFromTag(FString Tag);
	
		/**
		 * Prints all quest nodes to screen and log for debugging purposes
		 */
		void DEBUG_PrintAllQuestNodes(UWorld* World);
};
