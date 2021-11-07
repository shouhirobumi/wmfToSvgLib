#include "SvgFont.h"


//#include "SvgObject.h"
#include "SvgGdi.h"
//#include "GdiUtils.h"
//#include <vector>
//#include <string>
//#include <math.h>
//#include "tool.h"
#include "SvgDc.h"



using namespace WMFConverter;

namespace WMFConverter{


		SvgFont::SvgFont(
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
				char* faceName)
				: SvgObject(gdi)
			{
				initialPrivateData();
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
				_faceName = GdiUtils::ConvertString(faceName, (FontCharsetEnum)charset);

				// xml:lang
				_lang = GdiUtils::GetLanguage((FontCharsetEnum)charset);

				string emheight = gdi->GetProperty("font-emheight." + _faceName);
				if (emheight == "")
				{
					string alter = gdi->GetProperty("alternative-font." + _faceName);
					if (alter != "")
					{
						emheight = gdi->GetProperty("font-emheight." + alter);
					}
				}

				if (emheight != "")
				{
					_heightMultiply = stringToDouble(emheight);
				}
			}

		int SvgFont::Height(){
				return _height;
			}

			/// Object width.
		int SvgFont::Width(){
				return _width;
			}

			/// Object escapement.
		int SvgFont::Escapement()
			{
				return _escapement;
			}

			/// Object orientation
		int SvgFont::Orientation()
			{
				return _orientation;
			}

			/// Object weight.
		int SvgFont::Weight()
			{
				return _weight;
			}

			/// Italic font.
		bool SvgFont::IsItalic()
			{
				return _italic;
			}

			/// Underlined font.
		bool SvgFont::IsUnderlined()
			{
				return _underline;
			}

			/// Striked font.
		bool SvgFont::IsStrikedOut()
			{
				return _strikeout;
			}

			/// Object charset.
		int SvgFont::Charset()
			{
				return _charset;
			}

			/// Object precision.
		int SvgFont::OutPrecision()
			{
				return _outPrecision;
			}

			/// Object ClipPrecision.
		int SvgFont::ClipPrecision()
			{
				return _clipPrecision;
			}

			/// Font quality.
		int SvgFont::Quality()
			{
				return _quality;
			}

			/// Defines pitch and family.
		int SvgFont::PitchAndFamily()
			{
				return _pitchAndFamily;
			}

			/// Specifies the font name.
		string SvgFont::FaceName()
			{
				return _faceName;
			}

			/// Font language.
		string SvgFont::Lang()
			{
				return _lang;
			}

			/// Font size.
		int SvgFont::FontSize()
			{
				return abs((int)(GDI()->DC()->ToRelativeY(_height * _heightMultiply)));
			}

		int* SvgFont::ValidateDx(char* chars, int* dx)
			{
				if (dx == NULL)
				{
					return NULL;
				}
				int area[2][2] = {};
				int * temp = WMFConverter::GdiUtils::GetFirstByteArea((WMFConverter::FontCharsetEnum)_charset);
				if (temp == NULL)
				{
					return dx;
				}
				memcpy(area, temp, sizeof(area));
				int n = 0;
				bool skip = false;

				for (int i = 0; i < strlen(chars) && i < (sizeof(dx) / sizeof(int)); i++)
				{
					int c = (0xFF & chars[i]);

					if (skip)
					{
						dx[n - 1] += dx[i];
						skip = false;
						continue;
					}

					for (int j = 0; j < 2; j++)
					{
						if (area[j][0] <= c && c <= area[j][1])
						{
							skip = true;
							break;
						}
					}

					dx[n++] = dx[i];
				}

				int* ndx = NULL;
				ndx = (int*)malloc(n * sizeof(int));
				memcpy(ndx, dx, sizeof(ndx));
				return ndx;
			}

			/// Serves as the default hash function.
		int SvgFont::GetHashCode()
			{
				int PRIME = 31;
				int result = 1;
				result = PRIME * result + _charset;
				result = PRIME * result + _clipPrecision;
				result = PRIME * result + _escapement;
				result = PRIME * result + ((_faceName == "") ? 0 : stringGetHashCode(_faceName.c_str()));
				result = PRIME * result + _height;
				result = PRIME * result + (_italic ? 1231 : 1237);
				result = PRIME * result + _orientation;
				result = PRIME * result + _outPrecision;
				result = PRIME * result + _pitchAndFamily;
				result = PRIME * result + _quality;
				result = PRIME * result + (_strikeout ? 1231 : 1237);
				result = PRIME * result + (_underline ? 1231 : 1237);
				result = PRIME * result + _weight;
				result = PRIME * result + _width;
				return result;
			}

