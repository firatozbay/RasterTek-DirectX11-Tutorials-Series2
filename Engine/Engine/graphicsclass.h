////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
//#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "modellistclass.h"
#include "frustumclass.h"
#include "multitextureshaderclass.h"
#include "lightmapshaderclass.h"
#include "alphamapshaderclass.h"
#include "bumpmapshaderclass.h"
#include "specmapshaderclass.h"
#include "rendertextureclass.h"
#include "debugwindowclass.h"
#include "fogshaderclass.h"
#include "clipplaneshaderclass.h"
#include "translateshaderclass.h"
#include "transparentshaderclass.h"
#include "reflectionshaderclass.h"
#include "fadeshaderclass.h"
//#include "fadebitmapclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include "glassshaderclass.h"
#include "fireshaderclass.h"
#include "depthshaderclass.h"
#include "horizontalblurshaderclass.h"
#include "verticalblurshaderclass.h"
#include "rendertextureclass.h"
#include "orthowindowclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true; 
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();	
	bool Frame(float,float,float);//(int, int, int, int, float,float);

private:
	bool Render(float);// (float, int, int);
	//bool RenderToTexture(float);//(float, int, int);
	//bool RenderScene(float, int, int);
	bool RenderScene();
	//bool RenderFadingScene();
	//bool RenderNormalScene(float);
	//bool RenderRefractionToTexture();
	//bool RenderReflectionToTexture();
	bool RenderSceneToTexture(float);
	bool DownSampleTexture();
	bool RenderHorizontalBlurToTexture();
	bool RenderVerticalBlurToTexture();
	bool UpSampleTexture();
	bool Render2DTextureScene();
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap; 
	TextClass* m_Text;
	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;
	MultiTextureShaderClass* m_MultiTextureShader;
	LightMapShaderClass* m_LightMapShader;
	AlphaMapShaderClass* m_AlphaMapShader;	
	BumpMapShaderClass* m_BumpMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	//RenderTextureClass* m_RenderTexture;
	DebugWindowClass* m_DebugWindow;
	TextureShaderClass* m_TextureShader;
	FogShaderClass* m_FogShader;
	ClipPlaneShaderClass* m_ClipPlaneShader;	
	TranslateShaderClass* m_TranslateShader;
	TransparentShaderClass* m_TransparentShader;
	//ModelClass* m_FloorModel;
	ReflectionShaderClass* m_ReflectionShader;	
	FadeShaderClass* m_FadeShader;
	float m_fadeInTime, m_accumulatedTime, m_fadePercentage;
	bool m_fadeDone;
	//FadeBitmapClass* m_FadeBitmap;
	//ModelClass *m_GroundModel, *m_WallModel, *m_BathModel, *m_WaterModel;
	RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;
	RefractionShaderClass* m_RefractionShader;
	WaterShaderClass* m_WaterShader;
	float m_waterHeight, m_waterTranslation;
	LightClass *m_Light1, *m_Light2, *m_Light3, *m_Light4;
	ModelClass* m_WindowModel;
	GlassShaderClass* m_GlassShader;
	FireShaderClass* m_FireShader;
	ModelClass *m_FloorModel, *m_BillboardModel;
	DepthShaderClass* m_DepthShader;
	HorizontalBlurShaderClass* m_HorizontalBlurShader;
	VerticalBlurShaderClass* m_VerticalBlurShader;
	RenderTextureClass *m_RenderTexture, *m_DownSampleTexure, *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexure;
	OrthoWindowClass *m_SmallWindow, *m_FullScreenWindow;
};

#endif