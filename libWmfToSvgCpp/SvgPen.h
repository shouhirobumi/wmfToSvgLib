#ifndef _SVG_PEN_H_
#define _SVG_PEN_H_

#include "SvgObject.h"
//#include "IGdiPen.h"
//#include "SvgGdi.h"

#include "tinyxml2.h"

#include "IGdiPen.h"
#include "gdiInfoDefine.h"

namespace WMFConverter{

		//class SvgObject;
		//class IGdiPen;
		class SvgGdi;

		class SvgPen : public SvgObject, public IGdiPen
		{
		public:
			/// Construdor padrão.
			SvgPen(
				SvgGdi *gdi,
				int style,
				int width,
				int color); 
			
			/// Object style.
		int Style();
			/// Object width.
		int Width();

			/// Object color.
		int Color();

			/// Serves as the default hash function.

		int GetHashCode();
			/// Determines whether the specified object is equal to the current object.
		bool Equals(void* obj);
			/// Create inner text element.
		tinyxml2::XMLText* NewText(string id);

			/// Returns a string that represents the current object.
		string ToString();

		private:
			int _style;
			int _width;
			int _color;
		};

}


#endif