#ifndef _WMF_PATTERNBRUSH_H_
#define _WMF_PATTERNBRUSH_H_

#include "WmfObject.h"
#include "IGdiPatternBrush.h"


namespace WMFConverter{
	namespace Wmf{
		class WmfPatternBrush : public WmfObject, public IGdiPatternBrush
		{
		public:

			WmfPatternBrush(int id, char* image)
				: WmfObject(id)
			{
				_image = image;
			}

			char* Pattern()
			{
				return _image;
			}
		private:
			 char* _image;

		};
	
	}
}


#endif