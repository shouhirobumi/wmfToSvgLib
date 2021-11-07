#include "SvgDc.h"

#include "SvgGdi.h"
#include "SvgPen.h"
#include "SvgFont.h"
#include "SvgBrush.h"

namespace WMFConverter{

		SvgDc::SvgDc(SvgGdi *gdi){
				initialPrivateData();
				_gdi = gdi;
			}
			/// Background color.
		int SvgDc::BkColor(){
				return _bkColor;
			}
		void SvgDc::SetBkColor(int val){
				_bkColor = val;
			}

			/// Background mode.
		int SvgDc::BkMode(){
				return _bkMode;
			}
		void SvgDc::SetBkMode(int val){
				_bkMode = val;
			}

			/// Text color.
		int SvgDc::TextColor(){
				return _textColor;
			}
		void SvgDc::SetTextColor(int val){
				_textColor = val;
			}

		int SvgDc::PolyFillMode(){
				return _polyFillMode;
			}
		void SvgDc::SetPolyFillMode(int val){
				_polyFillMode = val;
			}

		int SvgDc::RelAbs(){
				return _relAbsMode;
			}
		void SvgDc::SetRelAbs(int val){
				_relAbsMode = val;
			}

		int SvgDc::ROP2(){
				return _rop2Mode;
			}
		void SvgDc::SetROP2(int val){
				_rop2Mode = val;
			}

		int SvgDc::StretchBltMode(){
				return _stretchBltMode;
			}
		void SvgDc::SetStretchBltMode(int val){
				_stretchBltMode = val;
			}

		int SvgDc::TextSpace(){
				return _textSpace;
			}
		void SvgDc::SetTextSpace(int val){
				_textSpace = val;
			}

		int SvgDc::TextAlign(){
				return _textAlign;
			}
		void SvgDc::SetTextAlign(int val){
				_textAlign = val;
			}

		int SvgDc::TextCharacterExtra(){
				return _textDx;
			}
		void SvgDc::SetTextCharacterExtra(int val){
				_textDx = val;
			}

		int SvgDc::Layout(){
				return _layout;
			}
		void SvgDc::SetLayout(int val){
				_layout = val;
			}

		int SvgDc::MapperFlags(){
				return _mapperFlags;
			}
		void SvgDc::SetMapperFlags(int val){
				_mapperFlags = val;
			}

		SvgBrush* SvgDc::Brush(){
				return _brush;
			}
		void SvgDc::SetBrush(SvgBrush* val){
				_brush = val;
			}

		SvgFont* SvgDc::Font(){
				return _font;
			}
		void SvgDc::SetFont(SvgFont* val){
				_font = val;
			}

		SvgPen* SvgDc::Pen(){
				return _pen;
			}
		void SvgDc::SetPen(SvgPen* val){
				_pen = val;
			}

		tinyxml2::XMLElement* SvgDc::Mask(){
				return _mask;
			}
		void SvgDc::SetMask(tinyxml2::XMLElement* val){
				_mask = val;
			}

		int SvgDc::CurrentX(){
				return _cx;
			}
		void SvgDc::SetCurrentX(int val){
				_cx = val;
			}

		int SvgDc::CurrentY(){
				return _cy;
			}
		void SvgDc::SetCurrentY(int val){
				_cy = val;
			}

		int SvgDc::OffsetClipX(){
				return _cox;
			}
		void SvgDc::SetOffsetClipX(int val){
				_cox = val;
			}

		int SvgDc::OffsetClipY(){
				return _coy;
			}
		void SvgDc::SetOffsetClipY(int val){
				_coy = val;
			}

		int SvgDc::MapMode(){
				return _mapMode;
			}

		int SvgDc::Dpi(){
				return _dpi;
			}

		int SvgDc::WindowX(){
				return _wx;
			}

		int SvgDc::WindowY(){
				return _wy;
			}

		int SvgDc::WindowWidth(){
				return _ww;
			}

		int SvgDc::WindowHeight(){
				return _wh;
			}


			/// Specifies which window point maps to the viewport origin (0,0).
		void SvgDc::SetWindowOrgEx(int x, int y, WMFConverter::Point *old)
			{
				if (old != NULL)
				{
					old->X = this->_wx;
					old->Y = this->_wy;
				}
				this->_wx = x;
				this->_wy = y;
			}

