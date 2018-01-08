#include "stdafx.h"

using namespace Menu;

CMenu::CMenu() :
	m_MenuFont( 0 )
{
	if (!this->Initialize())
		printf( "Menu failed initialization.\n" );
}

CMenu::~CMenu() {}

void CMenu::Execute()
{
	if (GetAsyncKeyState( VK_INSERT ) & 1)
		m_bIsMenuOpen = !m_bIsMenuOpen;

	if (!m_bIsMenuOpen)
		return;

	HandleInput();
	DrawMenu();
}

bool CMenu::Initialize()
{
	m_MenuFont = g_Interfaces->Surface->Create_Font();
	if (!m_MenuFont)
		return false;

	if (!g_Interfaces->Surface->SetFontGlyphSet( m_MenuFont, "Helvetica-Bold", 20, 700, 0, 0, FONTFLAG_OUTLINE ))
		return false;

	return true;
}

void CMenu::DrawMenu()
{
	std::vector<std::string> vecMenuItems;

	char buff[128];
	sprintf_s( buff, sizeof( buff ), "Aimbot = %s", (g_Config.m_nAimMode == Config::AIMBOT_MODE::AIMBOT_OFF)
		? "OFF" : (g_Config.m_nAimMode == Config::AIMBOT_MODE::AIMBOT_NONSILENT)
		? "NORMAL" : "SILENT" );

	vecMenuItems.push_back( buff );
	sprintf_s( buff, sizeof( buff ), "Aimkey = %s", m_Aimkeys.at( m_nAimkeyIndex ).keyname );
	vecMenuItems.push_back( buff );

	sprintf_s( buff, sizeof( buff ), "ESP = %s", g_Config.m_bESP ? "ON" : "OFF" );
	vecMenuItems.push_back( buff );

	sprintf_s( buff, sizeof( buff ), "Chams = %s", g_Config.m_bChams ? "ON" : "OFF" );
	vecMenuItems.push_back( buff );
	
	static const std::int32_t nTextPosX = 200;
	std::int32_t nTextPosY = 200;

	for (std::int32_t i = 0; i < vecMenuItems.size(); i++)
	{
		wchar_t wbuf[128];
		if (MultiByteToWideChar( CP_UTF8, 0, vecMenuItems[i].c_str(), -1, wbuf, 128 ) > 0)
		{
			(m_nMenuIndex == i)
				? g_Interfaces->Surface->DrawSetTextColor( 255, 0, 0, 255 )
				: g_Interfaces->Surface->DrawSetTextColor( 255, 255, 0, 255 );

			g_Interfaces->Surface->DrawSetTextPos( nTextPosX, nTextPosY );
			g_Interfaces->Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
		}

		nTextPosY += 14;
	}
}

void CMenu::UpdateMenuItem( const MenuDir & dir )
{
	switch (m_nMenuIndex)
	{
	case 0:
		(dir == MenuDir::LEFT) ? g_Config.m_nAimMode-- : g_Config.m_nAimMode++;

		if (g_Config.m_nAimMode < 0)
			g_Config.m_nAimMode = 2;

		else if (g_Config.m_nAimMode > 2)
			g_Config.m_nAimMode = 0;

		break;

	case 1:
		(dir == MenuDir::LEFT) ? m_nAimkeyIndex-- : m_nAimkeyIndex++;
		if (m_nAimkeyIndex < 0)
			m_nAimkeyIndex = 3;

		else if (m_nAimkeyIndex > 3)
			m_nAimkeyIndex = 0;

		g_Config.m_nAimkey = m_Aimkeys.at( m_nAimkeyIndex ).virtualkey;
		break;

	case 2:
		g_Config.m_bESP = !g_Config.m_bESP;
		break;

	case 3:
		g_Config.m_bChams = !g_Config.m_bChams;
		break;

	default:
		break;
	}
}

void CMenu::HandleInput()
{
	if (GetAsyncKeyState( VK_DOWN ) & 1)
	{
		m_nMenuIndex++;
		if (m_nMenuIndex > 3)
			m_nMenuIndex = 0;
	}

	else if (GetAsyncKeyState( VK_UP ) & 1)
	{
		m_nMenuIndex--;
		if (m_nMenuIndex < 0)
			m_nMenuIndex = 3;
	}

	else if (GetAsyncKeyState( VK_RIGHT ) & 1)
	{
		UpdateMenuItem( MenuDir::RIGHT );
	}

	else if (GetAsyncKeyState( VK_LEFT ) & 1)
	{
		UpdateMenuItem( MenuDir::LEFT );
	}
}
