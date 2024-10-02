#include "Tore.h"
#include "LevelEditor.h"
#include "AssetToolsModule.h"
#include "AssetTools/CAssetTypeAction.h"
#include "Toolbar/CButtonCommand.h"

#define LOCTEXT_NAMESPACE "FToreModule"

void FToreModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Tore Module"));

	//ToolBar
	{
		CButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate Delegate = FToolBarExtensionDelegate::CreateRaw(this, &FToreModule::AddLoadMeshButton);
		Extender->AddToolBarExtension("Misc", EExtensionHook::Before, nullptr, Delegate);

		FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	//AssetTools
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		//EAssetTypeCategories::Type AssetCategory = EAssetTypeCategories::Misc;
		EAssetTypeCategories::Type AssetCategory =  AssetTools.RegisterAdvancedAssetCategory("MaterialData", FText::FromString("Material Data"));
		AssetToolAction = MakeShareable(new CAssetTypeAction(AssetCategory));
		AssetTools.RegisterAssetTypeActions(AssetToolAction.ToSharedRef());
	}
}

void FToreModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdown Tore Module"));
}

void FToreModule::AddLoadMeshButton(FToolBarBuilder& ToolBarBuilder)
{
	FSlateIcon Icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");

	ToolBarBuilder.AddSeparator();
	ToolBarBuilder.AddToolBarButton
	(
		CButtonCommand::Get().LoadMeshButtonID,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data")
		Icon,

	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToreModule, Tore)