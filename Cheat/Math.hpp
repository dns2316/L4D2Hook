#pragma once
#include "Vector.hpp"
#include "QAngle.hpp"
#include "VMatrix.hpp"

namespace Math
{
	float WorldDistance( const Vector& vecStart, const Vector& vecEnd );
	float AngleDistance( const Vector& vecStart, const Vector& vecEnd, const float& fDistance );
	float NormalizeAngle( const float& fAxis );
	float NormalizeVector( Vector& vec );
	float DotProduct( const Vector& a, const Vector& b );

	void VectorTransform( const Vector in1, float in2[3][4], Vector &out );

	Vector VectorAngles( const Vector& vecDirection );
	Vector GetBoneAngles( const Vector& BonePos, const Vector& LocalEyeAngles );
}

inline float Math::WorldDistance( const Vector& vecStart, const Vector& vecEnd )
{
	float fX = powf( vecEnd.x - vecStart.x, 2.f );
	float fY = powf( vecEnd.y - vecStart.y, 2.f );
	float fZ = powf( vecEnd.z - vecStart.z, 2.f );

	return sqrtf( fX + fY + fZ );
}

inline float Math::AngleDistance( const Vector& vecStart, const Vector& vecEnd, const float& fDistance )
{
	Vector vecDifference = vecEnd - vecStart;

	float fPitch = ((DEG2RAD( fabsf( vecDifference.x ) ) * fDistance) * 0.1905f);
	float fYaw = ((DEG2RAD( fabsf( vecDifference.y ) ) * fDistance) * 0.1905f);

	return sqrtf( powf( fPitch, 2.f ) + powf( fYaw, 2.f ) );
}

inline float Math::NormalizeAngle( const float& fAxis )
{
	return std::isfinite( fAxis ) ? std::remainder( fAxis, 360.0f ) : 0.f;
}

inline float Math::NormalizeVector( Vector& vec )
{
	const float fLength = vec.Length();
	vec = fLength ? vec / fLength : Vector();

	return fLength;
}

inline Vector Math::VectorAngles( const Vector& vecDirection )
{
	float fPitch, fYaw = 0.f;

	if (vecDirection.x && vecDirection.y)
	{
		fPitch = RAD2DEG( std::atan2f( -vecDirection.z, vecDirection.Length2D() ) );
		fPitch += fPitch < 0.f ? 360.f : 0.f;

		fYaw = RAD2DEG( std::atan2f( vecDirection.y, vecDirection.x ) );
		fYaw += fYaw < 0.f ? 360.f : 0.f;
	}
	else
	{
		fPitch = vecDirection.z > 0.f ? 270.f : 90.f;
	}

	return Vector( fPitch, fYaw, 0.f );
}

inline Vector Math::GetBoneAngles( const Vector& BonePos, const Vector& LocalEyeAngles )
{
	Vector vecForward = BonePos - LocalEyeAngles;
	Math::NormalizeVector( vecForward );

	Vector vecAngles = Math::VectorAngles( vecForward );
	return vecAngles;
}

inline float Math::DotProduct( const Vector& a, const Vector& b )
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline void Math::VectorTransform( const Vector in1, float in2[3][4], Vector &out )
{
	out[0] = Math::DotProduct( in1, Vector( in2[0][0], in2[0][1], in2[0][2] ) ) + in2[0][3];
	out[1] = Math::DotProduct( in1, Vector( in2[1][0], in2[1][1], in2[1][2] ) ) + in2[1][3];
	out[2] = Math::DotProduct( in1, Vector( in2[2][0], in2[2][1], in2[2][2] ) ) + in2[2][3];
}