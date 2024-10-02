// Fill out your copyright notice in the Description page of Project Settings.


#include "CButtonCommand.h"

CButtonCommand::CButtonCommand()
	:TCommands("Tore", FText::FromString("My Command"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

CButtonCommand::~CButtonCommand()
{
}

void CButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE "Tore"
	UI_COMMAND(LoadMeshButtonID, "LoadMesh", "Load Mesh Data.", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
}
