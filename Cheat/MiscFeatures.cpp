#include "stdafx.h"

MiscFeatures::CMiscFeatures::CMiscFeatures() {}

MiscFeatures::CMiscFeatures::~CMiscFeatures() {}

void MiscFeatures::CMiscFeatures::Execute( CUserCmd* cmd )
{
	Bunnyhop( cmd );
}

void MiscFeatures::CMiscFeatures::Bunnyhop( CUserCmd * cmd )
{
	auto pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );
	if (!pLocal || pLocal->LifeState())
		return;

	auto nFlags = pLocal->Flags();

	if (cmd->buttons & IN_JUMP && GetAsyncKeyState( VK_SPACE ))
	{
		if (!(nFlags & FL_ONGROUND))
			cmd->buttons &= ~IN_JUMP;
	}
}
