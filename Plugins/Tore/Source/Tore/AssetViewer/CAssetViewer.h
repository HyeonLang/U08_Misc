#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class SCViewport;
class IDetailsView;

class TORE_API CAssetViewer : public FAssetEditorToolkit // 윈도우창을 띄우고 끄는 기능 보유
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
	TSharedRef<SDockTab> Spawn_PreviewSceneSettingsTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs);

private:
	static TSharedPtr<CAssetViewer> Instance;

private:
	TSharedPtr<SCViewport> Viewport;
	TSharedPtr<SWidget> PreviewSceneSettings;
	TSharedPtr<IDetailsView> DetailsView;
};
