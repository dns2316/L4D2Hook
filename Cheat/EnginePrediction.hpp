#pragma once

namespace EnginePrediction
{
	class CEnginePrediction
	{
	public:
		CEnginePrediction( CUserCmd* cmd, CBaseEntity* LocalPlayer );
		~CEnginePrediction();
		
	private:
		CUserCmd* pCmd;
		CBaseEntity* pLocal;
	};
}