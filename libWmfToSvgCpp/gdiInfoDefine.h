#ifndef _GDI_INFO_DEFINE_H_
#define _GDI_INFO_DEFINE_H_

namespace WMFConverter{

		enum BrushDIBColorsEnum
		{
			DIB_PAL_COLORS = 1,
			DIB_RGB_COLORS = 0,
		};

		enum BrushBSEnum
		{
			BS_DIBPATTERN = 5,
			BS_DIBPATTERN8X8 = 8,
			BS_DIBPATTERNPT = 6,
			BS_HATCHED = 2,
			BS_HOLLOW = 1,
			BS_NULL = 1,
			BS_PATTERN = 3,
			BS_PATTERN8X8 = 7,
			BS_SOLID = 0,
		};

		enum BrushHSEnum
		{
			HS_HORIZONTAL = 0,
			HS_VERTICAL = 1,
			HS_FDIAGONAL = 2,
			HS_BDIAGONAL = 3,
			HS_CROSS = 4,
			HS_DIAGCROSS = 5,
		};

		enum FontCharsetEnum
		{
			ANSI_CHARSET = 0,
			DEFAULT_CHARSET = 1,
			SYMBOL_CHARSET = 2,
			MAC_CHARSET = 77,
			SHIFTJIS_CHARSET = 128,
			HANGUL_CHARSET = 129,
			JOHAB_CHARSET = 130,
			GB2312_CHARSET = 134,
			CHINESEBIG5_CHARSET = 136,
			GREEK_CHARSET = 161,
			TURKISH_CHARSET = 162,
			VIETNAMESE_CHARSET = 163,
			ARABIC_CHARSET = 178,
			HEBREW_CHARSET = 177,
			BALTIC_CHARSET = 186,
			RUSSIAN_CHARSET = 204,
			THAI_CHARSET = 222,
			EASTEUROPE_CHARSET = 238,
			OEM_CHARSET = 255,
		};

		enum FontClipPrecisEnum
		{
			CLIP_DEFAULT_PRECIS = 0,
			CLIP_CHARACTER_PRECIS = 1,
			CLIP_STROKE_PRECIS = 2,
			CLIP_MASK = 15,
			CLIP_LH_ANGLES = 16,
			CLIP_TT_ALWAYS = 32,
			CLIP_EMBEDDED = 128,
		};

		enum FontFFEnum
		{
			FF_DONTCARE = 0,
			FF_ROMAN = 16,
			FF_SWISS = 32,
			FF_MODERN = 48,
			FF_SCRIPT = 64,
			FF_DECORATIVE = 80,
		};

		enum FontFWEnum
		{
			FW_DONTCARE = 0,
			FW_THIN = 100,
			FW_EXTRALIGHT = 200,
			FW_ULTRALIGHT = 200,
			FW_LIGHT = 300,
			FW_NORMAL = 400,
			FW_REGULAR = 400,
			FW_MEDIUM = 500,
			FW_SEMIBOLD = 600,
			FW_DEMIBOLD = 600,
			FW_BOLD = 700,
			FW_EXTRABOLD = 800,
			FW_ULTRABOLD = 800,
			FW_HEAVY = 900,
			FW_BLACK = 900,
		};

		enum FontOutPrecisEnum
		{
			OUT_DEFAULT_PRECIS = 0,
			OUT_STRING_PRECIS = 1,
			OUT_CHARACTER_PRECIS = 2,
			OUT_STROKE_PRECIS = 3,
			OUT_TT_PRECIS = 4,
			OUT_DEVICE_PRECIS = 5,
			OUT_RASTER_PRECIS = 6,
			OUT_TT_ONLY_PRECIS = 7,
			OUT_OUTLINE_PRECIS = 8,
			OUT_SCREEN_OUTLINE_PRECIS = 9,
		};

		enum FontPitchEnum
		{
			DEFAULT_PITCH = 0,
			FIXED_PITCH = 1,
			VARIABLE_PITCH = 2,
		};

