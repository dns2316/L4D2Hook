#pragma once
#include "Misc.hpp"
#include "ClientClass.hpp"
#include "ICollideable.hpp"
#include "IVEngineClient.hpp"
#include "IClientEntity.hpp"
#include "CGlobalVarsBase.hpp"
#include "Entity.hpp"
#include "IClientEntityList.hpp"
#include "IEngineTrace.hpp"
#include "IVRenderView.hpp"
#include "IVModelRenderer.hpp"
#include "IMaterialSystem.hpp"
#include "IPanel.hpp"
#include "ISurface.hpp"
#include "IPrediction.hpp"

namespace Interfaces
{
	class CInterfaces
	{
	public:
		CInterfaces();
		~CInterfaces();

	private:
		bool Initialize();

	public:
		IVEngineClient* EngineClient;
		IClientEntityList* EntityList;
		CGlobalVarsBase* GlobalVars;
		IEngineTrace* Trace;
		IVRenderView* RenderView;
		IVModelRenderer* ModelRenderer;
		IMaterialSystem* MaterialSystem;
		CModelInfo* ModelInfo;
		IPanel* Panel;
		ISurface* Surface;
		IPrediction* Prediction;
		IGameMovement* GameMovement;
		IMoveHelper* MoveHelper;

	private:
		using FnCreateInterface = void*(__cdecl*)(const char* szName, std::int32_t* nReturnCode);
		FnCreateInterface GetModuleFactory( HMODULE hModule )
		{
			return reinterpret_cast<FnCreateInterface>(GetProcAddress( hModule, "CreateInterface" ));
		}

		template<typename T>
		T* CreateInterface( FnCreateInterface f, const char* szInterfaceVersion )
		{
			return reinterpret_cast<T*>(f( szInterfaceVersion, nullptr ));
		}
	};
}

extern std::unique_ptr<Interfaces::CInterfaces> g_Interfaces;