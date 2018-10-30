#pragma once
#include "Execute.h"

class TestAmbi : public Execute
{
public:
	TestAmbi(ExecuteValues* values);
	~TestAmbi();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen(){}

private:
	Shader* shader;

	class MeshPlane* plane;
	class MeshCube* cube;
	class MeshSphere * sphere;
	class MeshSphere * sphere2;
	class MeshBunny * bunny;
private:
	class AmbientBuffer : public ShaderBuffer
	{
	public:
		AmbientBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXCOLOR(0.85f, 0.8f, 0.5f, 1.0f);
			Data.Floor = D3DXVECTOR3(0, 1, 0);
			Data.Ceil = D3DXVECTOR3(1, 1, 1);
		}

		struct Struct
		{
			D3DXCOLOR Color;

			D3DXVECTOR3 Floor;
			float padding1;
			D3DXVECTOR3 Ceil;
			float padding2;
		} Data;
	};
	AmbientBuffer* ambientBuffer;

	class SpecularBuffer : public ShaderBuffer
	{
	public:
		SpecularBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Exp = 10;
			Data.Intensity = 2;
		}

		struct Struct
		{
			float Exp;
			float Intensity;
			float padding[2];
		} Data;
	};
	SpecularBuffer* specularbuffer;

	class PointLightBuffer : public ShaderBuffer
	{
	public:
		PointLightBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.position = D3DXVECTOR3(0,10,0);
			Data.Range = 20;
			Data.Color = D3DXCOLOR(1, 0, 0, 1);
		}

		struct Struct
		{
			
			D3DXVECTOR3 position;
			float Range;
			D3DXCOLOR Color;
		} Data;
	};
	PointLightBuffer* pointLightBuffer;

	class SpotLightBuffer : public ShaderBuffer
	{
	public:
		SpotLightBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXCOLOR(0, 0, 1,0 );

			Data.position = D3DXVECTOR3(0, 10, 0);
			Data.Range = 20;
			Data.direction = D3DXVECTOR3(0,1,0);
			Data.Inner = 15;
			Data.Outer = 25;
		}

		struct Struct
		{
			D3DXCOLOR Color;

			D3DXVECTOR3 position;
			float Range;
			
			D3DXVECTOR3 direction;
			float Outer;
			float Inner;

			float padding[3];
		} Data;
	};
	SpotLightBuffer* spotLightBuffer;

	class CapsuleLightBuffer : public ShaderBuffer
	{
	public:
		CapsuleLightBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXCOLOR(1, 0, 0, 0);

			Data.position = D3DXVECTOR3(0, 10, 0);
			Data.Range = 60;
			Data.direction = D3DXVECTOR3(0, 1, 0);
			Data.length = 10;
		}

		struct Struct
		{
			D3DXCOLOR Color;

			D3DXVECTOR3 position;
			float Range;

			D3DXVECTOR3 direction;
			float length;
		} Data;
	};
	CapsuleLightBuffer* capsuleLightBuffer;;
};