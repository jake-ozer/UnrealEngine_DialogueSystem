// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/QuestInitializer.h"
#include "QuestInstance.h"

// Sets default values
AQuestInitializer::AQuestInitializer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestInitializer::BeginPlay()
{
	Super::BeginPlay();
	
	LoadAllQuestsFromCSV(QuestDataCSVPath_RawString);
}

void AQuestInitializer::LoadAllQuestsFromCSV(const FString& QuestDataCSVPath)
{
	//Load all the quest data from the quest data table csv
	TArray<FString> QuestDataFileRows;
	if (FFileHelper::LoadFileToStringArray(QuestDataFileRows, *QuestDataCSVPath))
	{
		//declare intended start index for parsing CSV
		const int32 DataStartIndex = 1 + HeaderRowIndex;

		//loop through all CSV rows, initialize quests
		for (int32 i = DataStartIndex; i < QuestDataFileRows.Num(); i++)
		{
			TArray<FString> QuestDataFileRow;
			QuestDataFileRows[i].ParseIntoArray(QuestDataFileRow, TEXT(","), true);
			
			FString CurQuestName = QuestDataFileRow[QUEST_NAME];
			FString CurFilePath = QuestDataFileRow[FILE_PATH];
			UQuestInstance* NewQuestInstance = NewObject<UQuestInstance>(this);
			NewQuestInstance->CreateQuestInstance(CurFilePath, GetWorld(), this);
		}
	}
}



// Called every frame
void AQuestInitializer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TODO: Uncouple this from QuestInitializer
void AQuestInitializer::BroadcastOnDialogueUIOpened(UDialogueUI* DialogueUIMenu)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple,
		FString::Printf(TEXT("UI opened event broadcasted")));
	OnDialogueUIOpened.Broadcast(DialogueUIMenu);
}

//TODO: Uncouple this from QuestInitializer
/*UDialogueChoiceButtonState* AQuestInitializer::CreateDialogueChoiceButtonState(FDialogueChoice Choice, TArray<FDialogueChoice>& DisplayList)
{
	UDialogueChoiceButtonState* ButtonState = NewObject<UDialogueChoiceButtonState>(this);
	ButtonState->CreateButtonState(Choice, DisplayList);
	return ButtonState;
}*/

