#include "SvgPen.h"
//#include "SvgObject.h"
//#include "IGdiPen.h"
#include "SvgGdi.h"

namespace WMFConverter{

			/// Construdor padrão.
		SvgPen::SvgPen(
				SvgGdi *gdi,
				int style,
				int width,
				int color)
				:SvgObject(gdi)
			{
				_style = style;
				_width = (width > 0) ? width : 1;
				_color = color;
				//IGdiObject::setType("Pen");
			}

			/// Object style.
		int SvgPen::Style()
			{
				return _style;
			}

			/// Object width.
		int SvgPen::Width()
			{
				return _width;
			}

			/// Object color.
		int SvgPen::Color()
			{
				return _color;
			}

			/// Serves as the default hash function.

		int SvgPen::GetHashCode()
			{
				int PRIME = 31;
				int result = 1;
				result = PRIME * result + _color;
				result = PRIME * result + _style;
				result = PRIME * result + _width;
				return result;
			}
			/// Determines whether the specified object is equal to the current object.
		bool SvgPen::Equals(void* obj)
			{
				if (this == obj)
					return true;
				if (obj == NULL)
					return false;
				SvgPen *other = (SvgPen*)obj;
				if (_color != other->_color)
					return false;
				if (_style != other->_style)
					return false;
				if (_width != other->_width)
					return false;
				return true;
			}
			/// Create inner text element.
		tinyxml2::XMLText* SvgPen::NewText(string id)
			{
				return GDI()->Document()->NewText(string( "." + id + " { " + this->ToString() + " }\r\n").c_str());
			}

			/// Returns a string that represents the current object.
		string SvgPen::ToString()
			{
				string buffer = "";

				if (_style == (int)PenPSEnum::PS_NULL)
				{
					buffer += "stroke: none; ";
				}
				else
				{
					char text[100] = {};
					// stroke
					buffer += "stroke: " + ToColor(_color) + "; ";

					// stroke-width
					sprintf(text, "stroke-width: %d; ", _width);
					buffer += string(text);

					// stroke-linejoin
					buffer += "stroke-linejoin: round; ";

					// stroke-dasharray
					if (_width == 1 && (int)PenPSEnum::PS_DASH <= _style && _style <= (int)PenPSEnum::PS_DASHDOTDOT)
					{
						buffer += "stroke-dasharray: ";

						switch (_style)
						{
						case (int)PenPSEnum::PS_DASH:
						{
							memset(text, 0x00, sizeof(text));
							sprintf(text, "%d,%d", ToRealSize(18), ToRealSize(6));
							buffer += string(text);
							break;
						}
						case (int)PenPSEnum::PS_DOT:
						{
							memset(text, 0x00, sizeof(text));
							sprintf(text, "%d,%d", ToRealSize(3), ToRealSize(3));
							buffer += string(text);
							break;
						}
						case (int)PenPSEnum::PS_DASHDOT:
						{
							memset(text, 0x00, sizeof(text));
							sprintf(text, "%d,%d,%d,%d", ToRealSize(9), ToRealSize(3), ToRealSize(3), ToRealSize(3));
							buffer += string(text);
							break;
						}
						case (int)PenPSEnum::PS_DASHDOTDOT:
						{
							memset(text, 0x00, sizeof(text));
							sprintf(text, "%d,%d,%d,%d", ToRealSize(9), ToRealSize(3), ToRealSize(3), ToRealSize(3), ToRealSize(3));
							buffer += string(text);
							break;
						}
						}
						buffer += "; ";
					}
				}
				return buffer;
			}

}
