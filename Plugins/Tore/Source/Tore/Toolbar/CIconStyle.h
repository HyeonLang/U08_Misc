#pragma once

#include "CoreMinimal.h"
#include "D:/UE_4.25/Engine/Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRHMD_RenderBridge.cpp"

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
	static TSharedPtr<CIconStyle> Instance;

public:
	FSlateIcon LoadMeshIcon;

private:
	const FName StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
