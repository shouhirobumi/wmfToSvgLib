#ifndef _SVG_OBJECT_H_
#define _SVG_OBJECT_H_

#include "SvgObject.h"
#include <string>
//#include "SvgGdi.h"

using namespace std;

namespace WMFConverter{
	
		class SvgGdi;

		class SvgObject
		{
		public:
			/// Default constructor.
			SvgObject(SvgGdi* gdi);
			/// Gdi object instance
			SvgGdi* GDI();
			/// Convert to real size.
			int ToRealSize(int px);
			/// Convert int color to rgb color.
			static string ToColor(int color);

		private:
			SvgGdi* _Objgdi;
		};


}


#endif