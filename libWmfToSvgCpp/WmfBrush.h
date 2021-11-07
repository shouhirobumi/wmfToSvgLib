#ifndef _WMF_BRUSH_H_
#define _WMF_BRUSH_H_

#include "IGdiBrush.h"
#include "WmfObject.h"

namespace WMFConverter{
	namespace Wmf{
		class WmfBrush : public WmfObject, public IGdiBrush
		{

		public:
			/// Object Style.
			int Style()
			{
				return _style;
			}

			/// Object Color.
			int Color()
			{
				return _color;
			}

			/// Object Hatch.
			int Hatch()
			{
				return _hatch;
			}

			/// Default Constructor
			WmfBrush(int id, int style, int color, int hatch)
				:WmfObject(id)
			{
				_style = style;
				_color = color;
				_hatch = hatch;
			}


		private:
			int _style;
			int _color;
			int _hatch;
		};

	}
}


#endif