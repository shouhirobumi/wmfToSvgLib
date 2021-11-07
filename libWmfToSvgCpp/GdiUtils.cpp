#include "GdiUtils.h"

//using namespace WMFConverter::GDI;

namespace WMFConverter{


		int GdiUtils::FBA_SHIFT_JIS[2][2] = { { 0x81, 0x9F }, { 0xE0, 0xFC } };
		int GdiUtils::FBA_HANGUL_CHARSET[2][2] = { { 0x80, 0xFF } };
		int GdiUtils::FBA_JOHAB_CHARSET[2][2] = { { 0x80, 0xFF } };
		int GdiUtils::FBA_GB2312_CHARSET[2][2] = { { 0x80, 0xFF } };
		int GdiUtils::FBA_CHINESEBIG5_CHARSET[2][2] = { { 0xA1, 0xFE } };


		GdiUtils::GdiUtils()
		{
		}
		GdiUtils::~GdiUtils()
		{
		}

		string GdiUtils::ConvertString(char* chars, FontCharsetEnum charset)
		{
			string str(chars);
			return str;
		}

		string GdiUtils::GetCharset(FontCharsetEnum charset)
		{
			switch (charset)
			{
			case ANSI_CHARSET:
				return "Cp1252";
			case SYMBOL_CHARSET:
				return "Cp1252";
			case MAC_CHARSET:
				return "MacRoman";
			case SHIFTJIS_CHARSET:
				return "MS932";
			case HANGUL_CHARSET:
				return "MS949";
			case JOHAB_CHARSET:
				return "Johab";
			case GB2312_CHARSET:
				return "MS936";
			case CHINESEBIG5_CHARSET:
				return "MS950";
			case GREEK_CHARSET:
				return "Cp1253";
			case TURKISH_CHARSET:
				return "Cp1254";
			case VIETNAMESE_CHARSET:
				return "Cp1258";
			case HEBREW_CHARSET:
				return "Cp1255";
			case ARABIC_CHARSET:
				return "Cp1256";
			case BALTIC_CHARSET:
				return "Cp1257";
			case RUSSIAN_CHARSET:
				return "Cp1251";
			case THAI_CHARSET:
				return "MS874";
			case EASTEUROPE_CHARSET:
				return "Cp1250";
			case OEM_CHARSET:
				return "Cp1252";
			default:
				break;
			}
			return "Cp1252";
		}

		string GdiUtils::GetLanguage(FontCharsetEnum charset)
		{
			switch (charset)
			{
			case ANSI_CHARSET:
				return "en";
			case SYMBOL_CHARSET:
				return "en";
			case MAC_CHARSET:
				return "en";
			case SHIFTJIS_CHARSET:
				return "ja";
			case HANGUL_CHARSET:
				return "ko";
			case JOHAB_CHARSET:
				return "ko";
			case GB2312_CHARSET:
				return "zh-CN";
			case CHINESEBIG5_CHARSET:
				return "zh-TW";
			case GREEK_CHARSET:
				return "el";
			case TURKISH_CHARSET:
				return "tr";
			case VIETNAMESE_CHARSET:
				return "vi";
			case HEBREW_CHARSET:
				return "iw";
			case ARABIC_CHARSET:
				return "ar";
			case BALTIC_CHARSET:
				return "bat";
			case RUSSIAN_CHARSET:
				return "ru";
			case THAI_CHARSET:
				return "th";
			case EASTEUROPE_CHARSET:
				return NULL;
			case OEM_CHARSET:
				return NULL;
			default:
				return NULL;
			}
		}

		int* GdiUtils::GetFirstByteArea(FontCharsetEnum charset)
		{
			switch (charset)
			{
			case SHIFTJIS_CHARSET:
				return FBA_SHIFT_JIS[0];
			case HANGUL_CHARSET:
				return FBA_HANGUL_CHARSET[0];
			case JOHAB_CHARSET:
				return FBA_JOHAB_CHARSET[0];
			case GB2312_CHARSET:
				return FBA_GB2312_CHARSET[0];
			case CHINESEBIG5_CHARSET:
				return FBA_CHINESEBIG5_CHARSET[0];
			default:
				return NULL;
			}
		}
}