#ifndef _SVG_BRUSH_H_
#define _SVG_BRUSH_H_

#include <string>

#include "tinyxml2.h"
#include "gdiInfoDefine.h"
#include "SvgObject.h"
#include "IGdiBrush.h"
#include "tool.h"

using namespace std;

namespace WMFConverter{


		class SvgGdi;

		class SvgBrush : public SvgObject, public IGdiBrush{

		public:

			SvgBrush(
				SvgGdi *gdi,
				int style,
				int color,
				int hatch);

			int Style();
			int Color();
			int Hatch();

			tinyxml2::XMLElement* CreateFillPattern(string id);
			/// Serves as the default hash function.
			int GetHashCode();
			/// Determines whether the specified object is equal to the current object.
			bool Equals(void* obj);
			/// Create element inner text.
			tinyxml2::XMLText* NewText(string id);
			/// Returns a string that represents the current object.
			string ToString();
		private:
			int _style;
			int _color;
			int _hatch;

			void initialPrivateData();



		};
}


#endif