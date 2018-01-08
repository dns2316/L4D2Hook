#pragma once

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

typedef unsigned long HFont;

class ISurface
{
private:
	struct Color {
		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};
public:
	inline void DrawSetColor( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a )
	{
		const Color color{ r, g, b, a };
		return GetFunction<void( __thiscall* )(ISurface*, Color)>( this, 10 )(this, color);
	}

	inline void DrawOutlinedRect( std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1 )
	{
		return GetFunction<void( __thiscall* )(ISurface*, std::int32_t, std::int32_t, std::int32_t, std::int32_t)>( this, 14 )(this, x0, y0, x1, y1);
	}

	inline void DrawLine( std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1 )
	{
		return GetFunction<void( __thiscall* )(ISurface*, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t)>( this, 15 )(this, x0, y0, x1, y1);
	}

	inline void DrawSetTextFont( HFont font )
	{
		return GetFunction<void( __thiscall* )(ISurface*, HFont)>( this, 17 )(this, font);
	}

	inline void DrawSetTextColor( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a )
	{
		return GetFunction<void( __thiscall* )(ISurface*, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t)>( this, 19 )(this, r, g, b, a);
	}

	inline void DrawSetTextPos( std::uint32_t x, std::uint32_t y )
	{
		return GetFunction<void( __thiscall* )(ISurface*, std::uint32_t, std::uint32_t)>( this, 20 )(this, x, y);
	}

	inline void DrawPrintText( const wchar_t* text, std::int32_t textLen, FontDrawType_t DrawType = FONT_DRAW_DEFAULT )
	{
		return GetFunction<void( __thiscall* )(ISurface*, const wchar_t*, std::int32_t, FontDrawType_t)>( this, 22 )(this, text, textLen, DrawType);
	}

	inline HFont Create_Font()
	{
		return GetFunction<HFont( __thiscall* )(ISurface*)>( this, 63 )(this);
	}

	inline bool SetFontGlyphSet( HFont font, const char* windowsFontName, std::int32_t tall, std::int32_t weight, std::int32_t blur, std::int32_t scanlines, std::int32_t flags, std::int32_t nRangeMin = 0, std::int32_t nRangeMax = 0 )
	{
		return GetFunction<bool( __thiscall* )(ISurface*, HFont, const char*, std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t)>( this, 64 )(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}
};