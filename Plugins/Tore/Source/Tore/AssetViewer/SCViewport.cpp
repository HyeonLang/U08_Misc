#include "SCViewport.h"
#include "CViewportClient.h"
#include "AdvancedPreviewScene.h"

SCViewport::SCViewport()
{
	
}

TSharedRef<FEditorViewportClient> SCViewport::MakeEditorViewportClient()
{
	Client = MakeShareable(new CViewportClient(Scene.Get(), SharedThis(this))); // ����Ʈ ������ ���� Sharedformthis�� ��ӹް� SharedThis(this)
	return Client.ToSharedRef();
}

void SCViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(AssetMesh);
	Collector.AddReferencedObject(FloorMesh);
}

