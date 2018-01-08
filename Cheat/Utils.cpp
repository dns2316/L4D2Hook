#include "stdafx.h"

static bool ScreenTransform( const Vector& in, Vector& out )
{
	auto& w2sMatrix = g_Interfaces->EngineClient->WorldToScreenMatrix();

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool Utils::WorldToScreen( const Vector & in, Vector & out )
{
	static std::int32_t w = 0;
	static std::int32_t h = 0;
	if (!w || !h)
		g_Interfaces->EngineClient->GetScreenSize( w, h );

	if (!ScreenTransform( in, out ))
		return false;

	out.x = (w / 2.0f) + (out.x * w) / 2.0f;
	out.y = (h / 2.0f) - (out.y * h) / 2.0f;

	return true;
}

bool Utils::Visible( CBaseEntity * pEntity, std::uint8_t nBone )
{
	Ray_t ray;
	trace_t trace;

	auto pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );

	if (!pLocal)
		return false;

	ray.Init( pLocal->Eyes(), GetHitbox( pEntity, nBone ) );

	CTraceFilter filter;
	filter.pSkip = pLocal;

	g_Interfaces->Trace->TraceRay( ray, MASK_SOLID, &filter, &trace );

	if (trace.m_pEnt == pEntity || trace.fraction == 1.f)
		return true;

	return false;
}

Vector Utils::GetHitbox( CBaseEntity * pEntity, std::int8_t nHitbox )
{
	matrix3x4 matrix[128];

	if (pEntity->SetupBones( matrix, 128, 0x100, 0.f ))
	{
		studiohdr_t* hdr = g_Interfaces->ModelInfo->GetStudioModel( pEntity->GetModel() );
		mstudiohitboxset_t* set = hdr->GetHitboxSet( 0 );

		mstudiobbox_t* hitbox = set->GetHitbox( nHitbox );

		if (hitbox)
		{
			Vector vMin, vMax, vCenter;
			Math::VectorTransform( hitbox->bbmin, matrix[hitbox->bone], vMin );
			Math::VectorTransform( hitbox->bbmax, matrix[hitbox->bone], vMax );

			
			vCenter = ((vMin + vMax) * 0.5f);

			return vCenter;
		}

	}

	return Vector{ 0,0,0 };
}

std::uint8_t Utils::GetHeadHitboxID( const std::uint32_t & nClassID )
{
	switch (nClassID)
	{
	case ClassID::Infected:
		return 15;
		break;

	case ClassID::Tank:
		return 12;
		break;

	case ClassID::Spitter:
		return 4;
		break;

	case ClassID::Jockey:
		return 4;
		break;

	case ClassID::Charger:
		return 9;

	default:
		return 10;
		break;
	}
}
