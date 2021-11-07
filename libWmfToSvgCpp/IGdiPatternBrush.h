#ifndef _IGDI_PAETTERNBRUSH_H_
#define _IGDI_PAETTERNBRUSH_H_

#include "IGdiObject.h"

namespace WMFConverter{

		/// Graphics Device Interface - Represents a Pattern Brush object.
		class IGdiPatternBrush : public IGdiObject
		{
		public:
			/// Object Patterns.
			virtual char* Pattern() {
				return NULL;
			};
		};
}
#endif // !_IGDI_PAETTERNBRUSH_H_
