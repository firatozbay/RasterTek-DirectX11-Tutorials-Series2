////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightClass::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
	return;
}


void LightClass::SetLookAt(float x, float y, float z)
{
	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;
	return;
}


XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}


XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


XMFLOAT3 LightClass::GetPosition()
{
	return m_position;
}


void LightClass::GenerateViewMatrix()
{
	XMFLOAT3 up;
	XMVECTOR tmp_up, tmp_position, tmp_lookAt;

	// Setup the FLOAT that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	tmp_up = XMLoadFloat3(&up);
	tmp_position = XMLoadFloat3(&m_position);
	tmp_lookAt = XMLoadFloat3(&m_lookAt);

	// Create the view matrix from the three FLOATs.
    m_viewMatrix = XMMatrixLookAtLH(tmp_position, tmp_lookAt, tmp_up);

	return;
}


void LightClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void LightClass::GenerateOrthoMatrix(float width, float depthPlane, float nearPlane)
{
	// Create the orthographic matrix for the light.
	m_orthoMatrix = XMMatrixOrthographicLH(width, width, nearPlane, depthPlane);

	return;
}


void LightClass::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}


XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}