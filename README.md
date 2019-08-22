# Rastertek DirectX 11 Tutorials Series 2 Converted Examples
The engine from the RasterTek DirectX 11 Tutorials, the code from the their older tutorials are edited to work with Windows SDK.
The progress is up to Tutorial 50 at this time, but the code can be used only as a reference for closer tutorials now as the every class changes drastically in one tutorial for one application then gets reverted back to another more primitive for another application.
I will be dividing each tutorials source codes in different files for the prople who need a reference for their part.

The important conversion issues I want to note are:
- DDS Texture Loader (The working solution can be found in the textureclass.cpp file), but you will be needing the DirectXTK library using the NuGet package manager(that's how I got my anyways)
- The difference between XMVECTORs and D3DXVECTORS: XMVECTORs are not meant to be stored in the memory, instead XMFLOATs are meant to be stored. Both XMFLOAT4 and XMFLOAT3 can be converted into XMVECTOR with the:
XMLoadFloat#(&floatName)
functions. Then the newly created XMVECTORs can be used as input for some application specific functions.
- The shader compiler for many shader classes should look like this:
D3DCompileFromFile(vsFilename, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
instead of:
D3DX11CompileFromFile(vsFilename, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
								   &vertexShaderBuffer, &errorMessage, NULL);
But you will be needing:
#include <d3dcompiler.h>
instead of:
#include <d3dx11async.h>

I will be updating this readme a bit more as I find more issues I should explain.


Rastertek DirectX 11 Tutorials - Series 2: http://www.rastertek.com/tutdx11s2.html

Rastertek DirectX 11 Tutorials - Series 1: http://www.rastertek.com/tutdx11.html

