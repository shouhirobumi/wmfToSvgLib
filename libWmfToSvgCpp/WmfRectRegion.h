#ifndef _WMF_RECT_REGION_H_
#define _WMF_RECT_REGION_H_

#include "WmfObject.h"
#include "IGdiRegion.h"

namespace WMFConverter{
	namespace Wmf{
		class WmfRectRegion : public WmfObject, public IGdiRegion
		{
		public:
			WmfRectRegion(int id, int left, int top, int right, int bottom)
				:WmfObject(id)
			{
				_left = left;
				_top = top;
				_right = right;
				_bottom = bottom;
			}
			/// Left value.
			int Left()
			{
				return _left;
			}

			/// Top value.
			int Top()
			{
				return _top;
			}

			/// Right value.
			int Right()
			{
				return _right;
			}

			/// Bottom value.
			int Bottom()
			{
				return _bottom;
			}

		private:
			int _left;
			int _top;
			int _right;
			int _bottom;
		};
	
	}
}



#endif