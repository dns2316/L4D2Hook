#include "stdafx.h"

using namespace Aimbot;

CAimbot::CAimbot() {}
CAimbot::~CAimbot() {}

void CAimbot::Execute( CUserCmd* cmd )
{
	if (g_Config.m_nAimMode == Config::AIMBOT_MODE::AIMBOT_OFF)
		return;

	pLocal = nullptr;
	pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );

	if (!pLocal || pLocal->LifeState())
		return;

	if (!(GetAsyncKeyState( g_Config.m_nAimkey ) & 0x8000))
		return;

	auto pWeapon = reinterpret_cast<C_BaseCombatWeapon*>(g_Interfaces->EntityList->GetClientEntityFromHandle( pLocal->WeaponHandle() ));
	if (!pWeapon)
		return;

	if (!(pWeapon->GetCSWpnData()->iMaxClip1 > 1))
		return;

	auto nTarget = GetBestTarget();
	if (nTarget == 1337)
		return;

	auto pEntity = g_Interfaces->EntityList->GetClientEntity( nTarget );

	auto nAimBone = Utils::GetHeadHitboxID( pEntity->GetClientClass()->m_ClassID );
	if (!nAimBone)
		return;

	cmd->viewangles = Math::GetBoneAngles( Utils::GetHitbox( pEntity, nAimBone ), pLocal->Eyes() );
	CompensateSpread( cmd );
	CompensateRecoil( cmd );

	static bool bFired = false;
	if (!bFired)
		cmd->buttons |= IN_ATTACK;

	bFired = !bFired;
}

std::uint32_t CAimbot::GetBestTarget()
{
	std::uint32_t nBestTarget = 1337;
	float fBestDistance = FLT_MAX;

	for (std::uint32_t nIndex = 1; nIndex < g_Interfaces->EntityList->GetHighestEntityIndex(); nIndex++)
	{
		auto pEntity = g_Interfaces->EntityList->GetClientEntity( nIndex );
		if (!pEntity || pEntity == pLocal || !pEntity->ValidEntity())
			continue;

		if (pEntity->Team() == pLocal->Team())
			continue;

		auto nBone = Utils::GetHeadHitboxID( pEntity->GetClientClass()->m_ClassID );
		if (!nBone)
			continue;

		if (!Utils::Visible( pEntity, nBone ))
			continue;

		if (pEntity->GetClientClass()->m_ClassID == ClassID::Witch && pEntity->Sequence() == 4)
			continue;

		float fCurrentDistance = Math::WorldDistance( pEntity->Origin(), pLocal->Origin() );
		if (fCurrentDistance < fBestDistance)
		{
			fBestDistance = fCurrentDistance;
			nBestTarget = nIndex;
		}
	}

	return nBestTarget;
}

void CAimbot::CompensateRecoil( CUserCmd* cmd )
{
	auto p = pLocal->Punch();
	cmd->viewangles.x -= p.x;
	cmd->viewangles.y -= p.y;
}

#pragma optimize( "", off )  
void CAimbot::CompensateSpread( CUserCmd* cmd )
{
	static const char* szHorizSpread = "CTerrorGun::FireBullet HorizSpread";
	static const char* szVertSpread = "CTerrorGun::FireBullet VertSpread";

	using FnSharedRandomFloat = float( __cdecl* )(const char*, float, float, int);
	using FnUpdateMaxSpread = void( __cdecl* )(C_BaseCombatWeapon*);

	static auto uSharedRandomFloat = reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x1A8170;
	static auto SharedRandomFloat = reinterpret_cast<FnSharedRandomFloat>(uSharedRandomFloat);

	static auto UpdateMaxSpread = reinterpret_cast<FnUpdateMaxSpread>((reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" ))) + 0x2ECAF0);

	static std::uintptr_t uSeed = uSharedRandomFloat + 7;
	static std::uintptr_t** pSeed = (std::uintptr_t**)uSeed;

	std::uintptr_t uOldSeed = **pSeed;
	**pSeed = cmd->random_seed;

	auto pWeapon = reinterpret_cast<C_BaseCombatWeapon*>(g_Interfaces->EntityList->GetClientEntityFromHandle( pLocal->WeaponHandle() ));
	if (!pWeapon)
		return;

	if (!(pWeapon->GetCSWpnData()->iMaxClip1 > 1))
		return;

	float fOldMaxSpread = pWeapon->MaxSpread();
	UpdateMaxSpread( pWeapon );
	float fMaxSpread = pWeapon->MaxSpread();

	float fSpreadX = SharedRandomFloat( szHorizSpread, -fMaxSpread, fMaxSpread, 0 );
	float fSpreadY = SharedRandomFloat( szVertSpread, -fMaxSpread, fMaxSpread, 0 );

	*(float*)(reinterpret_cast<std::uintptr_t>(pWeapon) + 0xD0C) = fOldMaxSpread;

	**pSeed = uOldSeed;

	cmd->viewangles.x -= fSpreadX;
	cmd->viewangles.y -= fSpreadY;
}
#pragma optimize( "", on ) 