			/// Sets the horizontal and vertical extents of the window for a device context by using the specified values.
		void SvgDc::SetWindowExtEx(int width, int height, WMFConverter::Size *old)
			{
				if (old != NULL)
				{
					old->Width = _ww;
					old->Height = _wh;
				}
				_ww = width;
				_wh = height;
			}

			/// Modifies the window origin for a device context using the specified horizontal and vertical offsets.
		void SvgDc::OffSetWindowOrgEx(int x, int y, WMFConverter::Point *old)
			{
				if (old != NULL)
				{
					old->X = _wox;
					old->Y = _woy;
				}
				_wox += x;
				_woy += y;
			}

			/// Modifies the window for a device context using the ratios formed by the specified multiplicands and divisors.
		void SvgDc::ScaleWindowExtEx(int x, int xd, int y, int yd, WMFConverter::Size *old)
			{
				// TODO
				_wsx = (_wsx * x) / xd;
				_wsy = (_wsy * y) / yd;
			}

			/// Specifies which device point maps to the window origin (0,0).
		void SvgDc::SetViewportOrgEx(int x, int y, WMFConverter::Point *old)
			{
				if (old != NULL)
				{
					old->X = _vx;
					old->Y = _vy;
				}
				_vx = x;
				_vy = y;
			}

			/// Sets the horizontal and vertical extents of the viewport for a device context by using the specified values.
		void SvgDc::SetViewportExtEx(int width, int height, WMFConverter::Size *old)
			{
				if (old != NULL)
				{
					old->Width = _vw;
					old->Height = _vh;
				}
				_vw = width;
				_vh = height;
			}

			/// Modifies the viewport origin for a device context using the specified horizontal and vertical offsets.
		void SvgDc::OffSetViewportOrgEx(int x, int y, WMFConverter::Point *old)
			{
				if (old != NULL)
				{
					old->X = _vox;
					old->Y = _voy;
				}
				_vox = x;
				_voy = y;
			}

			/// Modifies the viewport for a device context using the ratios formed by the specified multiplicands and divisors.
		void SvgDc::ScaleViewportExtEx(int x, int xd, int y, int yd, WMFConverter::Size *old)
			{
				// TODO
				_vsx = (_vsx * x) / xd;
				_vsy = (_vsy * y) / yd;
			}

			/// Moves the clipping region of a device context by the specified offsets.
		void SvgDc::OffSetClipRgn(int x, int y)
			{
				_cox = x;
				_coy = y;
			}

			/// Sets the mapping mode of the specified device context. 
			/// The mapping mode defines the unit of measure used to transform page-space units into device-space units, and also defines the orientation of the device's x and y axes.
		void SvgDc::SetMapMode(int mode)
			{
				_mapMode = mode;
				switch (mode)
				{
				case (int)GdiEnum::MM_HIENGLISH:
					_mx = 0.09;
					_my = -0.09;
					break;
				case (int)GdiEnum::MM_LOENGLISH:
					_mx = 0.9;
					_my = -0.9;
					break;
				case (int)GdiEnum::MM_HIMETRIC:
					_mx = 0.03543307;
					_my = -0.03543307;
					break;
				case (int)GdiEnum::MM_LOMETRIC:
					_mx = 0.3543307;
					_my = -0.3543307;
					break;
				case (int)GdiEnum::MM_TWIPS:
					_mx = 0.0625;
					_my = -0.0625;
					break;
				default:
					_mx = 1.0;
					_my = 1.0;
					break;
				}
			}

			/// Updates the current position to the specified point and optionally returns the previous position.
		void SvgDc::MoveToEx(int x, int y, WMFConverter::Point *old)
			{
				if (old != NULL)
				{
					old->X = _cx;
					old->Y = _cy;
				}
				_cx = x;
				_cy = y;
			}

			/// Return the absolute X position from x point.
		double SvgDc::ToAbsoluteX(double x)
			{
				// TODO Handle Viewport
				return ((_ww >= 0) ? 1 : -1) * (_mx * x - (_wx + _wox)) / _wsx;
			}

			/// Return the absolute Y position from y point.
		double SvgDc::ToAbsoluteY(double y)
			{
				// TODO Handle Viewport
				return ((_wh >= 0) ? 1 : -1) * (_my * y - (_wy + _woy)) / _wsy;
			}

