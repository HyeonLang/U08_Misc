#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TORE_API CAssetViewer : public FAssetEditorToolkit // ������â�� ���� ���� ��� ����
{
public:
	static void OpenWindow(UObject* Property);
	static void Shutdown();

public:
	virtual FName GetToolkitFName() const override;				
	virtual FText GetBaseToolkitName() const override;			
	virtual FString GetWorldCentricTabPrefix() const override;

	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	void OpenWindow_Internal(UObject* Property);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);

private:
	static TSharedPtr<CAssetViewer> Instance;
};
