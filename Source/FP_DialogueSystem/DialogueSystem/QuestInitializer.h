// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestInstance.h"
#include "DialogueUI.h"
#include "QuestInitializer.generated.h"


UCLASS(Blueprintable)
class FP_DIALOGUESYSTEM_API AQuestInitializer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestInitializer();
	
	FString QuestDataCSVPath_RawString = FPaths::ProjectSavedDir() / "QuestFiles/QuestData.csv";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LoadAllQuestsFromCSV(const FString& QuestDataCSVPath);
	
	int32 HeaderRowIndex = 0;
	
	enum EQuestDataCSV_Rows
	{
		QUEST_NAME,
		FILE_PATH
	};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	* this delegate will be invoked when the DialogueUI is opened.
		It's a signal for all QuestInstances to take their data and update the UI based on their own stages
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FOnDialogueUIOpened, UDialogueUI*, DialogueUIMenu
	);
	
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void BroadcastOnDialogueUIOpened(UDialogueUI* DialogueUIMenu);
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueUIOpened OnDialogueUIOpened;
	
	//Factory function so blueprints can make an object of this type
	/*UFUNCTION(BlueprintCallable, Category="Dialogue")
	UDialogueChoiceButtonState* CreateDialogueChoiceButtonState(FDialogueChoice Choice, UPARAM(ref) TArray<FDialogueChoice>& DisplayList);*/
};
