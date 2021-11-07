#include "SvgPalette.h"


//#include "SvgObject.h"
//#include "IGdiPalette.h"
#include "SvgGdi.h"


namespace WMFConverter{
			/// Default constructor.

		SvgPalette::SvgPalette(
				SvgGdi* gdi,
				int version,
				int* entries)
				:SvgObject(gdi)
			{
				_version = version;
				_entries = entries;
			}


			/// Object version.
		int SvgPalette::Version()
			{
				return _version;
			}

			/// Object entries.
		int* SvgPalette::Entries()
			{
				return _entries;
			}


}