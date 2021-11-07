#ifndef _SVG_PATTERNBRUSH_H_
#define _SVG_PATTERNBRUSH_H_

#include "SvgObject.h"
#include "IGdiPatternBrush.h"
//#include "SvgGdi.h"

namespace WMFConverter{
		
		//class SvgObject;
		//class IGdiPatternBrush;
		class SvgGdi;


		class SvgPatternBrush : public SvgObject, public IGdiPatternBrush
		{
		public:
			SvgPatternBrush(SvgGdi *gdi, char* bmp);

			char* Pattern();
		private:
			char* _bmp;
		};

}


#endif