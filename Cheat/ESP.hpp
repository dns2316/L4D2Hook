#pragma once

#define ESP_WORLD_MAX_RANGE 2000.0f

namespace ESP
{
	class CESP
	{
	public:
		CESP();
		~CESP();
		
	public:
		void Execute();

	private:
		CBaseEntity* pLocal;
		HFont m_ESPFont;

	private:
		bool Initialize();
		void DrawWatermark();;
		void DrawDrop( CBaseEntity* pEntity );

	private:
		void DrawPlayer( CBaseEntity* pEntity );
		void DrawBox( const RECT& rect );
		void DrawSkeleton( CBaseEntity* pEntity );
	};
}