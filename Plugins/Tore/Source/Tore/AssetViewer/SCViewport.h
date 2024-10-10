#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class CViewportClient;
class FAdvancedPreviewScene;

class TORE_API SCViewport : public SEditorViewport, public FGCObject // Uobject�� �ƴϹǷ� �������ݷ��͸� �������� ���
{
public:
	SCViewport();

public:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

private:
	TSharedPtr<FAdvancedPreviewScene> Scene;
	TSharedPtr<CViewportClient> Client;

private:
	UStaticMeshComponent* AssetMesh;
	UStaticMeshComponent* FloorMesh;
};
