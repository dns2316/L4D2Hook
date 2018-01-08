#include "stdafx.h"

std::uintptr_t* uPredictionRandomSeed;
CBaseEntity* pPredictionPlayer;

float m_fOldCurtime;
float m_fOldFrametime;

int m_fFlags;
int m_nTickBase;

using namespace EnginePrediction;

CEnginePrediction::CEnginePrediction( CUserCmd* cmd, CBaseEntity* LocalPlayer ) :
	pCmd( cmd ),
	pLocal( LocalPlayer )
{
	CMoveData moveData;
	ZeroMemory( &moveData, sizeof( moveData ) );

	static bool bGotSeed = false;
	if (!bGotSeed) {
		uPredictionRandomSeed = *reinterpret_cast<std::uintptr_t**>(((reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x197D9) + 0x1));
		bGotSeed = true;
	}

	*uPredictionRandomSeed = pCmd->random_seed;
	pPredictionPlayer = pLocal;

	m_fOldCurtime = g_Interfaces->GlobalVars->curtime;
	m_fOldFrametime = g_Interfaces->GlobalVars->frametime;
	m_fFlags = pLocal->Flags();
	g_Interfaces->GlobalVars->curtime = pLocal->TickBase() * g_Interfaces->GlobalVars->interval_per_tick;
	g_Interfaces->GlobalVars->frametime = g_Interfaces->GlobalVars->interval_per_tick;
	moveData.m_nButtons = pCmd->buttons;


	g_Interfaces->GameMovement->StartTrackPredictionErrors( pLocal );
	m_nTickBase = pLocal->TickBase();

	g_Interfaces->MoveHelper->SetHost( pLocal );
	g_Interfaces->Prediction->SetupMove( pLocal, pCmd, g_Interfaces->MoveHelper, &moveData );
	g_Interfaces->GameMovement->ProcessMovement( pLocal, &moveData );
	g_Interfaces->Prediction->FinishMove( pLocal, pCmd, &moveData );
}

CEnginePrediction::~CEnginePrediction()
{
	pLocal->SetTickBase( m_nTickBase );
	g_Interfaces->GameMovement->FinishTrackPredictionErrors( pLocal );

	g_Interfaces->GlobalVars->curtime = m_fOldCurtime;
	g_Interfaces->GlobalVars->frametime = m_fOldFrametime;

	*uPredictionRandomSeed = -1;
	pPredictionPlayer = nullptr;
	g_Interfaces->MoveHelper->SetHost( nullptr );
	pLocal->SetFlags( m_fFlags );
}