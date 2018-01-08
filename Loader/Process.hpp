#pragma once

namespace Process
{
	class CProcess
	{
	public:
		CProcess( const char* szProcessName );
		~CProcess();

	public:
		bool Inject();

	private:
		bool Initialize();
		std::uint32_t GetProcessId();

	private:
		HANDLE m_hProcessHandle;
		std::string m_szProcessName;
	};
}