			/// Determines whether the specified object is equal to the current object.
		bool SvgFont::Equals(void* obj)
			{
				if (this == obj)
					return true;
				if (obj == NULL)
					return false;
				SvgFont *other = (SvgFont*)obj;
				if (_charset != other->_charset)
					return false;
				if (_clipPrecision != other->ClipPrecision())
					return false;
				if (_escapement != other->Escapement())
					return false;
				if (_faceName == "")
				{
					if (other->FaceName() != "")
						return false;
				}
				else if (_faceName != other->FaceName())
					return false;
				if (_height != other->Height())
					return false;
				if (_italic != other->IsItalic())
					return false;
				if (_orientation != other->Orientation())
					return false;
				if (_outPrecision != other->OutPrecision())
					return false;
				if (_pitchAndFamily != other->PitchAndFamily())
					return false;
				if (_quality != other->Quality())
					return false;
				if (_strikeout != other->IsStrikedOut())
					return false;
				if (_underline != other->IsUnderlined())
					return false;
				if (_weight != other->Weight())
					return false;
				if (_width != other->Width())
					return false;
				return true;
			}



			/// Create inner text element.
			/// </summary>
			/// <param name="id"></param>
			/// <returns></returns>
		tinyxml2::XMLText* SvgFont::NewText(string id)
			{
				string textData = "." + id + "{" + this->ToString() + " }\r\n";
				return GDI()->Document()->NewText(textData.c_str());
			}

		string SvgFont::ToString()
			{
				std::string buffer = "";

				// font-style
				if (_italic)
					buffer = "font-style: italic; ";

				// font-weight
				if (_weight != (int)FontFWEnum::FW_DONTCARE && _weight != (int)FontFWEnum::FW_NORMAL)
				{
					if (_weight < 100)
						_weight = 100;
					else if (_weight > 900)
						_weight = 900;
					else
						_weight = (_weight / 100) * 100;

					if (_weight == (int)FontFWEnum::FW_BOLD)
						buffer += "font-weight: bold; ";
					else
					{
						char text[1000] = {};
						sprintf(text, "font-weight: %d;", _weight);
						buffer += std::string(text);
					}
				}

				int fontSize = FontSize();
				if (fontSize != 0)
				{
					char text[1000] = {};
					sprintf(text, "font-size: %dpx;", fontSize);
					buffer += std::string(text);
				}
				// font-family

				std::vector<std::string> fontList;
				if (_faceName != "")
				{
					string fontFamily = _faceName;
					if (_faceName[0] == '@')
						fontFamily = _faceName.substr(1);
					fontList.push_back(fontFamily);

					string altfont = SvgObject::GDI()->GetProperty("alternative-font." + fontFamily);
					if (altfont != "")
					{
						fontList.push_back(altfont);
					}
				}

				// int pitch = pitchAndFamily & 0x00000003;
				int family = _pitchAndFamily & 0x000000F0;
				switch (family)
				{
				case (int)FontFFEnum::FF_DECORATIVE:
					fontList.push_back("fantasy");
					break;
				case (int)FontFFEnum::FF_MODERN:
					fontList.push_back("monospace");
					break;
				case (int)FontFFEnum::FF_ROMAN:
					fontList.push_back("serif");
					break;
				case (int)FontFFEnum::FF_SCRIPT:
					fontList.push_back("cursive");
					break;
				case (int)FontFFEnum::FF_SWISS:
					fontList.push_back("sans-serif");
					break;
				}
				if (fontList.size() > 0)
				{
					buffer += "font-family:";
					for (int i = 0; i < fontList.size(); i++)
					{
						string font = fontList.at(i);
						if (font.find(" ") != -1)
							buffer += " \"" + font + "\"";
						else
							buffer += " " + font;

						if (i < fontList.size())
							buffer += ",";
					}
					buffer += "; ";
				}

				// text-decoration
				if (_underline || _strikeout)
				{
					buffer += "text-decoration:";
					if (_underline)
						buffer += " underline";
					if (_strikeout)
						buffer += " overline";
					buffer += "; ";
				}

				return buffer;
			}


		void SvgFont::initialPrivateData(){
				_height = 0;
				_width = 0;
				_escapement = 0;
				_orientation = 0;
				_weight = 0;
				_italic = false;
				_underline = false;
				_strikeout = false;
				_charset = 0;
				_outPrecision = 0;
				_clipPrecision = 0;
				_quality = 0;
				_pitchAndFamily = 0;
				_faceName = "";
				_heightMultiply = 1.0;
				_lang = "";
			}


}

