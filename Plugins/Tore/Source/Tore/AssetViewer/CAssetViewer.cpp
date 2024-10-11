#include "CAssetViewer.h"
#include "SCViewport.h"
#include "AdvancedPreviewSceneModule.h"

TSharedPtr<CAssetViewer> CAssetViewer::Instance = nullptr;
const static FName AppId = TEXT("ToreAssetViewer");
const static FName ViewportTabId = TEXT("ViewportTabId");
const static FName PreviewTabId = TEXT("PreviewTabId");
const static FName DetailsTabId = TEXT("DetailsTabId");

void CAssetViewer::OpenWindow(UObject* Property)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
		Instance.Reset();
	}

	Instance = MakeShareable(new CAssetViewer());
	Instance->OpenWindow_Internal(Property);
}

void CAssetViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
	}
}

FName CAssetViewer::GetToolkitFName() const
{
	return AppId;
}

FText CAssetViewer::GetBaseToolkitName() const
{
	return FText::FromName(AppId);
}

FString CAssetViewer::GetWorldCentricTabPrefix() const
{
	return AppId.ToString();
}

FLinearColor CAssetViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

void CAssetViewer::OpenWindow_Internal(UObject* Property)
{
	Viewport = SNew(SCViewport);

	FAdvancedPreviewSceneModule& AdvancedPreview = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	PreviewSceneSettings = AdvancedPreview.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetScene());

	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs Args(false, false, true, FDetailsViewArgs::ENameAreaSettings::ObjectsUseNameArea);
	DetailsView = PropertyEditor.CreateDetailView(Args);
	DetailsView->SetObject(Property);

	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("ToreLayout")
		->AddArea
		(
			//ToolBar
			FTabManager::NewPrimaryArea()
			->SetOrientation(EOrientation::Orient_Vertical)

			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				//->Split(영역)->Stack(실제 붙일 탭)
			)

			//(LargeSpace)
			->Split
			(
				//(MiddleSpace) Viewport
				FTabManager::NewSplitter()
				->SetOrientation(EOrientation::Orient_Horizontal)
				->SetSizeCoefficient(0.75f)

				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)

				//(MiddleSpace) RightPannel
				->Split
				(
					//(SmallSpace) Preview
					FTabManager::NewSplitter()
					->SetOrientation(EOrientation::Orient_Vertical)
					->SetSizeCoefficient(0.5f)

					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabId, ETabState::OpenedTab)
					)
					//(SmallSpace) Details
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabId, ETabState::OpenedTab)
					)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone,
		TSharedPtr<IToolkitHost>(),
		AppId,
		Layout,
		true,
		true,
		Property
	);
}

void CAssetViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &CAssetViewer::Spawn_ViewportTab));
	TabManager->RegisterTabSpawner(PreviewTabId, FOnSpawnTab::CreateSP(this, &CAssetViewer::Spawn_PreviewSceneSettingsTab));
	TabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &CAssetViewer::Spawn_DetailsViewTab));
}

TSharedRef<SDockTab> CAssetViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> CAssetViewer::Spawn_PreviewSceneSettingsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			PreviewSceneSettings.ToSharedRef()
		];
}

TSharedRef<SDockTab> CAssetViewer::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return  SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];;
}

