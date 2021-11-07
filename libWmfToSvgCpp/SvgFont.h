#ifndef _SVG_FONT_H_
#define _SVG_FONT_H_

#include "gdiInfoDefine.h"
#include "tinyxml2.h"
#include "IGdiFont.h"
#include "SvgObject.h"

//#include "SvgGdi.h"
#include "GdiUtils.h"
#include <vector>
#include <string>
#include <math.h>
#include "tool.h"


namespace WMFConverter{

		class SvgGdi;
		
		class SvgFont : public SvgObject, public IGdiFont
		{
		public:
			SvgFont(
				SvgGdi *gdi,
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
				char* faceName);
			int Height();
			/// Object width.
			int Width();
			/// Object escapement.
			int Escapement();
			/// Object orientation
			int Orientation();
			/// Object weight.
			int Weight();
			/// Italic font.
			bool IsItalic();
			/// Underlined font.
			bool IsUnderlined();
			/// Striked font.
			bool IsStrikedOut();
			/// Object charset.
			int Charset();
			/// Object precision.
			int OutPrecision();
			/// Object ClipPrecision.
			int ClipPrecision();
			/// Font quality.
			int Quality();
			/// Defines pitch and family.
			int PitchAndFamily();
			/// Specifies the font name.
			string FaceName();
			/// Font language.
			string Lang();
			/// Font size.
			int FontSize();
			int* ValidateDx(char* chars, int* dx);
			/// Serves as the default hash function.
			int GetHashCode();
			/// Determines whether the specified object is equal to the current object.
			bool Equals(void* obj);



			/// Create inner text element.
			/// </summary>
			/// <param name="id"></param>
			/// <returns></returns>
			tinyxml2::XMLText* NewText(string id);
			string ToString();


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
			double _heightMultiply ;
			string _lang;

			void initialPrivateData();
		};
}



#endif