#include "SvgRectRegion.h"

//#include "SvgRegion.h"
#include "SvgGdi.h"
#include "SvgDc.h"
//#include "tinyxml2.h"
//#include "tool.h"


namespace WMFConverter{


		SvgRectRegion::SvgRectRegion(SvgGdi *gdi, int left, int top, int right, int bottom)
				: SvgRegion(gdi)
			{
				_left = left;
				_top = top;
				_right = right;
				_bottom = bottom;
			}

			/// Left value.
		int SvgRectRegion::Left()
			{
				return _left;
			}

			/// Top value.
		int SvgRectRegion::Top()
			{
				return _top;
			}

			/// Right value.
		int SvgRectRegion::Right()
			{
				return _right;
			}

			/// Bottom value.
		int SvgRectRegion::Bottom()
			{
				return _bottom;
			}

			/// Create rect element.
		tinyxml2::XMLElement* SvgRectRegion::CreateElement()
			{
				tinyxml2::XMLElement *elem = GDI()->Document()->NewElement("rect");
				elem->SetAttribute("x", intToString((int)(GDI()->DC()->ToAbsoluteX(this->Left()))).c_str());
				elem->SetAttribute("y", intToString((int)GDI()->DC()->ToAbsoluteY(Top())).c_str());
				elem->SetAttribute("width", intToString((int)GDI()->DC()->ToRelativeX(Right() - Left())).c_str());
				elem->SetAttribute("height", intToString((int)GDI()->DC()->ToRelativeY(Bottom() - Top())).c_str());
				return (elem);
			}
			/// Serves as the default hash function.
		int SvgRectRegion::GetHashCode() {
				int prime = 31;
				int result = 1;
				result = prime * result + _bottom;
				result = prime * result + _left;
				result = prime * result + _right;
				result = prime * result + _top;
				return result;
			}

			/// Determines whether the specified object is equal to the current object.
		bool SvgRectRegion::Equals(void *obj)
			{
				if (this == obj)
					return true;
				if (obj == NULL)
					return false;
				SvgRectRegion *other = (SvgRectRegion*)obj;
				if (_bottom != other->Bottom())
					return false;
				if (_left != other->Left())
					return false;
				if (_right != other->Right())
					return false;
				if (_top != other->Top())
					return false;
				return true;
			}

}


