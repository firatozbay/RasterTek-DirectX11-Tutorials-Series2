////////////////////////////////////////////////////////////////////////////////
// Filename: frustumclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "frustumclass.h"


FrustumClass::FrustumClass()
{
}


FrustumClass::FrustumClass(const FrustumClass& other)
{
}


FrustumClass::~FrustumClass()
{
}


void FrustumClass::ConstructFrustum(float screenDepth, XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	float zMinimum, r;
	XMMATRIX matrix;


	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix.r[3].m128_f32[2] / projectionMatrix.r[2].m128_f32[2];
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix.r[2].m128_f32[2] = r;
	projectionMatrix.r[3].m128_f32[2] = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);
	
	XMVECTOR tmp_vector;


	// Calculate near plane of frustum.
	m_planes[0].x = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[2];
	m_planes[0].y = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[2];
	m_planes[0].z = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[2];
	m_planes[0].w = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[2];
	tmp_vector = XMLoadFloat4(&m_planes[0]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[0], tmp_vector);

	// Calculate far plane of frustum.
	m_planes[1].x = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[2];
	m_planes[1].y = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[2];
	m_planes[1].z = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[2];
	m_planes[1].w = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[2];
	tmp_vector = XMLoadFloat4(&m_planes[1]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[1], tmp_vector);
	// Calculate left plane of frustum.
	m_planes[2].x = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[0];
	m_planes[2].y = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[0];
	m_planes[2].z = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[0];
	m_planes[2].w = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[0];
	tmp_vector = XMLoadFloat4(&m_planes[2]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[2], tmp_vector);
	// Calculate right plane of frustum.
	m_planes[3].x = matrix.r[0].m128_f32[3] - matrix.r[0].m128_f32[0];
	m_planes[3].y = matrix.r[1].m128_f32[3] - matrix.r[1].m128_f32[0];
	m_planes[3].z = matrix.r[2].m128_f32[3] - matrix.r[2].m128_f32[0];
	m_planes[3].w = matrix.r[3].m128_f32[3] - matrix.r[3].m128_f32[0];
	tmp_vector = XMLoadFloat4(&m_planes[3]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[3], tmp_vector);
	XMVECTOR a;
	// Calculate top plane of frustum.
	m_planes[4].x = matrix.r[0].m128_f32[3] - matrix.r[0].m128_f32[1];
	m_planes[4].y = matrix.r[1].m128_f32[3] - matrix.r[1].m128_f32[1];
	m_planes[4].z = matrix.r[2].m128_f32[3] - matrix.r[2].m128_f32[1];
	m_planes[4].w = matrix.r[3].m128_f32[3] - matrix.r[3].m128_f32[1];
	tmp_vector = XMLoadFloat4(&m_planes[4]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[4], tmp_vector);
	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix.r[0].m128_f32[3] + matrix.r[0].m128_f32[1];
	m_planes[5].y = matrix.r[1].m128_f32[3] + matrix.r[1].m128_f32[1];
	m_planes[5].z = matrix.r[2].m128_f32[3] + matrix.r[2].m128_f32[1];
	m_planes[5].w = matrix.r[3].m128_f32[3] + matrix.r[3].m128_f32[1];
	tmp_vector = XMLoadFloat4(&m_planes[5]);
	XMPlaneNormalize(tmp_vector);
	XMStoreFloat4(&m_planes[5], tmp_vector);

	return;
}


bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;


	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i<6; i++)
	{
		XMVECTOR vector = XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4(x, y, z, 1.0f)));

		if (vector.m128_f32[0] < 0.0f)
		{
			return false;
		}
	}

	return true;
}


bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter - radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter - radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter - radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter - radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter + radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter + radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter + radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter + radius), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}


bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4(xCenter, yCenter, zCenter, 1.0f))).m128_f32[0] < -radius)
		{
			return false;
		}
	}

	return true;
}


bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}
		return false;
	}

	return true;
}