		enum FontQualityEnum
		{
			DEFAULT_QUALITY = 0,
			DRAFT_QUALITY = 1,
			PROOF_QUALITY = 2,
			NONANTIALIASED_QUALITY = 3,
			ANTIALIASED_QUALITY = 4,
			CLEARTYPE_QUALITY = 5, // Windows XP only
		};
		
		enum GdiEnum
		{
			OPAQUE = 2,
			TRANSPARENT = 1,

			TA_BASELINE = 24,
			TA_BOTTOM = 8,
			TA_TOP = 0,
			TA_CENTER = 6,
			TA_LEFT = 0,
			TA_RIGHT = 2,
			TA_NOUPDATECP = 0,
			TA_RTLREADING = 256,
			TA_UPDATECP = 1,
			VTA_BASELINE = 24,
			VTA_CENTER = 6,

			ETO_CLIPPED = 4,
			ETO_NUMERICSLOCAL = 1024,
			ETO_NUMERICSLATIN = 2048,
			ETO_GLYPH_INDEX = 16,
			ETO_OPAQUE = 2,
			ETO_PDY = 8192,
			ETO_RTLREADING = 128,
			ETO_IGNORELANGUAGE = 4096,

			MM_ANISOTROPIC = 8,
			MM_HIENGLISH = 5,
			MM_HIMETRIC = 3,
			MM_ISOTROPIC = 7,
			MM_LOENGLISH = 4,
			MM_LOMETRIC = 2,
			MM_TEXT = 1,
			MM_TWIPS = 6,

			STRETCH_ANDSCANS = 2,
			STRETCH_DELETESCANS = 3,
			STRETCH_HALFTONE = 4,
			STRETCH_ORSCANS = 2,
			BLACKONWHITE = 2,
			COLORONCOLOR = 3,
			HALFTONE = 4,
			WHITEONBLACK = 2,

			ALTERNATE = 1,
			WINDING = 2,

			R2_BLACK = 1,
			R2_COPYPEN = 13,
			R2_MASKNOTPEN = 3,
			R2_MASKPEN = 9,
			R2_MASKPENNOT = 5,
			R2_MERGENOTPEN = 12,
			R2_MERGEPEN = 15,
			R2_MERGEPENNOT = 14,
			R2_NOP = 11,
			R2_NOT = 6,
			R2_NOTCOPYPEN = 4,
			R2_NOTMASKPEN = 8,
			R2_NOTMERGEPEN = 2,
			R2_NOTXORPEN = 10,
			R2_WHITE = 16,
			R2_XORPEN = 7,

			BLACKNESS = 66,
			DSTINVERT = 5570569,
			MERGECOPY = 12583114,
			MERGEPAINT = 12255782,
			NOTSRCCOPY = 3342344,
			NOTSRCERASE = 1114278,
			PATCOPY = 15728673,
			PATINVERT = 5898313,
			PATPAINT = 16452105,
			SRCAND = 8913094,
			SRCCOPY = 13369376,
			SRCERASE = 4457256,
			SRCINVERT = 6684742,
			SRCPAINT = 15597702,
			WHITENESS = 16711778,

//			DIB_RGB_COLORS = 0,
//			DIB_PAL_COLORS = 1,

			LAYOUT_BITMAPORIENTATIONPRESERVED = 8,
			LAYOUT_RTL = 1,

			ABSOLUTE = 1,
			RELATIVE = 2,

			ASPECT_FILTERING = 1,
		};

		enum PenPSEnum
		{
			PS_SOLID = 0,
			PS_DASH = 1,
			PS_DOT = 2,
			PS_DASHDOT = 3,
			PS_DASHDOTDOT = 4,
			PS_NULL = 5,
			PS_INSIDEFRAME = 6,
		};

		enum RegionEnum
		{
			NULLREGION = 1,
			SIMPLEREGION = 2,
			COMPLEXREGION = 3,
			ERROR = 0,
		};
}





#endif // _GDI_INFO_DEFINE_
