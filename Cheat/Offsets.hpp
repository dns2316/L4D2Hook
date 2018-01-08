#pragma once

namespace Offsets
{
	struct SOffsets
	{
		std::uintptr_t m_iHealth = 0xEC;
		std::uintptr_t m_nTeamNum = 0xE4;
		std::uintptr_t m_vecOrigin = 0x94;
		std::uintptr_t m_lifeState = 0x147;
		std::uintptr_t m_fFlags = 0xF0;
		std::uintptr_t m_vecViewOffset = 0xF4;
		std::uintptr_t m_nSequence = 0x8A4;
		std::uintptr_t m_hActiveWeapon = 0x10A4;
		std::uintptr_t m_weaponID = 0x958;
		std::uintptr_t m_fMaxSpread = 0xD0C;
		std::uintptr_t m_hOwnerEntity = 0x138;
		std::uintptr_t m_nTickbase = 0x14EC;
		std::uintptr_t m_iWeaponID = 0x2C;
		std::uintptr_t m_vecPunch = 0x1224;
	};
}

extern Offsets::SOffsets g_Offsets;