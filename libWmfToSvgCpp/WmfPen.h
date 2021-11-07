#ifndef _WMF_PEN_H_
#define _WMF_PEN_H_

#include "WmfObject.h"
#include "IGdiPen.h"

namespace WMFConverter{
	namespace Wmf{
		class WmfPen : public WmfObject, public IGdiPen
		{
		public:

			WmfPen(int id, int style, int width, int color)
				: WmfObject(id)
			{
			}

			int Style()
			{
				return _style;
			}
			int Width()
			{

				return _width;
			}
			int Color()
			{
				return _color;
			}
		private:
			int _style;
			int _width;
			int _color;
		};

	}
}

#endif