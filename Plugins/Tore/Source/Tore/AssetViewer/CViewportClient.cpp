#include "CViewportClient.h"
#include "SCViewport.h"

CViewportClient::CViewportClient(FPreviewScene* InScene, const TSharedRef<SCViewport>& InViewport)
	: FEditorViewportClient(nullptr, InScene, StaticCastSharedRef<SCViewport>(InViewport)) // 스마트 포인터는 부모자리에 자식을 넣을 때 다운캐스팅을 해주어야함
{
	SetViewMode(EViewModeIndex::VMI_Lit);

	SetViewRotation(FRotator(-45.f, -45.f, 0.f));
	SetViewLocationForOrbiting(FVector(0.f, 0.f, 75.f), 250.f);
}

