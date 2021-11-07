#ifndef _WMF_REGION_H_
#define _WMF_REGION_H_

#include "WmfObject.h"
#include "IGdiRegion.h"

namespace WMFConverter{
	namespace Wmf{
		class WmfRegion : public WmfObject, public IGdiRegion
		{
		public:
			WmfRegion(int id)
				:WmfObject(id)
			{
			}

		};

	}
}



#endif