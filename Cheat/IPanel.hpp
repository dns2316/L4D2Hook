#pragma once

class IPanel
{
public:
	const char* GetName( std::uint32_t iPanel )
	{
		return GetFunction<const char*(__thiscall*)(IPanel*, std::uint32_t)>( this, 36 )(this, iPanel);
	}
};
