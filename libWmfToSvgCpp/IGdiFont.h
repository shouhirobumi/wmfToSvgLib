#ifndef _IGDI_FONT_H_
#define _IGDI_FONT_H_

#include "IGdiObject.h"
#include <string>

using namespace std;

namespace WMFConverter{

		class IGdiFont : public IGdiObject
		{
		public:
			/// Object Height.
			virtual int Height() {
				return 0;
			};

			/// Object Width.
			virtual int Width() {
				return 0;
			};

			/// Object Escapement.
			virtual int Escapement() {
				return 0;
			};

			/// Object Orientation.
			virtual int Orientation() {
				return 0;
			};

			/// Object Weight.
			virtual int Weight() {
				return 0;
			};

			/// Italic font.
			virtual bool IsItalic() {
				return 0;
			};

			/// Underlined font.
			virtual bool IsUnderlined() {
				return 0;
			};

			/// Striked font.
			virtual bool IsStrikedOut() {
				return 0;
			};

			/// Object Charset.
			virtual int Charset() {
				return 0;
			};

			/// Object out precision.
			virtual int OutPrecision() {
				return 0;
			};

			/// Object clip precision.
			virtual int ClipPrecision() {
				return 0;
			};

			/// Object Quality.
			virtual int Quality() {
				return 0;
			};

			virtual int PitchAndFamily() {
				return 0;
			};

			/// Font face name.
			virtual string FaceName() {
				return "";
			};
		};
}



#endif // !_IGDI_FONT_H_
