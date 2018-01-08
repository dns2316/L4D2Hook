#pragma once
#include <unordered_map>

namespace Menu
{
	class CMenu
	{
	public:
		CMenu();
		~CMenu();

	public:
		void Execute();

	private:
		bool m_bIsMenuOpen = false;
		HFont m_MenuFont;
		std::int32_t m_nMenuIndex = 0;
		std::int32_t m_nAimkeyIndex = 0;

		enum MenuDir
		{
			LEFT = 0, RIGHT
		};

	private:
		bool Initialize();
		void DrawMenu();
		void UpdateMenuItem( const MenuDir& dir );
		void HandleInput();

	private:
		struct virtualkey_t
		{
			virtualkey_t( std::int32_t virtualkey, const char* keyname )
			{
				this->virtualkey = virtualkey;
				this->keyname = keyname;
			}

			std::int32_t virtualkey;
			const char* keyname;
		};

		const std::unordered_map<std::int32_t, virtualkey_t> m_Aimkeys = {
		{0, {1, "Mouse 1"}},
		{1, {4, "Mouse 3"}},
		{2, {5, "Mouse 4"}},
		{3, {6, "Mouse 5"}}
		};
	};
}