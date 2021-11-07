#ifndef _WMF_FONT_H_
#define _WMF_FONT_H_

#include <string>
#include "WmfObject.h"
#include "IGdiFont.h"
#include "GdiUtils.h"


using namespace std;

namespace WMFConverter{
	namespace Wmf{
		class WmfFont : public WmfObject, public IGdiFont
		{
		public:
       
			/// Object Height.
			int Height()
			{
				return _height;
			}

			int Width()
			{
				return _width;
			}

        /// Object Escapement.
			int Escapement()
			{
				return _escapement;
			}

        /// Object Orientation.
			int Orientation()
			{
				return _orientation;
			}

        /// Object Weight.
			int Weight()
			{
				return _weight;
			}

        /// Defines whether the font is italic.
			bool IsItalic()
			{
				return _italic;
			}

        /// Defines whether the font is underlined.
			bool IsUnderlined()
			{
				return _underline;
			}

        /// Defines whether the font is striked.
			bool IsStrikedOut()
			{
				return _strikeout;
			}

        /// Defines the font charset.
			int Charset()
			{
				return _charset;
			}

        /// Defines the font out precision.
			int OutPrecision()
			{
				return _outPrecision;
			}

        /// Defines the clip precision.
			int ClipPrecision()
			{
				return _clipPrecision;
			}

        /// Object quality.
			int Quality()
			{
				return _quality;
			}

        /// Defines pitch and famility font.
			int PitchAndFamily()
			{
				return _pitchAndFamily;
			}

        /// Defines face name rules.
			string FaceName()
			{
				return _faceName;
			}
			WmfFont(int id,
				int height,
				int width,
				int escapement,
				int orientation,
				int weight,
				bool italic,
				bool underline,
				bool strikeout,
				int charset,
				int outPrecision,
				int clipPrecision,
				int quality,
				int pitchAndFamily,
				char* faceName)
				: WmfObject(id)
			{

				_height = height;
				_width = width;
				_escapement = escapement;
				_orientation = orientation;
				_weight = weight;
				_italic = italic;
				_underline = underline;
				_strikeout = strikeout;
				_charset = charset;
				_outPrecision = outPrecision;
				_clipPrecision = clipPrecision;
				_quality = quality;
				_pitchAndFamily = pitchAndFamily;
				_faceName = WMFConverter::GdiUtils::ConvertString(faceName, (FontCharsetEnum)charset);
			}

		private:
			int _height;
			int _width;
			int _escapement;
			int _orientation;
			int _weight;
			bool _italic;
			bool _underline;
			bool _strikeout;
			int _charset;
			int _outPrecision;
			int _clipPrecision;
			int _quality;
			int _pitchAndFamily;

			string _faceName;
		};
	}
}


#endif