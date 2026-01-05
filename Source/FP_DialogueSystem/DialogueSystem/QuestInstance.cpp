// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/QuestInstance.h"
#include "QuestInitializer.h"

#include "WorldNPCFinder.h"

void UQuestInstance::CreateQuestInstance(FString JsonPath, UWorld* World, AQuestInitializer* QuestInitializer)
{
	this->InstanceQuestInitializer = QuestInitializer;
	this->InstanceQuestData = ParseJsonForQuestData(JsonPath);
	
	//subscribe our local OnDialogueOpened to OnDialogueUIOpened event
	this->InstanceQuestInitializer->OnDialogueUIOpened.AddDynamic(
		this,
		&UQuestInstance::OnDialogueOpened
	);
	
	//debug print quest nodes and connection to NPCs
	//DEBUG_PrintAllQuestNodes(World);
	
	//Assign the starting choices for this quest's dialogue
	AssignStartingQuestDialogueChoice();
}

FQuestData UQuestInstance::ParseJsonForQuestData(const FString& JsonPath)
{
	FQuestData QuestData;
	
	FString FullPath = FPaths::ProjectSavedDir() / JsonPath;
	UE_LOG(LogTemp, Warning, TEXT("Loading JSON from: %s"), *FullPath);
	
	FString JsonString;
	
	if (!FFileHelper::LoadFileToString(JsonString, *FullPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read JSON file: %s"), *JsonPath);
		return QuestData;
	}
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		const TArray<TSharedPtr<FJsonValue>>* NodesArray;
		if (JsonObject->TryGetArrayField(TEXT("nodes"), NodesArray))
		{
			for (auto& NodeValue : *NodesArray)
			{
				TSharedPtr<FJsonObject> NodeObject = NodeValue->AsObject();
				if (NodeObject.IsValid())
				{
					FDialogueChoice DialogueChoice;
					DialogueChoice.NodeId = NodeObject->GetIntegerField(TEXT("node_id"));
					
					//Get all node tags
					const TArray<TSharedPtr<FJsonValue>>* TagArray;
					if (NodeObject->TryGetArrayField(TEXT("node_tags"), TagArray))
					{
						for (auto& TagValue : *TagArray)
						{
							DialogueChoice.NodeTags.Add(TagValue->AsString()); 
						}
					}
					
					DialogueChoice.NpcId = NodeObject->GetStringField(TEXT("npc_id"));
					DialogueChoice.NpcName = NodeObject->GetStringField(TEXT("npc_name"));
					DialogueChoice.PlayerSentence = NodeObject->GetStringField(TEXT("player"));
					
					//Get all NPC Responses
					const TArray<TSharedPtr<FJsonValue>>* ResponseArray;
					if (NodeObject->TryGetArrayField(TEXT("npc_response"), ResponseArray))
					{
						for (auto& ResponseValue : *ResponseArray)
						{
							DialogueChoice.NpcResponse.Add(ResponseValue->AsString()); 
						}
					}
					
					//Get all next node ids
					const TArray<TSharedPtr<FJsonValue>>* NextArray;
					if (NodeObject->TryGetArrayField(TEXT("next"), NextArray))
					{
						for (auto& NextValue : *NextArray)
						{
							DialogueChoice.NextNodeIds.Add(NextValue->AsNumber()); // JSON numbers -> int32
						}
					}
					
					DialogueChoice.OpenTangentId = NodeObject->GetStringField(TEXT("open-tangent"));
					DialogueChoice.CurrentTangentId = NodeObject->GetStringField(TEXT("current-tangent"));
					DialogueChoice.CloseTangentId = NodeObject->GetStringField(TEXT("close-tangent"));
					
					DialogueChoice.OwningQuestInstance = this;
					QuestData.QuestDialogueChoices.Add(DialogueChoice);
				}
			}
		}
	}
	
	return QuestData;
}

void UQuestInstance::AssignStartingQuestDialogueChoice()
{
	const FString STARTING_NODE_TAG = "START";
	
	//get all the choices that are marked with the 'start' tag
	TArray<FDialogueChoice> StartingChoices = GetAllDialogueChoicesFromTag(STARTING_NODE_TAG);
	
	//Add those starting choices to our current choices (to be displayed in OnDialogueOpened callback)
	for (auto const Choice : StartingChoices)
	{
		this->QuestCurrentChoices.Add(Choice);
	}
}

void UQuestInstance::OnDialogueOpened(UDialogueUI* DialogueUIMenu)
{
	//find our current dialogue options based on our quest, add them to the DialogueChoices reference
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple,
		FString::Printf(TEXT("HANDLING DIALOGUE UI OPENED FROM QUEST INSTANCE")));*/

	//have the UI menu cache this quest instance
	DialogueUIMenu->CacheQuestInstance(this);
}

TArray<FDialogueChoice> UQuestInstance::GetAllQuestCurrentChoices()
{
	return this->QuestCurrentChoices;
}

void UQuestInstance::AdvanceQuestFromDialogueChoice(FDialogueChoice PickedChoice)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,
		FString::Printf(TEXT("Picked sentence:  %s"), *PickedChoice.PlayerSentence));
	
	//get the set of next dialogue options, and swap out the current choices with the next
	this->QuestCurrentChoices.Empty();
	for (auto const ChoiceId : PickedChoice.NextNodeIds)
	{
		FDialogueChoice NewChoice = GetDialogueChoiceFromNodeId(ChoiceId);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,
	FString::Printf(TEXT("Adding new choice with sentence:  %s"), *NewChoice.PlayerSentence));
		this->QuestCurrentChoices.Add(NewChoice);
	}
}

FDialogueChoice UQuestInstance::GetDialogueChoiceFromNodeId(int32 NodeId)
{
	for (auto const Choice : this->InstanceQuestData.QuestDialogueChoices)
	{
		if (Choice.NodeId == NodeId)
		{
			return Choice;
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Could not find DialogueChoice ref from Node ID: %d"), NodeId);
	return FDialogueChoice();
}

TArray<FDialogueChoice> UQuestInstance::GetAllDialogueChoicesFromTag(FString Tag)
{
	//Grab nodes with tag
	TArray<FDialogueChoice> Choices;
	for (auto const QuestChoices : this->InstanceQuestData.QuestDialogueChoices)
	{
		if (QuestChoices.NodeTags.Contains(Tag))
		{
			Choices.Add(QuestChoices);
		}
	}
	
	//Validate that Choices list is not empty
	if (Choices.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find any choices with tag: %s"), *Tag);
		return {};
	}
	
	return Choices;
}

void UQuestInstance::DEBUG_PrintAllQuestNodes(UWorld* World)
{
	for (auto& DialogueChoice : this->InstanceQuestData.QuestDialogueChoices)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
		FString::Printf(TEXT("Node %d: NPC_Name: %s PlayerSentence: %s"), DialogueChoice.NodeId, *DialogueChoice.NpcName, *DialogueChoice.PlayerSentence));
		
		UE_LOG(LogTemp, Log, TEXT("DIALOGUE SYSTEM-> Node %d: NPC_Name: %s PlayerSentence: %s"), DialogueChoice.NodeId, *DialogueChoice.NpcName, *DialogueChoice.PlayerSentence);
		
		//take our validated quest data, and get the NPC that matches that quest
		UWorldNPCFinder* WorldNPCFinder = NewObject<UWorldNPCFinder>();
		if (WorldNPCFinder->GetNPCFromID(DialogueChoice.NpcId, World))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple,
		FString::Printf(TEXT("Found NPC:  %s"), *DialogueChoice.NpcName));
		}
	}
}




