#include "SCViewport.h"
#include "CViewportClient.h"
#include "AdvancedPreviewScene.h"

SCViewport::SCViewport()
{
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}

void SCViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(InArgs);

	FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	UStaticMesh* FloorAsset = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/MapTemplates/SM_Template_Map_Floor"));
	FloorMesh->SetStaticMesh(FloorAsset);

	FTransform TM;
	Scene->AddComponent(FloorMesh, TM);

	AssetMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	UStaticMesh* MikuAsset = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Meshes/SM_Miku"));
	AssetMesh->SetStaticMesh(MikuAsset);

	Scene->AddComponent(AssetMesh, TM);
}

TSharedRef<FAdvancedPreviewScene> SCViewport::GetScene()
{
	return Scene.ToSharedRef();
}

TSharedRef<FEditorViewportClient> SCViewport::MakeEditorViewportClient()
{
	Client = MakeShareable(new CViewportClient(Scene.Get(), SharedThis(this))); // 스마트 포인터 사용시 Sharedformthis를 상속받고 SharedThis(this)
	return Client.ToSharedRef();
}

void SCViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(AssetMesh);
	Collector.AddReferencedObject(FloorMesh);
}

