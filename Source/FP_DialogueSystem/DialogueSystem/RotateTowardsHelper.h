// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotateTowardsHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FP_DIALOGUESYSTEM_API URotateTowardsHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateTowardsHelper();

protected:
	APlayerController* CachedController;
	FRotator CachedTargetRot;

public:	
	UFUNCTION(BlueprintCallable, Category="DialogueSystem", meta=(ToolTip = "Sets the data needed for a camera interpolation. Execute this before RotateTowardsHelper"))
	void SetRotateHelperData(APlayerController* PlayerControllerToRotate, USceneComponent* DialogueFocusSceneComponent);
	
	UFUNCTION(BlueprintCallable, Category = "DialogueSystem", meta = (ToolTip = "Operates on stored data from SetRotateHelperData (that must be called first). Smoothly rotates player controller to target using interpolation. Must be hooked up to a Timeline node for dt update."))
	void RotateTowardsHelper(const float InterpSpeed) const;
		
};
