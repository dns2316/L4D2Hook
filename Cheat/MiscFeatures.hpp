#pragma once

namespace MiscFeatures
{
	class CMiscFeatures
	{
	public:
		CMiscFeatures();
		~CMiscFeatures();

	public:
		void Execute( CUserCmd* cmd );

	private:
		void Bunnyhop( CUserCmd* cmd );
	};
}