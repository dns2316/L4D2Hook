#pragma once

class IVEngineClient
{
public:
	inline void GetScreenSize( std::int32_t& w, std::int32_t& h )
	{
		return GetFunction<void( __thiscall* )(IVEngineClient*, std::int32_t&, std::int32_t&)>( this, 5 )(this, w, h);
	}

	inline void ClientCmd( const char* cmd )
	{
		return GetFunction<void( __thiscall* )(IVEngineClient*, const char*)>( this, 7 )(this, cmd);
	}

	inline int const GetLocalPlayer()
	{
		return GetFunction<int( __thiscall* )(IVEngineClient*)>( this, 12 )(this);
	}

	inline void GetViewAngles( Vector& vAngles )
	{
		return GetFunction<void( __thiscall* )(IVEngineClient*, Vector&)>( this, 19 )(this, vAngles);
	}

	inline void SetViewAngles( Vector& vAngles )
	{
		return GetFunction<void( __thiscall* )(IVEngineClient*, Vector&)>( this, 20 )(this, vAngles);
	}

	inline bool IsInGame()
	{
		return GetFunction<bool( __thiscall* )(IVEngineClient*)>( this, 26 )(this);
	}

	inline bool IsConnected()
	{
		return GetFunction<bool( __thiscall* )(IVEngineClient*)>( this, 27 )(this);
	}

	const VMatrix& WorldToScreenMatrix()
	{
		return GetFunction<VMatrix&( __thiscall* )(IVEngineClient*)>( this, 37 )(this);
	}
};