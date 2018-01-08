#pragma once

class IMaterial
{
public:
	inline void SetMaterialVarFlag( MaterialVarFlags_t flag, bool on )
	{
		return GetFunction<void( __thiscall* )(IMaterial*, MaterialVarFlags_t, bool)>( this, 29 )(this, flag, on);
	}

	inline void ColorModuleate( float r, float g, float b )
	{
		return GetFunction<void( __thiscall* )(IMaterial*, float, float, float)>( this, 28 )(this, r, g, b);
	}
};

class IMaterialSystem
{
public:
	IMaterial* FindMaterial( char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = 0 )
	{
		return GetFunction<IMaterial*(__thiscall*)(IMaterialSystem*, const char*, const char*, bool, const char*)>( this, 71 )(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
};

class CModelInfo
{
public:
	inline void* GetModel( int nIndex )
	{
		return GetFunction<void*(__thiscall*)(void*, int)>( this, 1 )(this, nIndex);
	}

	studiohdr_t* GetStudioModel( const model_t* model )
	{
		return GetFunction<studiohdr_t*(__stdcall*)(const model_t*)>( this, 30 )(model);
	}
};