#include "SCViewport.h"
#include "CViewportClient.h"
#include "AdvancedPreviewScene.h"

SCViewport::SCViewport()
{
	
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

