#pragma once

class ICollideable
{
public:
	virtual ~ICollideable() {};

	SolidFlags_t GetSolid()
	{
		return GetFunction<SolidFlags_t( __thiscall* )(ICollideable*)>( this, 11 )(this);
	}

	unsigned short GetSolidFlags()
	{
		return GetFunction<unsigned short( __thiscall* )(ICollideable*)>( this, 12 )(this);
	}
};
