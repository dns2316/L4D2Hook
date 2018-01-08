#include "stdafx.h"

using namespace ESP;

CESP::CESP() :
	pLocal(nullptr)
{
	if (!this->Initialize())
		printf( "ESP failed initialization.\n" );
}

CESP::~CESP(){}

void CESP::Execute()
{
	DrawWatermark();

	if (!g_Config.m_bESP)
		return;

	pLocal = nullptr;
	pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );

	if (!pLocal)
		return;

	for (std::uint32_t nIndex = 1; nIndex < g_Interfaces->EntityList->GetHighestEntityIndex(); nIndex++)
	{
		auto pEntity = g_Interfaces->EntityList->GetClientEntity( nIndex );
		if (!pEntity || pEntity == pLocal || pEntity->IsDormant())
			continue;

		std::int32_t nClassID = pEntity->GetClientClass()->m_ClassID;
		if (pEntity->GetGroup() && pEntity->ValidEntity())
			DrawPlayer( pEntity );

		else if (nClassID == ClassID::CWeaponSpawn || nClassID == ClassID::CWeaponAmmoSpawn)
			DrawDrop( pEntity );

		else if (pEntity->Team() == 2)
		{
			auto pWeapon = reinterpret_cast<C_BaseCombatWeapon*>(pEntity);
			if (pWeapon->Owner() == INVALID_HANDLE_VALUE)
				DrawDrop( pEntity );
		}
	}
}

bool CESP::Initialize()
{
	this->m_ESPFont = g_Interfaces->Surface->Create_Font();
	if (!m_ESPFont)
		return false;

	if (!g_Interfaces->Surface->SetFontGlyphSet( m_ESPFont, "Helvetica-Bold", 14, 700, 0, 0, FONTFLAG_DROPSHADOW ))
		return false;

	return true;
}

void CESP::DrawWatermark()
{
	static wchar_t szWatermark[128];
	static bool bGotWatermark = false;
	if (!bGotWatermark)
	{
		if (!MultiByteToWideChar( CP_UTF8, 0, "l4d2hook by tni", -1, szWatermark, 128 ) > 0)
			return;

		bGotWatermark = true;
	}

	g_Interfaces->Surface->DrawSetTextFont( m_ESPFont );
	g_Interfaces->Surface->DrawSetTextColor( 255, 255, 255, 255 );
	g_Interfaces->Surface->DrawSetTextPos( 10, 10 );
	g_Interfaces->Surface->DrawPrintText( szWatermark, wcslen( szWatermark ) );
}

void CESP::DrawPlayer( CBaseEntity * pEntity )
{
	Vector Origin3D = pEntity->Origin();
	Vector Origin;

	if (!Utils::WorldToScreen( Origin3D, Origin ))
		return;

	Vector Head3D = Utils::GetHitbox( pEntity, Utils::GetHeadHitboxID( pEntity->GetClientClass()->m_ClassID ) );
	Head3D.z += 15.0f;
	Vector Head;

	if (!Utils::WorldToScreen( Head3D, Head ))
		return;
	
	float h = fabs( Head.y - Origin.y );
	float w = h / 1.65f;

	RECT rect = {
		static_cast<long>(Origin.x - w * 0.5f),
		static_cast<long>(Head.y),
		static_cast<long>(w),
		static_cast<long>(Origin.y)
	};

	rect.right += static_cast<long>(rect.left);

	DrawBox( rect );
	DrawSkeleton( pEntity );

	std::int32_t nClassID = pEntity->GetClientClass()->m_ClassID;

	g_Interfaces->Surface->DrawSetTextFont( m_ESPFont );
	g_Interfaces->Surface->DrawSetTextColor( 255, 255, 255, 255 );

	if (nClassID == ClassID::Infected)
	{
		static bool b = false;
		static const char* szInfected = "Infected";
		static wchar_t wbuf[128];
		if (!b)
		{
			if (!MultiByteToWideChar( CP_UTF8, 0, szInfected, -1, wbuf, 128 ) > 0)
				return;

			b = true;
		}

		g_Interfaces->Surface->DrawSetTextPos( rect.left, rect.bottom );
		g_Interfaces->Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
	}

	else if (pEntity->GetGroup() == GROUP_SPECIAL)
	{
		char buffer[128];
		wchar_t wbuf[128];
		sprintf_s( buffer, sizeof( buffer ), "%s (%d)", pEntity->GetClientClass()->m_pNetworkName, pEntity->Health() );
		if (MultiByteToWideChar( CP_UTF8, 0, buffer, -1, wbuf, 128 ) > 0)
		{
			g_Interfaces->Surface->DrawSetTextPos( rect.left, rect.bottom );
			g_Interfaces->Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
		}
	}

	else
	{
		wchar_t wbuf[128];
		if (MultiByteToWideChar( CP_UTF8, 0, pEntity->GetClientClass()->m_pNetworkName, -1, wbuf, 128 ) > 0)
		{
			g_Interfaces->Surface->DrawSetTextPos( rect.left, rect.bottom );
			g_Interfaces->Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
		}
	}
}

