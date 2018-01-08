#pragma once

namespace Hooks
{
	using FnSceneEnd = void( __thiscall* )(void*);
	using FnPaintTraverse = void( __thiscall* )(IPanel*, std::uint32_t, bool, bool);

	extern void Initialize();
	extern void Unhook();

	extern void __fastcall SceneEnd( void* thisptr, void* edx );
	extern bool __stdcall CreateMove( float flInputSampleTime, CUserCmd* pCmd );
	extern void __stdcall PaintTraverse( std::uint32_t nPanel, bool bForceRepaint, bool bAllowForce );
}