			/// Return the relative X position from x point.
		double SvgDc::ToRelativeX(double x)
			{
				// TODO Handle Viewport
				return ((_ww >= 0) ? 1 : -1) * (_mx * x) / _wsx;
			}

			/// Return the relative Y position from y point.
		double SvgDc::ToRelativeY(double y)
			{
				// TODO Handle Viewport
				return ((_wh >= 0) ? 1 : -1) * (_my * y) / _wsy;
			}

			/// Define Dpi value
		void SvgDc::SetDpi(int dpi)
			{
				_dpi = (dpi > 0) ? dpi : 1440;
			}

		string SvgDc::GetRopFilter(long rop)
			{
				string name = "";
				tinyxml2::XMLDocument *doc = _gdi->Document();

				if (rop == (int)GdiEnum::BLACKNESS)
				{
					name = "BLACKNESS_FILTER";

					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "SourceGraphic");
						feColorMatrix->SetAttribute("values", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0");
						filter->InsertEndChild(feColorMatrix);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::NOTSRCERASE)
				{
					name = "NOTSRCERASE_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feComposite = doc->NewElement("feComposite");
						feComposite->SetAttribute("in", "SourceGraphic");
						feComposite->SetAttribute("in2", "BackgroundImage");
						feComposite->SetAttribute("operator", "arithmetic");
						feComposite->SetAttribute("k1", "1");
						feComposite->SetAttribute("result", "result0");
						filter->InsertEndChild(feComposite);

						tinyxml2::XMLElement *feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("in", "result0");
						feColorMatrix->SetAttribute("values", "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0");
						filter->InsertEndChild(feColorMatrix);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::NOTSRCCOPY)
				{
					name = "NOTSRCCOPY_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "SourceGraphic");
						feColorMatrix->SetAttribute("values", "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0");
						filter->InsertEndChild(feColorMatrix);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::SRCERASE)
				{
					name = "SRCERASE_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "BackgroundImage");
						feColorMatrix->SetAttribute("values", "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0");
						feColorMatrix->SetAttribute("result", "result0");
						filter->InsertEndChild(feColorMatrix);

						tinyxml2::XMLElement* feComposite = doc->NewElement("feComposite");
						feComposite->SetAttribute("in", "SourceGraphic");
						feComposite->SetAttribute("in2", "result0");
						feComposite->SetAttribute("operator", "arithmetic");
						feComposite->SetAttribute("k2", "1");
						feComposite->SetAttribute("k3", "1");
						filter->InsertEndChild(feComposite);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::PATINVERT)
				{
					// TODO
				}
				else if (rop == (int)GdiEnum::SRCINVERT)
				{
					// TODO
				}
				else if (rop == (int)GdiEnum::DSTINVERT)
				{
					name = "DSTINVERT_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.SetIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "BackgroundImage");
						feColorMatrix->SetAttribute("values", "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0");
						filter->InsertEndChild(feColorMatrix);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::SRCAND)
				{
					name = "SRCAND_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feComposite = doc->NewElement("feComposite");
						feComposite->SetAttribute("in", "SourceGraphic");
						feComposite->SetAttribute("in2", "BackgroundImage");
						feComposite->SetAttribute("operator", "arithmetic");
						feComposite->SetAttribute("k1", "1");
						filter->InsertEndChild(feComposite);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::MERGEPAINT)
				{
					name = "MERGEPAINT_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "SourceGraphic");
						feColorMatrix->SetAttribute("values", "-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0");
						feColorMatrix->SetAttribute("result", "result0");
						filter->InsertEndChild(feColorMatrix);

						tinyxml2::XMLElement* feComposite = doc->NewElement("feComposite");
						feComposite->SetAttribute("in", "result0");
						feComposite->SetAttribute("in2", "BackgroundImage");
						feComposite->SetAttribute("operator", "arithmetic");
						feComposite->SetAttribute("k1", "1");
						filter->InsertEndChild(feComposite);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::MERGECOPY)
				{
					// TODO
				}
				else if (rop == (int)GdiEnum::SRCPAINT)
				{
					name = "SRCPAINT_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.setIdAttribute("id", true);

						tinyxml2::XMLElement* feComposite = doc->NewElement("feComposite");
						feComposite->SetAttribute("in", "SourceGraphic");
						feComposite->SetAttribute("in2", "BackgroundImage");
						feComposite->SetAttribute("operator", "arithmetic");
						feComposite->SetAttribute("k2", "1");
						feComposite->SetAttribute("k3", "1");
						filter->InsertEndChild(feComposite);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}
				else if (rop == (int)GdiEnum::PATCOPY)
				{
					// TODO
				}
				else if (rop == (int)GdiEnum::PATPAINT)
				{
					// TODO
				}
				else if (rop == (int)GdiEnum::WHITENESS)
				{
					name = "WHITENESS_FILTER";
					tinyxml2::XMLElement *filter = doc->FirstChildElement(name.c_str());
					if (filter == NULL)
					{
						filter = _gdi->Document()->NewElement("filter");
						filter->SetAttribute("id", name.c_str());
						//filter.SetIdAttribute("id", true);

						tinyxml2::XMLElement* feColorMatrix = doc->NewElement("feColorMatrix");
						feColorMatrix->SetAttribute("type", "matrix");
						feColorMatrix->SetAttribute("in", "SourceGraphic");
						feColorMatrix->SetAttribute("values", "1 0 0 0 1 0 1 0 0 1 0 0 1 0 1 0 0 0 1 0");
						filter->InsertEndChild(feColorMatrix);

						_gdi->DefsElement()->InsertEndChild(filter);
					}
				}

				if (name != "")
				{
					if (doc->RootElement()->FindAttribute("enable-background") != NULL)
					{
						doc->RootElement()->SetAttribute("enable-background", "new");
					}
					return "url(#" + name + ")";
				}
				return NULL;
			}

