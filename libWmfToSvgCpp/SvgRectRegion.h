#ifndef _SVG_RECT_REGION_H_
#define _SVG_RECT_REGION_H_

#include "tinyxml2.h"
#include "SvgRegion.h"
#include "tool.h"
//#include "SvgGdi.h"



namespace WMFConverter{


		//class SvgRegion;
		class SvgGdi;

		class SvgRectRegion : public SvgRegion
		{
		public:
			SvgRectRegion(SvgGdi *gdi, int left, int top, int right, int bottom);
			/// Left value.
			int Left();

			/// Top value.
			int Top();

			/// Right value.
			int Right();

			/// Bottom value.
			int Bottom();

			/// Create rect element.
			tinyxml2::XMLElement* CreateElement();
			/// Serves as the default hash function.
			int GetHashCode();

			/// Determines whether the specified object is equal to the current object.
			bool Equals(void *obj);

		private:
			int _left;
			int _top;
			int _right;
			int _bottom;
		};

}




#endif