#pragma once

namespace Utils
{
	bool WorldToScreen( const Vector& in, Vector& out );
	bool Visible( CBaseEntity* pEntity, std::uint8_t nBone );
	Vector GetHitbox( CBaseEntity* pEntity, std::int8_t nHitbox );
	std::uint8_t GetHeadHitboxID( const std::uint32_t& nClassID );
}