#include "SvgBrush.h"

//#include "SvgObject.h"
//#include "IGdiBrush.h"
#include "SvgGdi.h"
#include "SvgDc.h"
//#include "tool.h"
namespace WMFConverter{

		SvgBrush::SvgBrush(
				SvgGdi *gdi,
				int style,
				int color,
				int hatch)
				: SvgObject(gdi)
			{
				initialPrivateData();
				_style = style;
				_color = color;
				_hatch = hatch;
			}

		int SvgBrush::Style(){
				return _style;
			}
		int SvgBrush::Color(){
				return _color;
			}
		int SvgBrush::Hatch(){
				return _hatch;
			}

		tinyxml2::XMLElement* SvgBrush::CreateFillPattern(string id)
			{
				tinyxml2::XMLElement *pattern = GDI()->Document()->NewElement("pattern");
				if (_style == (int)BrushBSEnum::BS_HATCHED)
				{
					pattern->SetAttribute("id", id.c_str());
					pattern->SetAttribute("patternUnits", "userSpaceOnUse");
					pattern->SetAttribute("x", intToString(ToRealSize(0)).c_str());
					pattern->SetAttribute("y", intToString(ToRealSize(0)).c_str());
					pattern->SetAttribute("width", intToString(ToRealSize(8)).c_str());
					pattern->SetAttribute("height", intToString(ToRealSize(8)).c_str());
					GDI()->Document()->InsertEndChild(pattern);

					if (GDI()->DC()->BkMode() == (int)GdiEnum::OPAQUE)
					{
						tinyxml2::XMLElement *rect = GDI()->Document()->NewElement("rect");
						rect->SetAttribute("fill", (SvgObject::ToColor(GDI()->DC()->BkColor())).c_str());
						rect->SetAttribute("x", intToString(ToRealSize(0)).c_str());
						rect->SetAttribute("y", intToString(ToRealSize(0)).c_str());
						rect->SetAttribute("width", intToString(ToRealSize(8)).c_str());
						rect->SetAttribute("height", intToString(ToRealSize(8)).c_str());
						//pattern->InsertEndChild(rect);
						pattern->InsertEndChild(rect);
					}

					switch (_hatch)
					{

					case (int)BrushHSEnum::HS_HORIZONTAL:
					{
						tinyxml2::XMLElement* path = GDI()->Document()->NewElement("line");
						path->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path->SetAttribute("x1", intToString(ToRealSize(0)).c_str());
						path->SetAttribute("y1", intToString(ToRealSize(4)).c_str());
						path->SetAttribute("x2", intToString(ToRealSize(8)).c_str());
						path->SetAttribute("y2", intToString(ToRealSize(4)).c_str());
						pattern->InsertEndChild(path);
					} break;
					case (int)BrushHSEnum::HS_VERTICAL:
					{
						tinyxml2::XMLElement* path = GDI()->Document()->NewElement("line");
						path->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path->SetAttribute("x1", intToString(ToRealSize(4)).c_str());
						path->SetAttribute("y1", intToString(ToRealSize(0)).c_str());
						path->SetAttribute("x2", intToString(ToRealSize(4)).c_str());
						path->SetAttribute("y2", intToString(ToRealSize(8)).c_str());
						pattern->InsertEndChild(path);
					} break;
					case (int)BrushHSEnum::HS_FDIAGONAL:
					{
						tinyxml2::XMLElement* path = GDI()->Document()->NewElement("line");
						path->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path->SetAttribute("x1", intToString(ToRealSize(0)).c_str());
						path->SetAttribute("y1", intToString(ToRealSize(0)).c_str());
						path->SetAttribute("x2", intToString(ToRealSize(8)).c_str());
						path->SetAttribute("y2", intToString(ToRealSize(8)).c_str());
						pattern->InsertEndChild(path);
					} break;
					case (int)BrushHSEnum::HS_BDIAGONAL:
					{
						tinyxml2::XMLElement* path = GDI()->Document()->NewElement("line");
						path->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path->SetAttribute("x1",  intToString(ToRealSize(0)).c_str());
						path->SetAttribute("y1",  intToString(ToRealSize(8)).c_str());
						path->SetAttribute("x2",  intToString(ToRealSize(8)).c_str());
						path->SetAttribute("y2",  intToString(ToRealSize(0)).c_str());
						pattern->InsertEndChild(path);
					} break;
					case (int)BrushHSEnum::HS_CROSS:
					{
						tinyxml2::XMLElement* path1 = GDI()->Document()->NewElement("line");
						path1->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path1->SetAttribute("x1",  intToString(ToRealSize(0)).c_str());
						path1->SetAttribute("y1",  intToString(ToRealSize(4)).c_str());
						path1->SetAttribute("x2",  intToString(ToRealSize(8)).c_str());
						path1->SetAttribute("y2",  intToString(ToRealSize(4)).c_str());
						pattern->InsertEndChild(path1);
						tinyxml2::XMLElement *path2 = GDI()->Document()->NewElement("line");
						path2->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path2->SetAttribute("x1",  intToString(ToRealSize(4)).c_str());
						path2->SetAttribute("y1",  intToString(ToRealSize(0)).c_str());
						path2->SetAttribute("x2",  intToString(ToRealSize(4)).c_str());
						path2->SetAttribute("y2",  intToString(ToRealSize(8)).c_str());
						pattern->InsertEndChild(path2);
					} break;
					case (int)BrushHSEnum::HS_DIAGCROSS:
					{
						tinyxml2::XMLElement* path1 = GDI()->Document()->NewElement("line");
						path1->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path1->SetAttribute("x1",  intToString(ToRealSize(0)).c_str());
						path1->SetAttribute("y1",  intToString(ToRealSize(0)).c_str());
						path1->SetAttribute("x2",  intToString(ToRealSize(8)).c_str());
						path1->SetAttribute("y2",  intToString(ToRealSize(8)).c_str());
						pattern->InsertEndChild(path1);
						tinyxml2::XMLElement *path2 = GDI()->Document()->NewElement("line");
						path2->SetAttribute("stroke", SvgObject::ToColor(_color).c_str());
						path2->SetAttribute("x1",  intToString(ToRealSize(0)).c_str());
						path2->SetAttribute("y1",  intToString(ToRealSize(8)).c_str());
						path2->SetAttribute("x2",  intToString(ToRealSize(8)).c_str());
						path2->SetAttribute("y2",  intToString(ToRealSize(0)).c_str());
						pattern->InsertEndChild(path2);
					} break;
					default:
						break;
					}
				}

				return pattern;
			}

