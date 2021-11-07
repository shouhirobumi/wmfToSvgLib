#ifndef _IGDI_H_
#define _IGDI_H_

#include "IGdiPalette.h"
#include "IGdiPatternBrush.h"
#include "IGdiBrush.h"
#include "IGdiPen.h"
#include "IGdiFont.h"
#include "IGdiRegion.h"
#include "Point.h"
#include "Size.h"
#include <vector>

namespace WMFConverter{

		class IGdi{

		public:

			/// Create header document.
			virtual void PlaceableHeader(int vsx, int vsy, int vex, int vey, int dpi){};

			/// Initialize Header document.
			virtual void Header(){};

			/// Element is put inside a shape element and defines how an attribute of an element changes over the animation. 
			/// The attribute will change from the initial value to the end value in the duration specified.
			virtual void AnimatePalette(IGdiPalette* palette, int startIndex, int* entries){};

			/// Draws an elliptical arc.
			virtual void Arc(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya){};

			/// Execute a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
			virtual void BitBlt(char* image, int dx, int dy, int dw, int dh, int sx, int sy, long rop){};

			/// Draws a chord (a region bounded by the intersection of an ellipse and a line segment, called a secant).
			/// The chord is outlined by using the current pen and filled by using the current brush.
			virtual void Chord(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya){};

			/// Creates a logical brush that has the specified style, color, and pattern.
			virtual IGdiBrush* CreateBrushIndirect(int style, int color, int hatch){
				return NULL;
			};

			/// Creates a logical font that has the specified characteristics. 
			/// The font can subsequently be selected as the current font for any device context.
			virtual IGdiFont* CreateFontIndirect(int height, int width, int escapement,
				int orientation, int weight,
				bool italic, bool underline, bool strikeout,
				int charset, int outPrecision, int clipPrecision,
				int quality, int pitchAndFamily, char* faceName){
				return NULL;
			};

			/// Creates a logical palette.
			virtual IGdiPalette* CreatePalette(int version, int* palEntry){
				return NULL;
			};

			/// Creates a logical brush with the specified bitmap pattern.
			/// The bitmap can be a DIB section bitmap, which is created by the CreateDIBSection function, or it can be a device-dependent bitmap.
			virtual IGdiPatternBrush *CreatePatternBrush(char* image){
				return NULL;
			};

			/// Creates a logical cosmetic pen that has the style, width, and color specified in a structure.
			virtual IGdiPen* CreatePenIndirect(int style, int width, int color){
				return NULL;
			};

			/// Creates a rectangular region.
			virtual IGdiRegion* CreateRectRgn(int left, int top, int right, int bottom){
				return NULL;
			};

			/// Deletes a logical pen, brush, font, bitmap, region, or palette, freeing all system resources associated with the object. 
			/// After the object is deleted, the specified handle is no longer valid.
			virtual void DeleteObject(IGdiObject* obj){};

			/// Function performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
			virtual void DibBitBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, long rop){};

			/// Create Dib Pattern Brush object instance.
			virtual IGdiPatternBrush* DibCreatePatternBrush(char* image, int usage){
				return NULL;
			};

