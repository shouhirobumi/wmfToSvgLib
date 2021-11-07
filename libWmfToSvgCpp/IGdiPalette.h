#ifndef _IGDI_PALETTE_H_
#define _IGDI_PALETTE_H_
#include "IGdiObject.h"

namespace WMFConverter{

		/// Graphics Device Interface - Represents a Palette object.
		class IGdiPalette : public IGdiObject
		{
		public:
			/// Object Version.
			int Version(){
				return _version;
			};

			/// Object Entries.
			int Entries() {
				return _entries;
			};


		private:
			int _version;
			int _entries;
		};

}	

#endif