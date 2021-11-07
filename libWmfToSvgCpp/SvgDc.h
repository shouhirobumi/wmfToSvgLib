#ifndef _SVG_DC_H_
#define _SVG_DC_H_

#include <string>
#include "gdiInfoDefine.h"
#include "tinyxml2.h"
//#include "SvgGdi.h"
//#include "SvgPen.h"
//#include "SvgFont.h"
//#include "SvgBrush.h"
#include "Point.h"
#include "Size.h"
using namespace std;

namespace WMFConverter{
		class SvgGdi;
		class SvgBrush;
		class SvgFont;
		class SvgPen;
		//class Size;
		class SvgDc
		{
		public:
			SvgDc(SvgGdi *gdi);
			/// Background color.
			int BkColor();
			void SetBkColor(int val);

			/// Background mode.
			int BkMode();
			void SetBkMode(int val);

			/// Text color.
			int TextColor();
			void SetTextColor(int val);

			int PolyFillMode();
			void SetPolyFillMode(int val);

			int RelAbs();
			void SetRelAbs(int val);

			int ROP2();
			void SetROP2(int val);

			int StretchBltMode();
			void SetStretchBltMode(int val);

			int TextSpace();
			void SetTextSpace(int val);

			int TextAlign();
			void SetTextAlign(int val);

			int TextCharacterExtra();
			void SetTextCharacterExtra(int val);

			int Layout();
			void SetLayout(int val);

			int MapperFlags();
			void SetMapperFlags(int val);

			SvgBrush* Brush();
			void SetBrush(SvgBrush* val);

			SvgFont* Font();
			void SetFont(SvgFont* val);

			SvgPen* Pen();
			void SetPen(SvgPen* val);

			tinyxml2::XMLElement* Mask();
			void SetMask(tinyxml2::XMLElement* val);

			int CurrentX();
			void SetCurrentX(int val);

			int CurrentY();
			void SetCurrentY(int val);

			int OffsetClipX();
			void SetOffsetClipX(int val);

			int OffsetClipY();
			void SetOffsetClipY(int val);

			int MapMode();

			int Dpi();

			int WindowX();

			int WindowY();

			int WindowWidth();

			int WindowHeight();


			/// Specifies which window point maps to the viewport origin (0,0).
			void SetWindowOrgEx(int x, int y, WMFConverter::Point *old);

			/// Sets the horizontal and vertical extents of the window for a device context by using the specified values.
			void SetWindowExtEx(int width, int height, WMFConverter::Size *old);
			/// Modifies the window origin for a device context using the specified horizontal and vertical offsets.
			void OffSetWindowOrgEx(int x, int y, WMFConverter::Point *old);

			/// Modifies the window for a device context using the ratios formed by the specified multiplicands and divisors.
			void ScaleWindowExtEx(int x, int xd, int y, int yd, WMFConverter::Size *old);
			/// Specifies which device point maps to the window origin (0,0).
			void SetViewportOrgEx(int x, int y, WMFConverter::Point *old);
			/// Sets the horizontal and vertical extents of the viewport for a device context by using the specified values.
			void SetViewportExtEx(int width, int height, WMFConverter::Size *old);
			/// Modifies the viewport origin for a device context using the specified horizontal and vertical offsets.
			void OffSetViewportOrgEx(int x, int y, WMFConverter::Point *old);
			/// Modifies the viewport for a device context using the ratios formed by the specified multiplicands and divisors.
			void ScaleViewportExtEx(int x, int xd, int y, int yd, WMFConverter::Size *old);
			/// Moves the clipping region of a device context by the specified offsets.
			void OffSetClipRgn(int x, int y);
			/// Sets the mapping mode of the specified device context. 
			/// The mapping mode defines the unit of measure used to transform page-space units into device-space units, and also defines the orientation of the device's x and y axes.
			void SetMapMode(int mode);
			/// Updates the current position to the specified point and optionally returns the previous position.
			void MoveToEx(int x, int y, WMFConverter::Point *old);
			/// Return the absolute X position from x point.
			double ToAbsoluteX(double x);
			/// Return the absolute Y position from y point.
			double ToAbsoluteY(double y);
			/// Return the relative X position from x point.
			double ToRelativeX(double x);
			/// Return the relative Y position from y point.
			double ToRelativeY(double y);
			/// Define Dpi value
			void SetDpi(int dpi);
			string GetRopFilter(long rop);
			SvgDc* Clone();
			/// Returns a string that represents the current object.
			string ToString();
		private:
			SvgGdi* _gdi;
			SvgBrush* _brush;
			SvgFont* _font;
			SvgPen* _pen;

			tinyxml2::XMLElement* _mask;

			void initialPrivateData();
			int _dpi ;

			// window
			int _wx;
			int _wy;
			int _ww;
			int _wh;

			// window offset
			int _wox ;
			int _woy ;

			// window scale
			double _wsx ;
			double _wsy ;

			// mapping scale
			double _mx ;
			double _my ;

			// viewport
			int _vx ;
			int _vy ;
			int _vw ;
			int _vh ;

			// viewport offset
			int _vox ;
			int _voy ;

			// viewport scale
			double _vsx ;
			double _vsy ;

			// current location
			int _cx ;
			int _cy ;

			// clip offset
			int _cox ;
			int _coy ;

			int _mapMode;
			int _bkColor;
			int _bkMode ;
			int _textColor ;
			int _textSpace ;
			int _textAlign ;
			int _textDx ;
			int _polyFillMode ;
			int _relAbsMode ;
			int _rop2Mode ;
			int _stretchBltMode;
			long _layout ;
			long _mapperFlags ;
		};

}



#endif