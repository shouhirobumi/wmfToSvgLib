#ifndef _WMF_PALETTE_H_
#define _WMF_PALETTE_H_

#include "WmfObject.h"
#include "IGdiPalette.h"

namespace WMFConverter{
	namespace Wmf{
		class WmfPalette : public WmfObject, public IGdiPalette
		{
		public:
			WmfPalette(int id, int version, int* entries)
				: WmfObject(id)
			{
				_version = version;
				_entries = entries;
			}

			int Version()
			{
				return _version;
			}

			int* Entries()
			{
				return _entries;
			}


		private:
			int _version;
			int* _entries;
		};

	}
}

#endif