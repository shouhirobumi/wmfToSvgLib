#ifndef _IGDI_PEN_H_
#define _IGDI_PEN_H_

#include "IGdiObject.h"

namespace WMFConverter{

		/// Graphics Device Interface - Represents a Pen object.
		class IGdiPen : public IGdiObject
		{
		public:
			/// Object Style.
			virtual int Style() {
				return 0;
			};

				/// Object Width.
			virtual int Width() {
				return 0;
			};

				/// Object Color.
			virtual int Color() {
				return 0;
			};

		};

}

#endif //_IGDI_PEN_H_