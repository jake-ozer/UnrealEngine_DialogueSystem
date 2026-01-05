// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem/RotateTowardsHelper.h"

#include "Camera/CameraComponent.h"
#include "EntitySystem/MovieSceneEntityManager.h"

// Sets default values for this component's properties
URotateTowardsHelper::URotateTowardsHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void URotateTowardsHelper::SetRotateHelperData(APlayerController* PlayerControllerToRotate, USceneComponent* DialogueFocusSceneComponent)
{
	//nullptr checks
	//-------------------------------------------------------------------------------------------
	if (!PlayerControllerToRotate || !DialogueFocusSceneComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid input to SetRotateHelperData"));
		return;
	}
	
	const APawn* Pawn = PlayerControllerToRotate->GetPawn();
	if (!Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController has no pawn."));
		return;
	}
	
	const UCameraComponent* CameraComp = Pawn->FindComponentByClass<UCameraComponent>();
	if (!CameraComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn has no CameraComponent."));
		return;
	}
	//-------------------------------------------------------------------------------------------
	
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,TEXT("Called SetRotateHelperData"));
	
	//Cache PlayerController that we will rotate
	this->CachedController = PlayerControllerToRotate;
	
	//Calculate then Cache target rotation for our eventual interpolation
	const FVector StartPos = CameraComp->GetComponentLocation();
	const FVector TargetPos = DialogueFocusSceneComponent->GetComponentLocation();
	const FVector LookDir = TargetPos - StartPos;
	this->CachedTargetRot = LookDir.Rotation();
}

void URotateTowardsHelper::RotateTowardsHelper(const float InterpSpeed) const
{
	//perform interpolation
	const float DT = GetWorld()->GetDeltaSeconds();
	const FRotator NewRot = FMath::RInterpTo(this->CachedController->GetControlRotation(), this->CachedTargetRot, DT, InterpSpeed);
	CachedController->SetControlRotation(NewRot);
}

