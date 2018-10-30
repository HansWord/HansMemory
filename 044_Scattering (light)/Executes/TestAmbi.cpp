#include "stdafx.h"
#include "TestAmbi.h"
#include "../Landscape/Sky.h"
#include "../Landscape/TerrainRender.h"
#include "./Objects/MeshPlane.h"
#include "./Objects/MeshSphere.h"
#include "./Objects/MeshCube.h"
#include "./Objects/MeshBunny.h"

TestAmbi::TestAmbi(ExecuteValues * values)
	: Execute(values)
{
	shader = new Shader(Shaders + L"045_Ambient.hlsl");
	plane = new MeshPlane();
	
	plane->Scale(10, 1, 10);
	plane->SetShader(shader);
	plane->SetDiffuse(1, 1, 1);

	cube = new MeshCube();
	cube->Position(-6, 1.5f, 0);
	cube->SetShader(shader);
	cube->SetDiffuse(0, 1, 0);
	cube->Scale(3, 3, 3);

	sphere = new MeshSphere();
	sphere->Position(12, 1.5f, 0);
	sphere->SetShader(shader);
	sphere->SetDiffuse(0, 0, 1);
	sphere->Scale(3, 3, 3);

	sphere2 = new MeshSphere();
	sphere2->Position(12, 1.5f, 10);
	sphere2->SetShader(shader);
	sphere2->SetDiffuse(1, 1, 1);
	sphere2->Scale(3, 3, 3);

	bunny = new MeshBunny();
	bunny->SetShader(shader);
	bunny->SetDiffuse(1, 1, 1);
	bunny->Scale(0.02f, 0.02f, 0.02f);
	bunny->Position(0, 5, 0);
	bunny->SetDiffuseMap(Textures + L"White.png");

	ambientBuffer = new AmbientBuffer();
	specularbuffer = new SpecularBuffer();
	pointLightBuffer = new PointLightBuffer();
	spotLightBuffer = new SpotLightBuffer();
	capsuleLightBuffer = new CapsuleLightBuffer();
}

TestAmbi::~TestAmbi()
{

	SAFE_DELETE(capsuleLightBuffer);
	SAFE_DELETE(spotLightBuffer);
	SAFE_DELETE(pointLightBuffer);
	SAFE_DELETE(specularbuffer);
	SAFE_DELETE(ambientBuffer);

	SAFE_DELETE(bunny);
	SAFE_DELETE(sphere2);
	SAFE_DELETE(sphere);
	SAFE_DELETE(cube);
	SAFE_DELETE(plane);
}

void TestAmbi::Update()
{
	plane->Update();
	cube->Update();
	sphere->Update();
	sphere2->Update();
	bunny->Update();
}

void TestAmbi::PreRender()
{
	
}

void TestAmbi::Render()
{
	ImGui::SliderFloat3("AmbientFloor", (float *)&ambientBuffer->Data.Floor, 0, 1);
	ImGui::SliderFloat3("AmbientCeil", (float *)&ambientBuffer->Data.Ceil, 0, 1);
	ImGui::Separator();

	ImGui::SliderFloat("Specular EXP", (float *)&specularbuffer->Data.Exp, 1, 100);
	ImGui::SliderFloat("Specular Intensity", (float *)&specularbuffer->Data.Intensity, 0, 10);
	ImGui::Separator();

	ImGui::ColorEdit4("Direction Color", (float *)&ambientBuffer->Data.Color);
	ImGui::Separator();

	ImGui::SliderFloat3("PointLight Position", (float *)&pointLightBuffer->Data.position, -50, 50);
	ImGui::ColorEdit3("PointLight Color", (float *)&pointLightBuffer->Data.Color);
	ImGui::SliderFloat("PointLight Range", (float *)&pointLightBuffer->Data.Range, 1, 100);
	ImGui::Separator();

	ImGui::ColorEdit3("SpotLight Color", (float *)&spotLightBuffer->Data.Color);
	ImGui::SliderFloat3("SpotLight Position", (float *)&spotLightBuffer->Data.position, -50, 50);
	ImGui::SliderFloat3("SpotLight Direction", (float *)&spotLightBuffer->Data.direction, -1, 1);
	ImGui::SliderFloat("SpotLight Range", (float *)&spotLightBuffer->Data.Range, 1, 100);
	ImGui::SliderFloat("SpotLight Outer", (float *)&spotLightBuffer->Data.Outer, 0, 90);
	ImGui::SliderFloat("SpotLight Inner", (float *)&spotLightBuffer->Data.Inner, 0, 90);
	ImGui::Separator();

	ImGui::ColorEdit3("CapsuleLight Color", (float *)&capsuleLightBuffer->Data.Color);
	ImGui::SliderFloat3("CapsuleLight Position", (float *)&capsuleLightBuffer->Data.position, -50, 50);
	ImGui::SliderFloat3("CapsuleLight Direction", (float *)&capsuleLightBuffer->Data.direction, -1, 1);
	ImGui::SliderFloat("CapsuleLight Range", (float *)&capsuleLightBuffer->Data.Range, 1, 100);
	ImGui::SliderFloat("CapsuleLight Length", (float *)&capsuleLightBuffer->Data.length, -100, 100);

	ambientBuffer->SetPSBuffer(10);
	specularbuffer->SetPSBuffer(11);
	pointLightBuffer->SetPSBuffer(12);
	spotLightBuffer->SetPSBuffer(13);
	capsuleLightBuffer->SetPSBuffer(9);

	plane->Render();
	cube->Render();
	sphere->Render();
	sphere2->Render();
	bunny->Render();
}

void TestAmbi::PostRender()
{
	
}