void CESP::DrawDrop( CBaseEntity* pEntity )
{
	std::int32_t nClassID = pEntity->GetClientClass()->m_ClassID;
	auto pWeapon = reinterpret_cast<C_BaseCombatWeapon*>(pEntity);
	Vector Origin3D = pEntity->Origin();

	if (Math::WorldDistance( Origin3D, pLocal->Origin() ) > ESP_WORLD_MAX_RANGE)
		return;

	Vector Origin;
	if (!Utils::WorldToScreen( Origin3D, Origin ))
		return;

	g_Interfaces->Surface->DrawSetTextFont( m_ESPFont );
	g_Interfaces->Surface->DrawSetTextColor( 0, 255, 0, 255 );

	wchar_t wbuf[128];
	if (MultiByteToWideChar( CP_UTF8, 0, (nClassID == ClassID::CWeaponSpawn)
		? pWeapon->WeaponAlias( pWeapon->GetWeaponId() )
		: (nClassID == ClassID::CWeaponAmmoSpawn)
		? "Ammo"
		: pWeapon->GetCSWpnData()->szClassName, -1, wbuf, 128 ) > 0)
	{
		g_Interfaces->Surface->DrawSetTextPos( Origin.x, Origin.y );
		g_Interfaces->Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
	}
}

void CESP::DrawBox( const RECT& rect )
{
	g_Interfaces->Surface->DrawSetColor( 0, 255, 0, 255 );
	g_Interfaces->Surface->DrawOutlinedRect( rect.left, rect.top, rect.right, rect.bottom );
}

void CESP::DrawSkeleton( CBaseEntity* pEntity )
{
	auto StudioModel = g_Interfaces->ModelInfo->GetStudioModel( pEntity->GetModel() );
	if (!StudioModel)
		return;

	static matrix3x4 matrix[128];
	if (!pEntity->SetupBones( matrix, 128, 0x100, g_Interfaces->GlobalVars->curtime ))
		return;

	g_Interfaces->Surface->DrawSetColor( 255, 255, 255, 255 );

	for (std::uint32_t i = 0; i < StudioModel->numbones; i++)
	{
		auto m_Bone = StudioModel->GetBone( i );
		if (!m_Bone || !(m_Bone->flags & 256) || m_Bone->parent == -1)
			continue;

		Vector vecBonePos;
		if (!Utils::WorldToScreen( Vector( matrix[i][0][3], matrix[i][1][3], matrix[i][2][3] ), vecBonePos ))
			continue;

		Vector vecBoneParent;
		if (!Utils::WorldToScreen( Vector( matrix[m_Bone->parent][0][3], matrix[m_Bone->parent][1][3], matrix[m_Bone->parent][2][3] ), vecBoneParent ))
			continue;

		g_Interfaces->Surface->DrawLine( vecBonePos.x, vecBonePos.y, vecBoneParent.x, vecBoneParent.y );
	}
}