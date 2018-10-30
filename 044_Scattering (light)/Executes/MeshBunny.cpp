#include "stdafx.h"
#include "MeshBunny.h"

MeshBunny::MeshBunny()
	: GameModel(Materials + L"Meshes/", L"Plane.material", Models + L"Meshes/", L"Plane.mesh")
{
	
}

MeshBunny::~MeshBunny()
{
	
}

void MeshBunny::Update()
{
	__super::Update();
}

void MeshBunny::Render()
{
	__super::Render();
}
