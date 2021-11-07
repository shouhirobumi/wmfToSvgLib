#ifndef _SVG_PALETTE_H_
#define _SVG_PALETTE_H_

#include "SvgObject.h"
#include "IGdiPalette.h"
//#include "SvgGdi.h"


namespace WMFConverter{

		class SvgGdi;
		//class IGdiPalette;

		class SvgPalette : public SvgObject, public IGdiPalette
		{
		public:
			/// Default constructor.

			SvgPalette(
				SvgGdi* gdi,
				int version,
				int* entries);


			/// Object version.
			int Version();

			/// Object entries.
			int* Entries();

		private:
			int _version;
			int* _entries;
		};
}



#endif