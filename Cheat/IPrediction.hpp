#pragma once
#include "IGameMovement.hpp"
#include "IMoveHelper.hpp"

class IPrediction
{
public:
	void SetupMove( CBaseEntity* player, CUserCmd* cmd, IMoveHelper* pHelper, CMoveData* move )
	{
		GetFunction<void( __thiscall* )(IPrediction*, CBaseEntity*, CUserCmd*, IMoveHelper*, CMoveData*)>( this, 19 )(this, player, cmd, pHelper, move);
	}
	void FinishMove( CBaseEntity* player, CUserCmd* cmd, CMoveData* move )
	{
		GetFunction<void( __thiscall* )(IPrediction*, CBaseEntity*, CUserCmd*, CMoveData*)>( this, 20 )(this, player, cmd, move);
	}
};