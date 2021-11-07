#include "SvgPatternBrush.h"


//#include "SvgObject.h"
//#include "IGdiPatternBrush.h"
#include "SvgGdi.h"

namespace WMFConverter{

		SvgPatternBrush::SvgPatternBrush(SvgGdi *gdi, char* bmp)
			: SvgObject(gdi)
		{
			_bmp = bmp;
		}

		char* SvgPatternBrush::Pattern()
		{
			return _bmp;
		}

}