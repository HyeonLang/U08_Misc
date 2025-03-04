#include "CMiku.h"
#include "Materials/MaterialInstanceConstant.h"

ACMiku::ACMiku()
{

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/AMiku/Mesh/Appearance_Miku"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	LightDirection = FVector(1, 1, 1);

	bRunConstructionScriptOnDrag = false;
}

void ACMiku::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (MaterialData)
	{
		TArray<FMaterialElementData*> ReadDatas;
		MaterialData->GetAllRows("", ReadDatas);

		if ((int32)RenderType >= ReadDatas.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("RenderType is out of size"));
			return;
		}

		MikuMeterials.Empty();

		if (ReadDatas[(int32)RenderType] && ReadDatas[(int32)RenderType]->DataAsset)
		{
			UCMaterialData* SelectedDataAsset = ReadDatas[(int32)RenderType]->DataAsset;

			for (int32 i = 0; i < (int32)EMaterialElementType::Max; i++)
			{
				if (SelectedDataAsset->Materials[i])
				{
					MikuMeterials.Add(SelectedDataAsset->Materials[i]);
					GetMesh()->SetMaterial(i, SelectedDataAsset->Materials[i]);
				}
			}
		}
	}

	SetLightDirectionToMaterials(LightDirection);
}



#if WITH_EDITOR
void ACMiku::SetLightDirectionToMaterials(FVector InDirection)
{
	for (UMaterialInstanceConstant* MikuMeterial : MikuMeterials)
	{
		for (const FVectorParameterValue& VectorParams : MikuMeterial->VectorParameterValues)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, VectorParams.ParameterInfo.Name.ToString());
			
			if (VectorParams.ParameterInfo.Name == "LightDirection")
			{
				MikuMeterial->SetVectorParameterValueEditorOnly(VectorParams.ParameterInfo, InDirection);
			}
		}
	}
}
#endif

