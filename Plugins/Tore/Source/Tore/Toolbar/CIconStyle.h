#pragma once

#include "CoreMinimal.h"
//#include "D:/UE_4.25/Engine/Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRHMD_RenderBridge.cpp"

class FSlateStyleSet;

class TORE_API CIconStyle
{
public:
	static TSharedPtr<CIconStyle> Get();
	static void Shutdown();

public:
	CIconStyle();
	~CIconStyle();

private:
	void RegisterIcon(FSlateIcon& OutIcon, const FString& PostFix, const FString& ImagePath, const FVector2D& Size = FVector2D(48));

private:
	static TSharedPtr<CIconStyle> Instance;

public:
	FSlateIcon LoadMeshIcon;
	FSlateIcon OpenViewerIcon;

private:
	const FName StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
