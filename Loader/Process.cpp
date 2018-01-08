#include "stdafx.h"

using namespace Process;

CProcess::CProcess( const char* szProcessName ) :
	m_hProcessHandle( nullptr ),
	m_szProcessName( szProcessName )
{
	if (!this->Initialize())
		printf( "Failed process initialization.\n" );
}

CProcess::~CProcess(){}

bool CProcess::Initialize()
{
	auto nProcessId = GetProcessId();
	if (!nProcessId)
	{
		printf( "Failed getting %s process ID.\n", m_szProcessName.c_str() );
		return false;
	}

	m_hProcessHandle = OpenProcess( PROCESS_ALL_ACCESS, false, nProcessId );
	return (m_hProcessHandle != INVALID_HANDLE_VALUE);
}

std::uint32_t CProcess::GetProcessId()
{
	auto hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	
	PROCESSENTRY32 ProcessEntry{};
	ProcessEntry.dwSize = sizeof( PROCESSENTRY32 );

	if (Process32First( hSnap, &ProcessEntry ))
	{
		do {
			if (!strcmp( m_szProcessName.c_str(), ProcessEntry.szExeFile ))
			{
				CloseHandle( hSnap );
				return ProcessEntry.th32ProcessID;
			}
		} while (Process32Next( hSnap, &ProcessEntry ));
	}

	return 0;
}

bool CProcess::Inject()
{
	char szDllPath[MAX_PATH];
	GetCurrentDirectoryA( MAX_PATH, szDllPath );
	strcat_s( szDllPath, "\\L4D2Hook.dll" );

	auto pLoadLibrary = GetProcAddress( GetModuleHandleA( "kernel32.dll" ), "LoadLibraryA" );
	if (!pLoadLibrary)
		return false;

	auto pAllocAddress = reinterpret_cast<std::uintptr_t>(VirtualAllocEx( m_hProcessHandle, 0, strlen( szDllPath ) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE ));
	if (!pAllocAddress)
		return false;

	if (!WriteProcessMemory( m_hProcessHandle, reinterpret_cast<PVOID>(pAllocAddress), szDllPath, strlen( szDllPath ) + 1, 0 ))
		return false;

	auto hThread = CreateRemoteThread( m_hProcessHandle, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pLoadLibrary), reinterpret_cast<LPVOID>(pAllocAddress), 0, 0 );
	if (hThread == INVALID_HANDLE_VALUE)
		return false;

	WaitForSingleObject( hThread, INFINITE );
	VirtualFreeEx( m_hProcessHandle, reinterpret_cast<LPVOID>(pAllocAddress), 0, MEM_RELEASE );

	return true;
}