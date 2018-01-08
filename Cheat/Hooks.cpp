#include "stdafx.h"
#include "checksum.hpp"

std::unique_ptr<VMTHook> g_RenderViewHook;
std::unique_ptr<VMTHook> g_ClientModeHook;
std::unique_ptr<VMTHook> g_PanelHook;

void Hooks::Initialize()
{
	g_RenderViewHook = std::make_unique<VMTHook>( g_Interfaces->RenderView );
	if (g_RenderViewHook->HookFunction( Hooks::SceneEnd, 9 ))
		printf( "Hooked SceneEnd.\n" );

	auto GetClientMode = (void*(__cdecl*)())(reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x223470);
	void* ClientMode = GetClientMode();
	g_ClientModeHook = std::make_unique<VMTHook>( ClientMode );
	if (g_ClientModeHook->HookFunction( Hooks::CreateMove, 27 ))
		printf( "Hooked ClientMode::CreateMove.\n" );

	g_PanelHook = std::make_unique<VMTHook>( g_Interfaces->Panel );
	if (g_PanelHook->HookFunction( Hooks::PaintTraverse, 41 ))
		printf( "Hooked PaintTraverse.\n" );
}

void Hooks::Unhook()
{
	g_RenderViewHook->UnhookFunction( 9 );
	g_ClientModeHook->UnhookFunction( 27 );
	g_PanelHook->UnhookFunction( 41 );
	printf( "Uninjected.\n" );
}

void __fastcall Hooks::SceneEnd( void * thisptr, void * edx )
{
	static auto oSceneEnd = g_RenderViewHook->GetOriginalFunction<FnSceneEnd>( 9 );
	oSceneEnd( edx );

	if (!g_Config.m_bChams)
		return;

	auto pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );
	if (!pLocal)
		return;

	static IMaterial* pMaterial = nullptr;
	if (!pMaterial)
	{
		pMaterial = g_Interfaces->MaterialSystem->FindMaterial( "debug/debugambientcube", "Model textures" );
		pMaterial->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
		pMaterial->ColorModuleate( 1.f, 1.f, 1.f );
	}

	for (std::uint32_t nIndex = 1; nIndex < g_Interfaces->EntityList->GetHighestEntityIndex(); nIndex++)
	{
		auto pEntity = g_Interfaces->EntityList->GetClientEntity( nIndex );
		if (!pEntity || pEntity == pLocal || !pEntity->ValidEntity())
			continue;

		g_Interfaces->ModelRenderer->ForcedMaterialOverride( pMaterial );
		pEntity->DrawModel( 0x1 );
		g_Interfaces->ModelRenderer->ForcedMaterialOverride( nullptr );

	}
}

bool __stdcall Hooks::CreateMove( float flInputSampleTime, CUserCmd * pCmd )
{
	static auto g_Aimbot = std::make_unique<Aimbot::CAimbot>();
	static auto g_Misc = std::make_unique<MiscFeatures::CMiscFeatures>();

	if (!pCmd->command_number)
		return false;

	auto pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );
	if (!pLocal)
		return false;

	pCmd->random_seed = MD5_PseudoRandom( pCmd->command_number ) & 0x7fffffff;

	g_Misc->Execute( pCmd );

	EnginePrediction::CEnginePrediction EnginePred = EnginePrediction::CEnginePrediction( pCmd, pLocal );
	g_Aimbot->Execute( pCmd );

	return !(g_Config.m_nAimMode == Config::AIMBOT_MODE::AIMBOT_SILENT);
}

void __stdcall Hooks::PaintTraverse( std::uint32_t nPanel, bool bForceRepaint, bool bAllowForce )
{
	static FnPaintTraverse oPaintTraverse = g_PanelHook->GetOriginalFunction<FnPaintTraverse>( 41 );
	oPaintTraverse( g_Interfaces->Panel, nPanel, bForceRepaint, bAllowForce );

	static auto g_ESP = std::make_unique<ESP::CESP>();
	static auto g_Menu = std::make_unique<Menu::CMenu>();

	static std::uint32_t nDrawPanel = 0;
	if (!nDrawPanel)
	{
		if (!strcmp( g_Interfaces->Panel->GetName( nPanel ), "FocusOverlayPanel" ))
			nDrawPanel = nPanel;
		else
			return;
	}

	if (nPanel != nDrawPanel)
		return;

	if (!g_Interfaces->EngineClient->IsInGame() || !g_Interfaces->EngineClient->IsConnected())
		return;

	g_ESP->Execute();
	g_Menu->Execute();
}
