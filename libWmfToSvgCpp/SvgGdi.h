#ifndef _SVG_GDI_H_
#define _SVG_GDI_H_


#include <algorithm>
#include <string>
#include <map>
#include "tinyxml2.h"
#include "IGdi.h"

//#include "Properties.h"
//#include "SvgDc.h"
//#include "SvgPen.h"
//#include "SvgBrush.h"
//#include "SvgFont.h"
//using namespace tinyxml2;

using namespace std;

namespace WMFConverter{


		class Properties ;
		class SvgDc;
		class SvgBrush;
		class SvgPen;
		class SvgFont;
		//class IGdi;

		class SvgGdi : public IGdi
		{

		public:
			SvgGdi();

			SvgGdi(bool compatible);

			void Write(string file);

			/// Write SVG XML document.
			void Write(FILE* output);
			/// Get property value using key value.
			string GetProperty(string key);
			 /// Define header document.
			void PlaceableHeader(int wsx, int wsy, int wex, int wey, int dpi);

			 /// Initialize header document.
			void Header();

			 /// Replaces entries in the specified logical palette.
			void AnimatePalette(IGdiPalette *palette, int startIndex, int* entries);

			 /// Draws an elliptical arc.
			void Arc(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya);
			 /// Execute a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
			void BitBlt(char* image, int dx, int dy, int dw, int dh,int sx, int sy, long rop);
			 /// Draws a chord (a region bounded by the intersection of an ellipse and a line segment, called a secant).
			 /// The chord is outlined by using the current pen and filled by using the current brush.
			void Chord(int sxr, int syr, int exr, int eyr, int sxa, int sya,
				int exa, int eya);

			 /// Creates a logical brush that has the specified style, color, and pattern.
			WMFConverter::IGdiBrush* CreateBrushIndirect(int style, int color, int hatch);

			 /// Creates a logical font that has the specified characteristics. 
			 /// The font can subsequently be selected as the current font for any device context.
			WMFConverter::IGdiFont* CreateFontIndirect(int height, int width, int escapement,
				int orientation, int weight, bool italic, bool underline,
				bool strikeout, int charset, int outPrecision,
				int clipPrecision, int quality, int pitchAndFamily, char* faceName);
			 /// Creates a logical palette.

			WMFConverter::IGdiPalette* CreatePalette(int version, int* entries);

			 /// Creates a logical brush with the specified bitmap pattern.
			 /// The bitmap can be a DIB section bitmap, which is created by the CreateDIBSection function, or it can be a device-dependent bitmap.
			WMFConverter::IGdiPatternBrush* CreatePatternBrush(char* image);

			 /// Creates a logical cosmetic pen that has the style, width, and color specified in a structure.
			WMFConverter::IGdiPen* CreatePenIndirect(int style, int width, int color);

			 /// Creates a rectangular region.
			WMFConverter::IGdiRegion* CreateRectRgn(int left, int top, int right, int bottom);
			 /// Deletes a logical pen, brush, font, bitmap, region, or palette, freeing all system resources associated with the object. 
			 /// After the object is deleted, the specified handle is no longer valid.

