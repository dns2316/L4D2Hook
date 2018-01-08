#pragma once

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {};
};

class IClientUnknown
{
public:
	virtual ~IClientUnknown() {};

	ICollideable* GetCollideable()
	{
		return GetFunction<ICollideable*(__thiscall*)(IClientUnknown*)>( this, 3 )(this);
	}
};

class IClientThinkable {
public:
	virtual ~IClientThinkable() {};
};

struct model_t;

class IClientRenderable
{
public:
	virtual ~IClientRenderable() {};

	inline model_t* GetModel()
	{
		return GetFunction<model_t*(__thiscall*)(IClientRenderable*)>( this, 8 )(this);
	}

	inline int DrawModel( int flags, float alpha = 1.f )
	{
		return GetFunction<int( __thiscall* )(IClientRenderable*, int, float)>( this, 9 )(this, flags, alpha);
	}

	inline bool SetupBones( matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
	{
		return GetFunction<bool( __thiscall* )(IClientRenderable*, matrix3x4*, int, int, float)>( this, 13 )(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};

	inline ClientClass* GetClientClass()
	{
		return GetFunction<ClientClass*(__thiscall*)(IClientNetworkable*)>( this, 1 )(this);
	}

	inline bool IsDormant()
	{
		return GetFunction<bool( __thiscall* )(IClientNetworkable*)>( this, 7 )(this);
	}

	inline const int GetIndex()
	{
		return GetFunction<int( __thiscall* )(IClientNetworkable*)>( this, 8 )(this);
	}
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual ~IClientEntity() {};
};

class C_BaseCombatWeapon
{
public:
	float MaxSpread()
	{
		return *(float*)(reinterpret_cast<uintptr_t>(this) + g_Offsets.m_fMaxSpread);
	}

	int GetWeaponId()
	{
		return *(int*)(reinterpret_cast<uintptr_t>(this) + g_Offsets.m_weaponID);
	}

	HANDLE Owner()
	{
		return *(HANDLE*)(reinterpret_cast<uintptr_t>(this) + g_Offsets.m_hOwnerEntity);
	}

	FileWeaponInfo_t* GetCSWpnData()
	{
		static std::uintptr_t FnGetCSWpnData = reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x148A0;
		return ((FileWeaponInfo_t*(__thiscall*)(C_BaseCombatWeapon*))(FnGetCSWpnData))(this);
	}

	const char* WeaponAlias( const std::uint32_t& nWeaponID )
	{
		static auto FnWeaponIDToAlias = (char*(*)(std::uint32_t))(reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x22C770);
		return FnWeaponIDToAlias( nWeaponID );
	}
};
