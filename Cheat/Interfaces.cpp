#include "stdafx.h"

std::unique_ptr<Interfaces::CInterfaces> g_Interfaces;
using namespace Interfaces;

CInterfaces::CInterfaces() :
	EngineClient( nullptr ), EntityList( nullptr ), GlobalVars( nullptr ), Trace( nullptr ),
	RenderView( nullptr ), ModelRenderer( nullptr ), MaterialSystem( nullptr ), ModelInfo( nullptr ),
	Panel( nullptr ), Surface( nullptr ), Prediction( nullptr ), GameMovement( nullptr ), MoveHelper( nullptr )
{
	this->Initialize()
		? printf( "Interfaces initialized.\n" )
		: printf( "Interfaces failed initialization." );
}

CInterfaces::~CInterfaces(){}

bool CInterfaces::Initialize()
{
	auto ClientFactory = GetModuleFactory( GetModuleHandleA( "client.dll" ) );
	auto EngineFactory = GetModuleFactory( GetModuleHandleA( "engine.dll" ) );
	auto MatSysFactory = GetModuleFactory( GetModuleHandleA( "materialsystem.dll" ) );
	auto VGUIFactory = GetModuleFactory( GetModuleHandleA( "vguimatsurface.dll" ) );
	auto VGUI2Factory = GetModuleFactory( GetModuleHandleA( "vgui2.dll" ) );

	this->EngineClient = CreateInterface<IVEngineClient>( EngineFactory, "VEngineClient013" );
	this->EntityList = CreateInterface<IClientEntityList>( ClientFactory, "VClientEntityList003" );
	this->Trace = CreateInterface<IEngineTrace>( EngineFactory, "EngineTraceClient003" );
	this->RenderView = CreateInterface<IVRenderView>( EngineFactory, "VEngineRenderView013" );
	this->ModelRenderer = CreateInterface<IVModelRenderer>( EngineFactory, "VEngineModel016" );
	this->MaterialSystem = CreateInterface<IMaterialSystem>( MatSysFactory, "VMaterialSystem080" );
	this->ModelInfo = CreateInterface<CModelInfo>( EngineFactory, "VModelInfoClient004" );
	this->Panel = CreateInterface<IPanel>( VGUI2Factory, "VGUI_Panel009" );
	this->Surface = CreateInterface<ISurface>( VGUIFactory, "VGUI_Surface031" );
	this->Prediction = CreateInterface<IPrediction>( ClientFactory, "VClientPrediction001" );
	this->GameMovement = CreateInterface<IGameMovement>( ClientFactory, "GameMovement001" );

	this->MoveHelper = **reinterpret_cast<IMoveHelper***>(((reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0xFAD93) + 0x1));
	this->GlobalVars = **reinterpret_cast<CGlobalVarsBase***>(((reinterpret_cast<std::uintptr_t>(GetModuleHandleA( "client.dll" )) + 0x46C0) + 0x2));

	return true;
}