			void DeleteObject(WMFConverter::IGdiObject *obj);
			  /// Function performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
			void DibBitBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, long rop);
			  /// Create Dib Pattern Brush object instance.
			WMFConverter::IGdiPatternBrush* DibCreatePatternBrush(char* image, int usage);
			  /// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			  /// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
			void DibStretchBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, int sw, int sh, long rop);
			  /// Draws an ellipse. 
			  /// The center of the ellipse is the center of the specified bounding rectangle.
			  /// The ellipse is outlined by using the current pen and is filled by using the current brush.
			void Ellipse(int sx, int sy, int ex, int ey);
			  /// TODO
			void Escape(char* data);
			  ///  Creates a new clipping region that consists of the existing clipping region minus the specified rectangle.
			int ExcludeClipRect(int left, int top, int right, int bottom);
			  /// TODO
			void ExtFloodFill(int x, int y, int color, int type);

			  /// Draws text using the currently selected font, background color, and text color. 
			  /// You can optionally provide dimensions to be used for clipping, opaquing, or both.
			void ExtTextOut(int x, int y, int options, int* rect, char* text, int* dx);

			  /// Fills a region by using the specified brush.
			void FillRgn(IGdiRegion* rgn, IGdiBrush* brush);

			  /// TODO
			void FloodFill(int x, int y, int color);

			  /// TODO
			void FrameRgn(IGdiRegion* rgn, IGdiBrush* brush, int width, int height);

			  /// TODO
			void IntersectClipRect(int left, int top, int right, int bottom);

			  /// Inverts the colors in the specified region.
			void InvertRgn(IGdiRegion* rgn);

			  /// Draws a line from the current position up to, but not including, the specified point.
			void LineTo(int ex, int ey);

			  /// Updates the current position to the specified point and optionally returns the previous position.
			void MoveToEx(int x, int y, WMFConverter::Point* old);

			  /// Moves the clipping region of a device context by the specified offsets.
			void OffsetClipRgn(int x, int y);

			  /// Modifies the viewport origin for a device context using the specified horizontal and vertical offsets.
			void OffsetViewportOrgEx(int x, int y, WMFConverter::Point* point);

			  /// Modifies the window origin for a device context using the specified horizontal and vertical offsets.
			void OffsetWindowOrgEx(int x, int y, WMFConverter::Point* point);
			  /// Paints the specified region by using the brush currently selected into the device context.
			void PaintRgn(IGdiRegion* rgn);

			  /// TODO
			void PatBlt(int x, int y, int width, int height, long rop);

			  /// Draws a pie-shaped wedge bounded by the intersection of an ellipse and two radials. 
			  /// The pie is outlined by using the current pen and filled by using the current brush.
			void Pie(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya);

			  /// Draws a polygon consisting of two or more vertices connected by straight lines. 
			  /// The polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode.
			void Polygon(vector< WMFConverter::Point*> points);

			  /// Element is an SVG basic shape that creates straight lines connecting several points. 
			  /// Typically a polyline is used to create open shapes as the last point doesn't have to be connected to the first point. 
			void Polyline(vector<WMFConverter::Point*> points);

			  ///  Draws a series of closed polygons. 
			  ///  Each polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode. 
			  ///  The polygons drawn by this function can overlap.
			void PolyPolygon(vector< WMFConverter::Point*> points, int* len);
			  /// TODO
			void RealizePalette();

			  /// Restores a device context (DC) to the specified state. 
			  /// The DC is restored by popping state information off a stack created by earlier calls to the SaveDC function.
			void RestoreDC(int savedDC);

			  /// Draws a rectangle. 
			  /// The rectangle is outlined by using the current pen and filled by using the current brush.
			void Rectangle(int sx, int sy, int ex, int ey);

			  /// TODO
			void ResizePalette(IGdiPalette *palette);

			  /// Draws a rectangle with rounded corners. 
			  /// The rectangle is outlined by using the current pen and filled by using the current brush.
			void RoundRect(int sx, int sy, int ex, int ey, int rw, int rh);

			  /// Save device context (DC).
			void SeveDC();

			  /// Modifies the viewport for a device context using the ratios formed by the specified multiplicands and divisors.
			void ScaleViewportExtEx(int x, int xd, int y, int yd, WMFConverter::Size* old);

			  /// Modifies the window for a device context using the ratios formed by the specified multiplicands and divisors.
			void ScaleWindowExtEx(int x, int xd, int y, int yd, WMFConverter::Size* old);
			  /// Selects a region as the current clipping region for the specified device context.
			void SelectClipRgn(IGdiRegion* rgn);

			  /// Selects an object into the specified device context (DC). The new object replaces the previous object of the same type.
			void SelectObject(WMFConverter::IGdiObject *obj);
			void SelectObject(WMFConverter::IGdiObject *obj, string);

			  /// TODO
			void SelectPalette(IGdiPalette *palette, bool mode);

			  /// Sets the current background color to the specified color value, or to the nearest physical color if the device cannot represent the specified color value.
			void SetBkColor(int color);

			  /// Sets the background mix mode of the specified device context. 
			  /// The background mix mode is used with text, hatched brushes, and pen styles that are not solid lines.
			void SetBkMode(int mode);

			  /// Sets the pixels in the specified rectangle on the device that is associated with the destination device context using color data from a DIB, JPEG, or PNG image.
			void SetDIBitsToDevice(int dx, int dy, int dw, int dh, int sx, int sy, int startscan, int scanlines, char* image, int colorUse);

			  /// Changes the layout of a device context (DC).
			void SetLayout(long layout);

			  /// Sets the mapping mode of the specified device context. 
			  /// The mapping mode defines the unit of measure used to transform page-space units into device-space units, and also defines the orientation of the device's x and y axes.
			void SetMapMode(int mode);

			  /// Alters the algorithm the font mapper uses when it maps logical fonts to physical fonts.
			void SetMapperFlags(long flags);

			  /// TODO
			void SetPaletteEntries(IGdiPalette* palette, int startIndex, int* entries);

			  /// Sets the pixel at the specified coordinates to the specified color.
			void SetPixel(int x, int y, int color);

			  /// Sets the polygon fill mode for functions that fill polygons.
			void SetPolyFillMode(int mode);

			void SetRelAbs(int mode);

			  /// Sets the current foreground mix mode. 
			  /// GDI uses the foreground mix mode to combine pens and interiors of filled objects with the colors already on the screen. 
			  /// The foreground mix mode defines how colors from the brush or pen and the colors in the existing image are to be combined.
			void SetROP2(int mode);

			  /// Sets the bitmap stretching mode in the specified device context.
			void SetStretchBltMode(int mode);

			  /// Sets the text-alignment flags for the specified device context.
			void SetTextAlign(int align);

			  /// Sets the intercharacter spacing. 
			  /// Intercharacter spacing is added to each character, including break characters, when the system writes a line of text.
			void SetTextCharacterExtra(int extra);

			  /// Sets the text color for the specified device context to the specified color.
			void SetTextColor(int color);

			  /// Specifies the amount of space the system should add to the break characters in a string of text. 
			  /// The space is added when an application calls the TextOut or ExtTextOut functions.
			void SetTextJustification(int breakExtra, int breakCount);

			  /// Sets the horizontal and vertical extents of the viewport for a device context by using the specified values.
			void SetViewportExtEx(int x, int y, WMFConverter::Size* old);

			  /// Specifies which device point maps to the window origin (0,0).
			void SetViewportOrgEx(int x, int y, WMFConverter::Point* old);

			  /// Sets the horizontal and vertical extents of the window for a device context by using the specified values.
			void SetWindowExtEx(int width, int height, WMFConverter::Size *old);

			  /// Specifies which window point maps to the viewport origin (0,0).
			void SetWindowOrgEx(int x, int y, WMFConverter::Point* old);

			  /// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			  /// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
			void StretchBlt(char* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, long rop);

			  /// Copies the color data for a rectangle of pixels in a DIB, JPEG, or PNG image to the specified destination rectangle. 
			  /// If the destination rectangle is larger than the source rectangle, this function stretches the rows and columns of color data to fit the destination rectangle. If the destination rectangle is smaller than the source rectangle, this function compresses the rows and columns by using the specified raster operation.
			void StretchDIBits(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, char* image, int usage, long rop);

			  /// Writes a character string at the specified location, using the currently selected font, background color, and text color.
			void TextOut(int x, int y, char* text);

			void Footer();
				/// SVG Document - XML
			tinyxml2::XMLDocument *Document();
			tinyxml2::XMLElement *DefsElement();

				/// Style node element.
			tinyxml2::XMLElement *StyleElement();

				/// IE9-compatible style output
			bool Compatible();
			void SetCompatible(bool val);

			bool ReplaceSymbolFont();
			void SetReplaceSymbolFont(bool val);

			SvgDc* DC();



		private:


			string getClassString(WMFConverter::IGdiObject* obj1, WMFConverter::IGdiObject* obj2);

			/// Get class name.
			string GetClassString(WMFConverter::IGdiObject *style);

			/// Append specified string to specified element.
			void AppendText(tinyxml2::XMLElement* elem, string str);



			/// Convert BMP to SVG.
			void bmpToSvg(char* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, int usage, long rop);

			/// Convert Dib to BMP.
			char* dibToBmp(char* dib);

			/// Init Document.
			void init();

			void initialPrivateData();

			bool _compatible;
			bool _replaceSymbolFont;
			Properties *_props;
			SvgDc* _dc;
			
			vector<SvgDc*> _saveDC;
		
			tinyxml2::XMLDocument* _doc ;
			tinyxml2::XMLElement* _parentNode ;
			tinyxml2::XMLElement* _styleNode ;
			tinyxml2::XMLElement *_defsNode;

			int _brushNo;
			int _fontNo;
			int _penNo;
			int _patternNo;
			int _rgnNo;
			int _clipPathNo;
			int _maskNo;

			map<WMFConverter::IGdiObject*, string> _nameMap;
			std::string _buffer;
			SvgBrush* _defaultBrush;
			SvgPen* _defaultPen;
			SvgFont* _defaultFont;

		};
}



#endif