#ifndef _IGDI_BRUSH_H_
#define _IGDI_BRUSH_H_


#include "IGdiObject.h"



namespace WMFConverter{

		class IGdiBrush : public IGdiObject
		{
		public:
			/// Object Style.
			virtual int Style() {
				return 0;
			};

			/// Object Color.
			virtual int Color() {
				return 0;
			};

			/// Object Hatch.
			virtual int Hatch() {
				return 0;
			};

		};

}











#endif // !_IGDI_BRUSH_H_
