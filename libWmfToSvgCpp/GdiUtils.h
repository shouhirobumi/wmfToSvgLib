#ifndef _GDIUTILS_H_
#define _GDIUTILS_H_

#include "stdio.h"
#include <string>
#include "gdiInfoDefine.h"


using namespace std;

namespace WMFConverter{

		class GdiUtils{

		public:
			GdiUtils();
			~GdiUtils();

			static string ConvertString(char* chars, FontCharsetEnum charset);
			static string GetCharset(FontCharsetEnum charset);
			static string GetLanguage(FontCharsetEnum charset);
			
			static int* GetFirstByteArea(FontCharsetEnum charset);


		private:

			static int FBA_SHIFT_JIS[2][2];
			static int FBA_HANGUL_CHARSET[2][2];
			static int FBA_JOHAB_CHARSET[2][2]; 
			static int FBA_GB2312_CHARSET[2][2];
			static int FBA_CHINESEBIG5_CHARSET[2][2];


		};
}


#endif
