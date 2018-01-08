#pragma once

class CBaseEntity : public IClientEntity
{
public:
	inline const bool LifeState()
	{
		return *(bool*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_lifeState);
	}

	inline const std::uint32_t Health()
	{
		return *(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_iHealth);
	}

	inline const std::uint32_t Sequence()
	{
		return *(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_nSequence);
	}

	inline const std::uint32_t TickBase()
	{
		return *(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_nTickbase);
	}

	inline const void SetTickBase( const std::uint32_t& tickbase )
	{
		*(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_nTickbase) = tickbase;
	}

	inline const std::uint8_t Team()
	{
		return *(std::uint8_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_nTeamNum);
	}

	inline const std::uint32_t Flags()
	{
		return *(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_fFlags);
	}

	inline const void SetFlags( const std::uint32_t& flags )
	{
		*(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_fFlags) = flags;
	}

	const GROUP GetGroup()
	{
		constexpr std::uint32_t m_Boss[] = { 275, 276 };
		constexpr std::uint32_t m_Special[] = { 0, 99, 269, 262, 264, 271 };
		constexpr std::uint32_t m_Infected = 263;
		constexpr std::uint32_t m_Player[] = { 231, 274 };

		std::uint32_t m_ClassID = this->GetClientClass()->m_ClassID;

		if (m_ClassID == m_Infected)
			return GROUP_INFECTED;

		else if (std::find( std::begin( m_Special ), std::end( m_Special ), m_ClassID ) != std::end( m_Special ))
			return GROUP_SPECIAL;

		else if (std::find( std::begin( m_Player ), std::end( m_Player ), m_ClassID ) != std::end( m_Player ))
			return GROUP_PLAYER;

		else if (std::find( std::begin( m_Boss ), std::end( m_Boss ), m_ClassID ) != std::end( m_Boss ))
			return GROUP_BOSS;

		return GROUP_INVALID;
	}

	const bool ValidEntity()
	{
		if (this->IsDormant())
			return false;

		const auto nTeam = this->Team();

		if (nTeam != 2 && nTeam != 3)
			return false;

		auto m_Group = this->GetGroup();
		auto m_Sequence = this->Sequence();
		auto m_SolidFlags = this->GetCollideable()->GetSolidFlags();

		if (m_Group == GROUP_INVALID)
			return false;

		if (m_Group == GROUP_BOSS)
		{
			if (m_SolidFlags & 4)
				return false;

			if (m_Sequence > 70)
				return false;
		}

		else if (m_Group == GROUP_SPECIAL)
		{
			if (m_SolidFlags & 4)
				return false;
		}

		else if (m_Group == GROUP_INFECTED)
		{
			if (m_SolidFlags & 4)
				return false;

			if (m_Sequence > 305)
				return false;
		}

		return true;
	}

	inline const Vector Origin()
	{
		return *(Vector*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_vecOrigin);
	}

	inline const Vector ViewOffset()
	{
		return *(Vector*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_vecViewOffset);
	}

	inline const Vector Eyes()
	{
		return Origin() + ViewOffset();
	}

	inline const Vector Punch()
	{
		return *(Vector*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_vecPunch);
	}

	inline const HANDLE WeaponHandle()
	{
		return *(HANDLE*)(reinterpret_cast<std::uintptr_t>(this) + g_Offsets.m_hActiveWeapon);
	}
};