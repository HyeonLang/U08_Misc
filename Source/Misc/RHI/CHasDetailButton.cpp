#include "CHasDetailButton.h"
#include "Materials/MaterialInstanceConstant.h"

ACHasDetailButton::ACHasDetailButton()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
}

#if WITH_EDITOR
void ACHasDetailButton::ChangeColor()
{
	if (!MeshComp->GetStaticMesh() || MeshComp->GetNumMaterials() < 1)
	{
		return;
	}

	TArray<UMaterialInterface*> Materials = MeshComp->GetMaterials();

	FLinearColor RandomColor = FLinearColor::MakeRandomColor();

	for (const auto& Material : Materials)
	{
		UMaterialInstanceConstant* MaterialInstance = Cast<UMaterialInstanceConstant>(Material);
		for (const auto& VectorParams : MaterialInstance->VectorParameterValues)
		{
			if (VectorParams.ParameterInfo.Name.Compare("MyColor") == 0)
			{
				MaterialInstance->SetVectorParameterValueEditorOnly(VectorParams.ParameterInfo, RandomColor);
			}
		}
	}
}

#endif