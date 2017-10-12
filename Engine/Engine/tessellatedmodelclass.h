////////////////////////////////////////////////////////////////////////////////
// Filename: tessellatedmodelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TESSELLATEDMODELCLASS_H_
#define _TESSELLATEDMODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include<DirectXMath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: TessellatedModelClass
////////////////////////////////////////////////////////////////////////////////
class TessellatedModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	TessellatedModelClass();
	TessellatedModelClass(const TessellatedModelClass&);
	~TessellatedModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif