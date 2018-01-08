#pragma once

namespace Aimbot
{
	class CAimbot
	{
	public:
		CAimbot();
		~CAimbot();

	public:
		void Execute( CUserCmd* cmd );

	private:
		CBaseEntity* pLocal;

	private:
		std::uint32_t GetBestTarget();
		void CompensateSpread( CUserCmd* cmd );
		void CompensateRecoil( CUserCmd* cmd );
	};
}