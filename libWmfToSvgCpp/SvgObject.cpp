#include "SvgObject.h"
#include "SvgGdi.h"
#include "SvgDc.h"

namespace WMFConverter{

			/// Default constructor.
		SvgObject::SvgObject(SvgGdi* gdi){
			_Objgdi = gdi;
			}
			/// Gdi object instance
		SvgGdi* SvgObject::GDI(){
			return _Objgdi;
			}

			/// Convert to real size.
		int SvgObject::ToRealSize(int px)
			{
				return (this->_Objgdi->DC()->Dpi() * px / 90);
			}

			/// Convert int color to rgb color.
		std::string SvgObject::ToColor(int color)
			{
				int b = (0x00FF0000 & color) >> 16;
				int g = (0x0000FF00 & color) >> 8;
				int r = (0x000000FF & color);

				char str[100] = {};
				sprintf(str, "rgb(%d,%d,%d)", r, g, b);

				return std::string(str);
			}

}