		SvgDc* SvgDc::Clone()
		{
			SvgDc *obj = new SvgDc(_gdi);
			return obj;
		}

		/// Returns a string that represents the current object.
		string SvgDc::ToString()
		{

			char str[1000] = {};
			sprintf(str, "SvgDc [gdi=%d, dpi=%d, wx=%d, wy=%d, ww=%d, wh=%d, wox=%d, woy=%d, wsx=%d, wsy=%d, mx=%d, my=%d, vx=%d, vy=%d, vw=%d, vh="
				"%d, vox=%d, voy=%d, vsx=%d, vsy=%d, cx=%d, cy=%d, mapMode=%d, bkColor=%d, bkMode=%d, textColor=%d, textSpace=%d, textAlign=%d, textDx="
				"%d, polyFillMode=%d, relAbsMode=%d, rop2Mode=%d, stretchBltMode=%d, brush=%d, font=%d, pen=%d]", _gdi, _dpi, _wx, _wy, _ww, _wh, _wox,
				_woy, _wsx, _wsy, _mx, _my, _vx, _vy, _vw, _vh, _vox, _voy, _vsx, _vsy, _cx, _cy, _mapMode, _bkColor, _bkMode, _textColor, _textSpace,
				_textAlign, _textDx, _polyFillMode, _relAbsMode, _rop2Mode, _stretchBltMode, _brush, _font, _pen);

			return (std::string)str;
		}


		void SvgDc::initialPrivateData(){
			_dpi = 1440;
			_wx = 0;
			_wy = 0;
			_ww = 0;
			_wh = 0;
			_wox = 0;
			_woy = 0;
			_wsx = 1.0;
			_wsy = 1.0;
			_mx = 1.0;
			_my = 1.0;
			_vx = 0;
			_vy = 0;
			_vw = 0;
			_vh = 0;
			_vox = 0;
			_voy = 0;
			_vsx = 1.0;
			_vsy = 1.0;
			_cx = 0;
			_cy = 0;
			_cox = 0;
			_coy = 0;

			_mapMode = (int)GdiEnum::MM_TEXT;
			_bkColor = 0x00FFFFFF;
			_bkMode = (int)GdiEnum::OPAQUE;
			_textColor = 0x00000000;
			_textSpace = 0;
			_textAlign = (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_LEFT;
			_textDx = 0;
			_polyFillMode = (int)GdiEnum::ALTERNATE;
			_relAbsMode = 0;
			_rop2Mode = (int)GdiEnum::R2_COPYPEN;
			_stretchBltMode = (int)GdiEnum::STRETCH_ANDSCANS;
			_layout = 0;
			_mapperFlags = 0;
			_brush = NULL;
			_font = NULL;
			_pen = NULL;
			_mask = NULL;

		}

}