		/// Serves as the default hash function.
		int SvgBrush::GetHashCode()
		{
			int PRIME = 31;
			int result = 1;
			result = PRIME * result + _color;
			result = PRIME * result + _hatch;
			result = PRIME * result + _style;
			return result;
		}

		/// Determines whether the specified object is equal to the current object.
		bool SvgBrush::Equals(void* obj)
		{
			if (this == obj)
				return true;
			if (obj == NULL)
				return false;
			SvgBrush* other = (SvgBrush*)obj;
			if (_color != other->_color)
				return false;
			if (_hatch != other->_hatch)
				return false;
			if (_style != other->_style)
				return false;
			return true;
		}

		/// Create element inner text.
		tinyxml2::XMLText* SvgBrush::NewText(string id)
		{
			string textData = "." + id + " { " + ToString() + " }\r\n";
			return GDI()->Document()->NewText(textData.c_str());
		}

		/// Returns a string that represents the current object.
		string SvgBrush::ToString()
		{
			string buffer = "";

			// fill
			switch (_style)
			{
			case (int)BrushBSEnum::BS_SOLID:
				buffer = "fill: " + SvgObject::ToColor(_color) + "; ";
				break;
			case (int)BrushBSEnum::BS_HATCHED:
				break;
			default:
				buffer = "fill: none; ";
				break;
			}
			return buffer;
		}
		void SvgBrush::initialPrivateData(){
			_style = 0;
			_color = 0;
			_hatch = 0;
		}

}