			/// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			/// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
			virtual void DibStretchBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, int sw, int sh, long rop){};

			/// Draws an ellipse. 
			/// The center of the ellipse is the center of the specified bounding rectangle.
			/// The ellipse is outlined by using the current pen and is filled by using the current brush.
			virtual void Ellipse(int sx, int sy, int ex, int ey){};

			/// Enables an application to access the system-defined device capabilities that are not available through GDI. 
			/// Escape calls made by an application are translated and sent to the driver.
			virtual void Escape(char* data){};

			///  Creates a new clipping region that consists of the existing clipping region minus the specified rectangle.
			virtual int ExcludeClipRect(int left, int top, int right, int bottom){
				return 0;
			};

			/// Fills an area of the display surface with the current brush.
			virtual void ExtFloodFill(int x, int y, int color, int type){};

			/// Draws text using the currently selected font, background color, and text color. 
			/// You can optionally provide dimensions to be used for clipping, opaquing, or both.
			virtual void ExtTextOut(int x, int y, int options, int* rect, char* text, int* lpdx){};

			/// Fills a region by using the specified brush.
			virtual void FillRgn(IGdiRegion *rgn, IGdiBrush *brush){};

			/// Fills an area of the display surface with the current brush. 
			/// The area is assumed to be bounded as specified by the crFill parameter.
			virtual void FloodFill(int x, int y, int color){};

			/// Draws a border around the specified region by using the specified brush.
			virtual void FrameRgn(IGdiRegion* rgn, IGdiBrush* brush, int w, int h){};

			/// Creates a new clipping region from the intersection of the current clipping region and the specified rectangle.
			virtual void IntersectClipRect(int left, int top, int right, int bottom){};

			/// Inverts the colors in the specified region.
			virtual void InvertRgn(IGdiRegion* rgn){};

			/// Draws a line from the current position up to, but not including, the specified point.
			virtual void LineTo(int ex, int ey){};

			/// Updates the current position to the specified point and optionally returns the previous position.
			virtual void MoveToEx(int x, int y, Point* old){};

			/// Moves the clipping region of a device context by the specified offsets.
			virtual void OffsetClipRgn(int x, int y){};

			/// Modifies the viewport origin for a device context using the specified horizontal and vertical offsets.
			virtual void OffsetViewportOrgEx(int x, int y, Point* point){};

			/// Modifies the window origin for a device context using the specified horizontal and vertical offsets.
			virtual void OffsetWindowOrgEx(int x, int y, Point* point){};

			/// Paints the specified region by using the brush currently selected into the device context.
			virtual void PaintRgn(IGdiRegion *rgn){};

			/// Paints the specified rectangle using the brush that is currently selected into the specified device context.
			/// The brush color and the surface color or colors are combined by using the specified raster operation.
			virtual void PatBlt(int x, int y, int width, int height, long rop){};

			/// Draws a pie-shaped wedge bounded by the intersection of an ellipse and two radials. 
			/// The pie is outlined by using the current pen and filled by using the current brush.
			virtual void Pie(int sx, int sy, int ex, int ey, int sxr, int syr, int exr, int eyr){};

			/// Draws a polygon consisting of two or more vertices connected by straight lines. 
			/// The polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode.
			//virtual void Polygon(Point* points){};
			virtual void Polygon(vector<Point*> points){};
			/// Element is an SVG basic shape that creates straight lines connecting several points. 
			/// Typically a polyline is used to create open shapes as the last point doesn't have to be connected to the first point. 
			//virtual void Polyline(Point* points){};
			virtual void Polyline(vector<Point*> points){};

			///  Draws a series of closed polygons. 
			///  Each polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode. 
			///  The polygons drawn by this function can overlap.
			virtual void PolyPolygon(vector<Point*> points, int *){};

			/// Maps palette entries from the current logical palette to the system palette.
			virtual void RealizePalette(){};

			/// Restores a device context (DC) to the specified state. 
			/// The DC is restored by popping state information off a stack created by earlier calls to the SaveDC function.
			virtual void RestoreDC(int savedDC){};

			/// Draws a rectangle. 
			/// The rectangle is outlined by using the current pen and filled by using the current brush.
			virtual void Rectangle(int sx, int sy, int ex, int ey){};

			/// Increases or decreases the size of a logical palette based on the specified value.
			virtual void ResizePalette(IGdiPalette* palette){};

			/// Draws a rectangle with rounded corners. 
			/// The rectangle is outlined by using the current pen and filled by using the current brush.
			virtual void RoundRect(int sx, int sy, int ex, int ey, int rw, int rh){};

			/// Save device context (DC).
			virtual void SeveDC(){};

			/// Modifies the viewport for a device context using the ratios formed by the specified multiplicands and divisors.
			virtual void ScaleViewportExtEx(int x, int xd, int y, int yd, Size* old){};

			/// Modifies the window for a device context using the ratios formed by the specified multiplicands and divisors.
			virtual void ScaleWindowExtEx(int x, int xd, int y, int yd, Size *old){};


			/// Selects a region as the current clipping region for the specified device context.
			virtual void SelectClipRgn(IGdiRegion *rgn){};

			/// Selects an object into the specified device context (DC). The new object replaces the previous object of the same type.
			virtual void SelectObject(IGdiObject *obj){};
			virtual void SelectObject(IGdiObject *obj, string){};

			/// Selects the specified logical palette into a device context.
			virtual void SelectPalette(IGdiPalette* palette, bool mode){};

			/// Sets the current background color to the specified color value, or to the nearest physical color if the device cannot represent the specified color value.
			virtual void SetBkColor(int color){};

			/// Sets the background mix mode of the specified device context. 
			/// The background mix mode is used with text, hatched brushes, and pen styles that are not solid lines.
			virtual void SetBkMode(int mode){};

			/// Sets the pixels in the specified rectangle on the device that is associated with the destination device context using color data from a DIB, JPEG, or PNG image.
			virtual void SetDIBitsToDevice(int dx, int dy, int dw, int dh, int sx, int sy,
				int startscan, int scanlines, char* image, int colorUse){};

			/// Changes the layout of a device context (DC).
			virtual void SetLayout(long layout){};

			/// Sets the mapping mode of the specified device context. 
			/// The mapping mode defines the unit of measure used to transform page-space units into device-space units, and also defines the orientation of the device's x and y axes.
			virtual void SetMapMode(int mode){};

			/// Alters the algorithm the font mapper uses when it maps logical fonts to physical fonts.
			virtual void SetMapperFlags(long flags){};

			/// Sets RGB (red, green, blue) color values and flags in a range of entries in a logical palette.
			virtual void SetPaletteEntries(IGdiPalette *palette, int startIndex, int* entries){};

			/// Sets the pixel at the specified coordinates to the specified color.
			virtual void SetPixel(int x, int y, int color){};

			/// Sets the polygon fill mode for functions that fill polygons.
			virtual void SetPolyFillMode(int mode){};

			virtual void SetRelAbs(int mode){};

			/// Sets the current foreground mix mode. 
			/// GDI uses the foreground mix mode to combine pens and interiors of filled objects with the colors already on the screen. 
			/// The foreground mix mode defines how colors from the brush or pen and the colors in the existing image are to be combined.
			virtual void SetROP2(int mode){};

			/// Sets the bitmap stretching mode in the specified device context.
			virtual void SetStretchBltMode(int mode){};

			/// Sets the text-alignment flags for the specified device context.
			virtual void SetTextAlign(int align){};

			/// Sets the intercharacter spacing. 
			/// Intercharacter spacing is added to each character, including break characters, when the system writes a line of text.
			virtual void SetTextCharacterExtra(int extra){};

			/// Sets the text color for the specified device context to the specified color.
			virtual void SetTextColor(int color){};

			/// Specifies the amount of space the system should add to the break characters in a string of text. 
			/// The space is added when an application calls the TextOut or ExtTextOut functions.
			virtual void SetTextJustification(int breakExtra, int breakCount){};

			/// Sets the horizontal and vertical extents of the viewport for a device context by using the specified values.
			virtual void SetViewportExtEx(int x, int y, Size *old){};

			/// Specifies which device point maps to the window origin (0,0).
			virtual void SetViewportOrgEx(int x, int y, Point* old){};

			/// Sets the horizontal and vertical extents of the window for a device context by using the specified values.
			virtual void SetWindowExtEx(int width, int height, Size* old){};

			/// Specifies which window point maps to the viewport origin (0,0).
			virtual void SetWindowOrgEx(int x, int y, Point* old){};

			/// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			/// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
			virtual void StretchBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, int sw, int sh, long rop){};


			/// Copies the color data for a rectangle of pixels in a DIB, JPEG, or PNG image to the specified destination rectangle. 
			/// If the destination rectangle is larger than the source rectangle, this function stretches the rows and columns of color data to fit the destination rectangle. If the destination rectangle is smaller than the source rectangle, this function compresses the rows and columns by using the specified raster operation.
			virtual void StretchDIBits(int dx, int dy, int dw, int dh,
				int sx, int sy, int sw, int sh,
				char* image, int usage, long rop){};


			/// Writes a character string at the specified location, using the currently selected font, background color, and text color.
			virtual void TextOut(int x, int y, char* text){};

			virtual void Footer(){};
		};
}

#endif