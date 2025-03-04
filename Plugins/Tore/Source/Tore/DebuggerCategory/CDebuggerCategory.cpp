#include "CDebuggerCategory.h"
#include "GameFramework/PlayerController.h"
#include "CanvasItem.h"

CDebuggerCategory::CDebuggerCategory()
{
	UE_LOG(LogTemp, Error, TEXT(__FUNCTION__));

	bShowOnlyWithDebugActor = false; // bShowOnlyWithDebugActor : 현재 카메라에 보이는 액터만 디버그 액터로 취급 여부
}

CDebuggerCategory::~CDebuggerCategory()
{
	UE_LOG(LogTemp, Error, TEXT(__FUNCTION__));
}

TSharedRef<FGameplayDebuggerCategory> CDebuggerCategory::MakeInstance()
{
	return MakeShareable(new CDebuggerCategory);
}

void CDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	APawn* PlayerPawn = OwnerPC->GetPawn();

	//Player
	{
		PlayerData.Name = PlayerPawn->GetName();
		PlayerData.Location = PlayerPawn->GetActorLocation();
		PlayerData.Forward = PlayerPawn->GetActorForwardVector();
	}

	//ForwardActor
	{
		FVector Start = PlayerPawn->GetActorLocation();
		FVector End = Start + PlayerPawn->GetActorForwardVector() * 1e+4f;
		FHitResult Hit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(PlayerPawn);

		PlayerPawn->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);

		if (Hit.bBlockingHit)
		{
			ForwardActorData.Name = Hit.GetActor()->GetName();
			ForwardActorData.Location = Hit.GetActor()->GetActorLocation();
			ForwardActorData.Forward = Hit.GetActor()->GetActorForwardVector();
		}
		else
		{
			ForwardActorData.Name = "No exist forward actor";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;
		}
	}

	//DebugActor
	if (DebugActor)
	{
		DebugActorData.Name = DebugActor->GetName();
		DebugActorData.Location = DebugActor->GetActorLocation();
		DebugActorData.Forward = DebugActor->GetActorForwardVector();
	}
	else
	{
		DebugActorData.Name = "No exist debug actor";
		DebugActorData.Location = FVector::ZeroVector;
		DebugActorData.Forward = FVector::ZeroVector;
	}
}


void CDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem Item(FVector2D(10, 10), FVector2D(300, 220), FLinearColor(1, 0, 0, 0.3f));
	Item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend; // alpha mode set
	CanvasContext.DrawItem(Item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, TEXT("--Player--"));
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *PlayerData.Name);
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *PlayerData.Location.ToString());
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *PlayerData.Forward.ToString());
	CanvasContext.Printf(FColor::Green, TEXT(""));

	CanvasContext.Printf(FColor::Green, TEXT("--Forward Actor--"));
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *ForwardActorData.Name);
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::Green, TEXT(""));

	CanvasContext.Printf(FColor::Green, TEXT("--Debug Actor--"));
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *DebugActorData.Name);
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *DebugActorData.Location.ToString());
	CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *DebugActorData.Forward.ToString());
	CanvasContext.Printf(FColor::Green, TEXT(""));
}
