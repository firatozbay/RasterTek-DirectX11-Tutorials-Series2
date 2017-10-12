////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
using namespace std;
using namespace DirectX;
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
//#include "textureclass.h"
#include "texturearrayclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};
	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	struct VectorType
	{
		float x, y, z;
	};
	struct InstanceType
	{
		XMFLOAT3 position;
	};
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, WCHAR*, char*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, WCHAR*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();


	ID3D11ShaderResourceView* GetTexture();		//Assume it is 0
	ID3D11ShaderResourceView* GetNormalMap();	//Assume it is 1
	ID3D11ShaderResourceView** GetTextureArray();
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	
	//bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	//void ReleaseTexture();	

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char*);
	void ReleaseModel();

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);
private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer* m_instanceBuffer;
	int m_vertexCount;	
	int m_instanceCount;
	//TextureClass* m_Texture;
	TextureArrayClass* m_TextureArray;
	ModelType* m_model;
};

#endif