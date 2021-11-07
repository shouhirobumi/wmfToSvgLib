#include "SvgGdi.h"

#include "Properties.h"
#include "SvgDc.h"
#include "SvgPen.h"
#include "SvgBrush.h"
#include "SvgFont.h"
#include "SvgPalette.h"
#include "SvgRectRegion.h"
#include "SvgPatternBrush.h"
#include <stdlib.h>

namespace WMFConverter{

		SvgGdi::SvgGdi()
			{
				SvgGdi(false);
				//initialPrivateData();
			}

		SvgGdi::SvgGdi(bool compatible)
			{
				initialPrivateData();
				_compatible = compatible;

				_doc = new tinyxml2::XMLDocument();

				string data = "xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"";
				tinyxml2::XMLDeclaration* declaration = _doc->NewDeclaration(data.c_str());
				_doc->InsertFirstChild(declaration);

		//data = "<!DOCTYPE svg PUBLIC \" -\/\/W3C\/\/DTD SVG 1.0\/\/EN\" \"\">";
		//tinyxml2::XMLDeclaration* doctype = _doc->NewDeclaration(data.c_str());
		////auto doctype = _doc->NewDeclaration("svg", "-//W3C//DTD SVG 1.0//EN", "", NULL);
		//_doc->InsertEndChild(doctype);

//				tinyxml2::XMLElement* svg = _doc->NewElement("svg http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* svg = _doc->NewElement("svg");
				_doc->InsertEndChild(svg);
				_props->load();
			}

		void SvgGdi::Write(string file)
			{
				_doc->SaveFile(file.c_str());
			}

			/// Write SVG XML document.
		void SvgGdi::Write(FILE* output)
			{
				//TODO
				// 生成一个XmlWriterSettings实例，设置参数为 Indent = true,				NamespaceHandling = System.Xml.NamespaceHandling.OmitDuplicates

				//_doc->SaveFile("e://bbb.svg");
				_doc->SaveFile(output);
				
				
		/*		var writer = System.Xml.XmlWriter.Create(output, new System.Xml.XmlWriterSettings
				{
					Indent = true,
					NamespaceHandling = System.Xml.NamespaceHandling.OmitDuplicates
				});
				_doc.Save(writer);

				writer.Flush();*/
			}

			/// Get property value using key value.
		string SvgGdi::GetProperty(string key)
			{
				string outstring = "";
				//_props.TryGetValue(key, out outstring);
				outstring = _props->findVal(key);
				return outstring;
			}
			/// Define header document.
		void SvgGdi::PlaceableHeader(int wsx, int wsy, int wex, int wey, int dpi)
			{
				if (_parentNode == NULL)
					init();

				_dc->SetWindowExtEx(abs(wex - wsx), abs(wey - wsy), NULL);
				_dc->SetDpi(dpi);

				tinyxml2::XMLElement* root = _doc->RootElement();	//文档树的跟document

				double doubledpi = (double)_dc->Dpi();

				string data = doubleToString(abs((double)1.00 * (wex - wsx)) / doubledpi) + "in";
				root->SetAttribute("width", data.c_str());
				data = doubleToString(abs((double)(wey - wsy)) / (double)_dc->Dpi()) + "in";
				root->SetAttribute("height", data.c_str());
			}

			/// Initialize header document.
		void SvgGdi::Header()
			{
				if (_parentNode == NULL)
					this->init();
			}

			/// Replaces entries in the specified logical palette.
		void SvgGdi::AnimatePalette(IGdiPalette *palette, int startIndex, int* entries)
			{
				// TODO
				printf("not implemented: animatePalette");
			}

			/// Draws an elliptical arc.
		void SvgGdi::Arc(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya)
			{
				double rx = abs(exr - sxr) / 2.0;
				double ry = abs(eyr - syr) / 2.0;
				if (rx <= 0 || ry <= 0)
					return;

				double cx = min(sxr, exr) + rx;
				double cy = min(syr, eyr) + ry;

				tinyxml2::XMLElement* elem = NULL;
				if (sxa == exa && sya == eya)
				{
					if (rx == ry)
					{
//						elem = _doc->NewElement("circle http://www.w3.org/2000/svg");
						elem = _doc->NewElement("circle");
						elem->SetAttribute("cx", doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("r", doubleToString(_dc->ToRelativeX(rx)).c_str());
					}
					else
					{
//						elem = _doc->NewElement("ellipse http://www.w3.org/2000/svg");
						elem = _doc->NewElement("ellipse");
						elem->SetAttribute("cx", doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("rx", doubleToString(_dc->ToRelativeX(rx)).c_str());
						elem->SetAttribute("ry", doubleToString(_dc->ToRelativeY(ry)).c_str());
					}
				}
				else
				{
					double sa = atan2((sya - cy) * rx, (sxa - cx) * ry);
					double sx = rx * cos(sa);
					double sy = ry * sin(sa);

					double ea = atan2((eya - cy) * rx, (exa - cx) * ry);
					double ex = rx * cos(ea);
					double ey = ry * sin(ea);

					double a = atan2((ex - sx) * (-sy) - (ey - sy) * (-sx), (ex - sx) * (-sx) + (ey - sy) * (-sy));

					elem = _doc->NewElement("path");
					string data = "M " + doubleToString(_dc->ToAbsoluteX(sx + cx)) + "," + doubleToString(_dc->ToAbsoluteY(sy + cy))
						+ " A " + doubleToString(_dc->ToRelativeX(rx)) + "," + doubleToString(_dc->ToRelativeY(ry))
						+ " 0 " + (a > 0 ? "1" : "0") + " 0"
						+ " " + doubleToString(_dc->ToAbsoluteX(ex + cx)) + "," + doubleToString(_dc->ToAbsoluteY(ey + cy));
					elem->SetAttribute("d", data.c_str());
				}

				if (_dc->Pen() != NULL)
					elem->SetAttribute("class", this->GetClassString(_dc->Pen()).c_str());

				elem->SetAttribute("fill", "none");
				_parentNode->InsertEndChild(elem);
			}

			/// Execute a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
		void SvgGdi::BitBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, long rop)
			{
				this->bmpToSvg(image, dx, dy, dw, dh, sx, sy, dw, dh, (int)BrushDIBColorsEnum::DIB_RGB_COLORS, rop);
			}

			/// Draws a chord (a region bounded by the intersection of an ellipse and a line segment, called a secant).
			/// The chord is outlined by using the current pen and filled by using the current brush.
		void SvgGdi::Chord(int sxr, int syr, int exr, int eyr, int sxa, int sya,
				int exa, int eya)
			{
				double rx = abs(exr - sxr) / 2.0;
				double ry = abs(eyr - syr) / 2.0;
				if (rx <= 0 || ry <= 0) return;

				double cx = min(sxr, exr) + rx;
				double cy = min(syr, eyr) + ry;

				tinyxml2::XMLElement *elem = NULL;
				if (sxa == exa && sya == eya)
				{
					if (rx == ry)
					{
//						elem = _doc->NewElement("circle http://www.w3.org/2000/svg");
						elem = _doc->NewElement("circle");
						elem->SetAttribute("cx", doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("r", doubleToString(_dc->ToRelativeX(rx)).c_str());
					}
					else
					{
//						elem = _doc->NewElement("ellipse http://www.w3.org/2000/svg");
						elem = _doc->NewElement("ellipse");
						elem->SetAttribute("cx", doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("rx", doubleToString(_dc->ToRelativeX(rx)).c_str());
						elem->SetAttribute("ry", doubleToString(_dc->ToRelativeY(ry)).c_str());
					}
				}
				else
				{
					double sa = atan2((sya - cy) * rx, (sxa - cx) * ry);
					double sx = rx * cos(sa);
					double sy = ry * sin(sa);

					double ea = atan2((eya - cy) * rx, (exa - cx) * ry);
					double ex = rx * cos(ea);
					double ey = ry * sin(ea);

					double a = atan2((ex - sx) * (-sy) - (ey - sy) * (-sx), (ex - sx) * (-sx) + (ey - sy) * (-sy));

//					elem = _doc->NewElement("path http://www.w3.org/2000/svg");
					elem = _doc->NewElement("path");
					string data = "M " + doubleToString(_dc->ToAbsoluteX(sx + cx)) + "," + doubleToString(_dc->ToAbsoluteY(sy + cy))
						+ " A " + doubleToString(_dc->ToRelativeX(rx)) + "," + doubleToString(_dc->ToRelativeY(ry))
						+ " 0 " + (a > 0 ? "1" : "0") + " 0"
						+ " " + doubleToString(_dc->ToAbsoluteX(ex + cx)) + "," + doubleToString(_dc->ToAbsoluteY(ey + cy)) + " Z";
					elem->SetAttribute("d",data.c_str());
				}

				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", this->getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill", id.c_str() );
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
				}

				_parentNode->InsertEndChild(elem);
			}

			/// Creates a logical brush that has the specified style, color, and pattern.
		WMFConverter::IGdiBrush* SvgGdi::CreateBrushIndirect(int style, int color, int hatch)
			{
				SvgBrush *brush = new SvgBrush(this, style, color, hatch);


				bool fCanFindSame = false;

				map <WMFConverter::IGdiObject*, string >::iterator iter;
				iter = _nameMap.begin();
				while (iter != _nameMap.end()) {
					string dataType = iter->second;
					if ((dataType[0] == 'b') &&
						(dataType[1] == 'r') &&
						(dataType[2] == 'u'))
					{
						SvgBrush* temp = (SvgBrush*)(iter->first);
						if (temp->ToString() == brush->ToString())
						{
							// 判断为已存在的对象
							fCanFindSame = true;
							brush = (SvgBrush *)iter->first;
							break;
						}
						else
						{
							fCanFindSame = false;
						}
					}
					iter++;
				}

				if (!fCanFindSame)
				{
					string name = "brush" + intToString(_brushNo++);
					_nameMap.insert(make_pair((IGdiObject*)brush, name));
					_styleNode->InsertEndChild(brush->NewText(name));
				}

				return brush;
			}

			/// Creates a logical font that has the specified characteristics. 
			/// The font can subsequently be selected as the current font for any device context.
		WMFConverter::IGdiFont* SvgGdi::CreateFontIndirect(int height, int width, int escapement,
				int orientation, int weight, bool italic, bool underline,
				bool strikeout, int charset, int outPrecision,
				int clipPrecision, int quality, int pitchAndFamily, char* faceName)
			{
				SvgFont *font = new SvgFont(this, height, width, escapement,
					orientation, weight, italic, underline, strikeout, charset,
					outPrecision, clipPrecision, quality, pitchAndFamily, faceName);

				bool fCanFindSame = false;

				map <WMFConverter::IGdiObject*, string >::iterator iter;
				iter = _nameMap.begin();
				while (iter != _nameMap.end()) {
					string dataType = iter->second;
					if ((dataType[0] == 'f') &&
						(dataType[1] == 'o') &&
						(dataType[2] == 'n'))
					{
						SvgFont* temp = (SvgFont*)(iter->first);
						if (temp->ToString() == font->ToString())
						{
							// 判断为已存在的对象
							fCanFindSame = true;
							font = (SvgFont *)iter->first;
							break;
						}
						else
						{
							fCanFindSame = false;
						}
					}
					iter++;
				}

				if (!fCanFindSame)
				{
					string name = "font" + intToString(_fontNo++);
					_nameMap.insert(make_pair((IGdiObject*)font, name));
					_styleNode->InsertEndChild(font->NewText(name));
				}

				return font;
			}
			/// Creates a logical palette.

		WMFConverter::IGdiPalette* SvgGdi::CreatePalette(int version, int* entries)
			{
				return (new SvgPalette(this, version, entries));
			}

			/// Creates a logical brush with the specified bitmap pattern.
			/// The bitmap can be a DIB section bitmap, which is created by the CreateDIBSection function, or it can be a device-dependent bitmap.
		WMFConverter::IGdiPatternBrush* SvgGdi::CreatePatternBrush(char* image)
			{
				return new SvgPatternBrush(this, image);
			}

			/// Creates a logical cosmetic pen that has the style, width, and color specified in a structure.
		WMFConverter::IGdiPen* SvgGdi::CreatePenIndirect(int style, int width, int color)
			{
				SvgPen *pen = new SvgPen(this, style, width, color);

				bool fCanFindSame = false;

				map <WMFConverter::IGdiObject*, string >::iterator iter;
				iter = _nameMap.begin();
				while (iter != _nameMap.end()) {
					string dataType = iter->second;
					if ((dataType[0] == 'p') &&
						(dataType[1] == 'e') &&
						(dataType[2] == 'n'))
					{
						SvgPen* temp = (SvgPen*)(iter->first);
						if (temp->ToString() == pen->ToString())
		/*				if ((temp->Color() == color) &&
							(temp->Width() == width) &&
							(temp->Style() == style))*/
						{
							// 判断为已存在的对象
							fCanFindSame = true;
							pen = (SvgPen *)iter->first;
							break;
						}
						else
						{
							fCanFindSame = false;
						}
					}
					iter++;
				}

				if (!fCanFindSame)
				{
					//pen = new SvgPen(this, style, width, color);
					string name = "pen" + intToString(_penNo++);
					_nameMap.insert(make_pair((IGdiObject*)pen, name));
					_styleNode->InsertEndChild(pen->NewText(name));
				}

				//if (_nameMap.find((IGdiObject*)pen) == _nameMap.end())
				//{
				//	string name = "pen" + intToString(_penNo++);
				//	//_nameMap.insert(std::pair<WMFConverter::IGdiObject*, string>((IGdiObject*)pen, name));
				//	_nameMap.insert(make_pair((IGdiObject*)pen, name));


				//	_styleNode->InsertEndChild(pen->NewText(name));
				//}
				return pen;
			}

			/// Creates a rectangular region.
		WMFConverter::IGdiRegion* SvgGdi::CreateRectRgn(int left, int top, int right, int bottom)
			{
				SvgRectRegion* rgn = new SvgRectRegion(this, left, top, right, bottom);
				if (_nameMap.find((IGdiObject*)rgn) == _nameMap.end())
				{
					string name = "rgn" + intToString(_rgnNo++);
					//_nameMap.insert(std::pair<WMFConverter::IGdiObject*, string>((IGdiObject*)rgn, name));
					_nameMap.insert(make_pair((IGdiObject*)rgn, name));


					_defsNode->InsertEndChild(rgn->CreateElement());
				}
				return rgn;
			}
			/// Deletes a logical pen, brush, font, bitmap, region, or palette, freeing all system resources associated with the object. 
			/// After the object is deleted, the specified handle is no longer valid.

		void SvgGdi::DeleteObject(WMFConverter::IGdiObject *obj)
			{
				if (_dc->Brush() == obj)
					_dc->SetBrush(_defaultBrush);
				else if (_dc->Font() == obj)
					_dc->SetFont(_defaultFont);
				else if (_dc->Pen() == obj)
					_dc->SetPen(_defaultPen);
			}
			/// Function performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
		void SvgGdi::DibBitBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, long rop)
			{
				this->BitBlt(image, dx, dy, dw, dh, sx, sy, rop);
			}
			/// Create Dib Pattern Brush object instance.
		WMFConverter::IGdiPatternBrush* SvgGdi::DibCreatePatternBrush(char* image, int usage)
			{
				// TODO usage
				return (SvgPatternBrush*)(new SvgPatternBrush(this, image));
			}
			/// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			/// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
		void SvgGdi::DibStretchBlt(char* image, int dx, int dy, int dw, int dh,
				int sx, int sy, int sw, int sh, long rop)
			{
				StretchDIBits(dx, dy, dw, dh, sx, sy, sw, sh, image, (int)BrushDIBColorsEnum::DIB_RGB_COLORS, rop);
			}
			/// Draws an ellipse. 
			/// The center of the ellipse is the center of the specified bounding rectangle.
			/// The ellipse is outlined by using the current pen and is filled by using the current brush.
		void SvgGdi::Ellipse(int sx, int sy, int ex, int ey)
			{
//				tinyxml2::XMLElement *elem = _doc->NewElement("ellipse http://www.w3.org/2000/svg");
				tinyxml2::XMLElement *elem = _doc->NewElement("ellipse");

				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", this->getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString((_patternNo++)) + ")";
						elem->SetAttribute("fill", id.c_str() );
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
				}

				elem->SetAttribute("cx", intToString((int)_dc->ToAbsoluteX((sx + ex) / 2)).c_str());
				elem->SetAttribute("cy", intToString((int)_dc->ToAbsoluteY((sy + ey) / 2)).c_str());
				elem->SetAttribute("rx", intToString((int)_dc->ToRelativeX((ex - sx) / 2)).c_str());
				elem->SetAttribute("ry", intToString((int)_dc->ToRelativeY((ey - sy) / 2)).c_str());
				_parentNode->InsertEndChild(elem);
			}
			/// TODO
		void SvgGdi::Escape(char* data)
			{

			}
			///  Creates a new clipping region that consists of the existing clipping region minus the specified rectangle.
		int SvgGdi::ExcludeClipRect(int left, int top, int right, int bottom)
			{
				tinyxml2::XMLElement* mask = _dc->Mask();
				if (mask != NULL)
				{
					mask = (tinyxml2::XMLElement*)mask->DeepClone(NULL);
					string name = "mask" + intToString((_maskNo++));
					mask->SetAttribute("id", name.c_str());
					_defsNode->InsertEndChild(mask);

//					tinyxml2::XMLElement* unclip = _doc->NewElement("rect http://www.w3.org/2000/svg");
					tinyxml2::XMLElement* unclip = _doc->NewElement("rect");
					unclip->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(left)).c_str());
					unclip->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(top)).c_str());
					unclip->SetAttribute("width", intToString((int)_dc->ToRelativeX(right - left)).c_str());
					unclip->SetAttribute("height", intToString((int)_dc->ToRelativeY(bottom - top)).c_str());
					unclip->SetAttribute("fill", "black");
					mask->InsertEndChild(unclip);
					_dc->SetMask(mask);

					// TODO
					return (int)RegionEnum::COMPLEXREGION;
				}
				else
					return (int)RegionEnum::NULLREGION;
			}
			/// TODO
		void SvgGdi::ExtFloodFill(int x, int y, int color, int type)
			{
				// TODO
				printf("not implemented: extFloodFill");
			}

			/// Draws text using the currently selected font, background color, and text color. 
			/// You can optionally provide dimensions to be used for clipping, opaquing, or both.
		void SvgGdi::ExtTextOut(int x, int y, int options, int* rect, char* text, int* dx)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("text http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("text");

				int escapement = 0;
				bool vertical = false;
				if (_dc->Font() != NULL)
				{
					elem->SetAttribute("class", this->GetClassString(_dc->Font()).c_str());
					if (_dc->Font()->FaceName()[0] == '@')
					{
						vertical = true;
						escapement = _dc->Font()->Escapement() - 2700;
					}
					else
						escapement = _dc->Font()->Escapement();
				}
				elem->SetAttribute("fill", SvgObject::ToColor(_dc->TextColor()).c_str());

				// style
				_buffer = "";
				int align = _dc->TextAlign();

				if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_RIGHT)
					_buffer += "text-anchor: end; ";
				else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_CENTER)
					_buffer += "text-anchor: middle; ";

				if (_compatible)
					_buffer += "dominant-baseline: alphabetic; ";
				else
				{
					if (vertical)
						elem->SetAttribute("writing-mode", "tb");
					else
					{
						if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BASELINE)
							_buffer += "dominant-baseline: alphabetic; ";
						else
							_buffer += "dominant-baseline: text-before-edge; ";
					}
				}

				if ((align & (int)GdiEnum::TA_RTLREADING) == (int)GdiEnum::TA_RTLREADING || (options & (int)GdiEnum::ETO_RTLREADING) > 0)
					_buffer += "unicode-bidi: bidi-override; direction: rtl; ";

				if (_dc->TextSpace() > 0)
				{
					_buffer += "word-spacing: " + intToString(_dc->TextSpace()) + "; ";
				}
				//if (_buffer.length() > 0)
				// _buffer.length() = _buffer.length() - 1;
				elem->SetAttribute("style", _buffer.c_str());

				elem->SetAttribute("stroke", "none");

				if ((align & ((int)GdiEnum::TA_NOUPDATECP | (int)GdiEnum::TA_UPDATECP)) == (int)GdiEnum::TA_UPDATECP)
				{
					x = _dc->CurrentX();
					y = _dc->CurrentY();
				}

				// x
				int ax = (int)_dc->ToAbsoluteX(x);
				int width = 0;
				if (vertical)
				{
					string data = intToString(ax) + ";";
					elem->SetAttribute("x", data.c_str());
					if (_dc->Font() != NULL)
						width = abs(_dc->Font()->FontSize());
				}
				else
				{
					if (_dc->Font() != NULL)
						dx = _dc->Font()->ValidateDx(text, dx);

					if (dx != NULL && dx > 0)
					{
						int dxSize = sizeof(dx) / sizeof(int);
						for (int i = 0; i < dxSize; i++)
							width += dx[i];

						int tx = x;

						if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_RIGHT)
							tx -= (width - dx[dxSize - 1]);
						else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_CENTER)
							tx -= (width - dx[dxSize - 1]) / 2;

						for (int i = 0; i < dxSize; i++)
						{
							if (i > 0)
								_buffer += " ";
							_buffer += intToString((int)_dc->ToAbsoluteX(tx));
							tx += dx[i];
						}
						if ((align & ((int)GdiEnum::TA_NOUPDATECP | (int)GdiEnum::TA_UPDATECP)) == (int)GdiEnum::TA_UPDATECP)
							_dc->MoveToEx(tx, y, NULL);
						elem->SetAttribute("x", _buffer.c_str());
					}
					else
					{
						if (_dc->Font() != NULL) width = abs((int)(_dc->Font()->FontSize() * sizeof(text))) / 2;
						elem->SetAttribute("x", intToString(ax).c_str());
					}
				}

				// y
				int ay = (int)_dc->ToAbsoluteY(y);
				int height = 0;
				if (vertical)
				{
					if (_dc->Font() != NULL)
						dx = _dc->Font()->ValidateDx(text, dx);

					//_buffer.length() = 0;
					_buffer = "";
					char text[100] = {};
					if (align == 0)
					{
						sprintf(text, "%d", ay + (int)_dc->ToRelativeY(abs(_dc->Font()->Height())));
						_buffer += string(text);
					}
					else
					{
						sprintf(text, "%d", ay);
						_buffer += text;
					}
					int dxSize = sizeof(dx) / sizeof(int);
					if (dx != NULL && dxSize > 0)
					{
						for (int i = 0; i < dxSize - 1; i++)
							height += dx[i];

						int ty = y;

						if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_RIGHT)
							ty -= (height - dx[dxSize - 1]);
						else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_CENTER | (int)GdiEnum::TA_RIGHT)) == (int)GdiEnum::TA_CENTER)
							ty -= (height - dx[dxSize - 1]) / 2;

						for (int i = 0; i < dxSize; i++)
						{
							_buffer += " ";
							char text[100] = {};
							sprintf(text, "%d", (int)_dc->ToAbsoluteY(ty));
							_buffer += string(text);
							ty += dx[i];
						}

						if ((align & ((int)GdiEnum::TA_NOUPDATECP | (int)GdiEnum::TA_UPDATECP)) == (int)GdiEnum::TA_UPDATECP)
							_dc->MoveToEx(x, ty, NULL);
					}
					else
					{
						if (_dc->Font() != NULL)
							height = abs(int(_dc->Font()->FontSize() * sizeof(text))) / 2;
					}
					elem->SetAttribute("y", _buffer.c_str());
				}
				else
				{
					if (_dc->Font() != NULL)
						height = abs(_dc->Font()->FontSize());
					if (_compatible)
					{
						if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_TOP)
						{
							elem->SetAttribute("y", intToString(ay + (int)_dc->ToRelativeY(height * 0.88)).c_str());
						}
						else if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BOTTOM)
						{
							elem->SetAttribute("y", intToString(ay + rect[3] - rect[1] + (int)_dc->ToRelativeY(height * 0.88)).c_str());
						}
						else
						{
							elem->SetAttribute("y", intToString(ay).c_str());
						}
					}
					else
					{
						if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BOTTOM && rect != NULL)
						{
							elem->SetAttribute("y", intToString((ay + rect[3] - rect[1] - (int)_dc->ToRelativeY(height))).c_str());
						}
						else
						{
							elem->SetAttribute("y", intToString(ay).c_str());
						}
					}
				}

				tinyxml2::XMLElement* bk = NULL;
				if (_dc->BkMode() == (int)GdiEnum::OPAQUE || (options & (int)GdiEnum::ETO_OPAQUE) > 0)
				{
					if (rect == NULL && _dc->Font() != NULL)
					{
						rect = (int*)malloc(4 * sizeof(int));
						if (vertical)
						{
							if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BOTTOM)
								rect[0] = x - width;
							else if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BASELINE)
								rect[0] = x - (int)(width * 0.85);
							else
								rect[0] = x;
							if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_RIGHT)
								rect[1] = y - height;
							else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_CENTER)
								rect[1] = y - height / 2;
							else
								rect[1] = y;
						}
						else
						{
							if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_RIGHT)
								rect[0] = x - width;
							else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_CENTER)
								rect[0] = x - width / 2;
							else
								rect[0] = x;
							if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BOTTOM)
								rect[1] = y - height;
							else if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BASELINE)
								rect[1] = y - (int)(height * 0.85);
							else
								rect[1] = y;
						}
						rect[2] = rect[0] + width;
						rect[3] = rect[1] + height;
					}
//					bk = _doc->NewElement("rect http://www.w3.org/2000/svg");
					bk = _doc->NewElement("rect");

					bk->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(rect[0])).c_str());
					bk->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(rect[1])).c_str());
					bk->SetAttribute("width", intToString((int)_dc->ToRelativeX(rect[2] - rect[0])).c_str());
					bk->SetAttribute("height", intToString((int)_dc->ToRelativeY(rect[3] - rect[1])).c_str());
					bk->SetAttribute("fill", SvgObject::ToColor(_dc->BkColor()).c_str());
				}

				tinyxml2::XMLElement *clip = NULL;
				if ((options & (int)GdiEnum::ETO_CLIPPED) > 0)
				{
					string name = "clipPath" + intToString(_clipPathNo++);
//					clip = _doc->NewElement("clipPath http://www.w3.org/2000/svg");
					clip = _doc->NewElement("clipPath");
					clip->SetAttribute("id", name.c_str());
					//clip.setIdAttribute("id", true);

//					tinyxml2::XMLElement* clipRect = _doc->NewElement("rect http://www.w3.org/2000/svg");
					tinyxml2::XMLElement* clipRect = _doc->NewElement("rect");
					clipRect->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(rect[0])).c_str());
					clipRect->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(rect[1])).c_str());
					clipRect->SetAttribute("width", intToString((int)_dc->ToRelativeX(rect[2] - rect[0])).c_str());
					clipRect->SetAttribute("height", intToString((int)_dc->ToRelativeX(rect[3] - rect[1])).c_str());

					clip->InsertEndChild(clipRect);
					string data = "url(#" + name + ")";
					elem->SetAttribute("clip-path", data.c_str());
				}

				string str = NULL;
				if (_dc->Font() != NULL)
					str = GdiUtils::ConvertString(text, (FontCharsetEnum)_dc->Font()->Charset());
				else
					str = GdiUtils::ConvertString(text, FontCharsetEnum::DEFAULT_CHARSET);

				if (_dc->Font() != NULL && _dc->Font()->Lang() != "")
					elem->SetAttribute("xml:lang", _dc->Font()->Lang().c_str());

				elem->SetAttribute("xml:space", "preserve");
				this->AppendText(elem, str);

				if (bk != NULL || clip != NULL)
				{
//					tinyxml2::XMLElement *g = _doc->NewElement("g http://www.w3.org/2000/svg");
					tinyxml2::XMLElement *g = _doc->NewElement("g");
					if (bk != NULL) g->InsertEndChild(bk);
					if (clip != NULL) g->InsertEndChild(clip);
					g->InsertEndChild(elem);
					elem = g;
				}

				if (escapement != 0)
				{
					string data = "rotate(" + intToString(-1 * escapement / 10.0) + ", " + intToString(ax) + ", " + intToString(ay) + ")";
					elem->SetAttribute("transform", data.c_str());
				}
				_parentNode->InsertEndChild(elem);
			}

			/// Fills a region by using the specified brush.
			void SvgGdi::FillRgn(IGdiRegion* rgn, IGdiBrush* brush)
			{
				if (rgn == NULL)
					return;

//				tinyxml2::XMLElement* elem = _doc->NewElement("use http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("use");

				string output = "";
				output = "url(#" + _nameMap[rgn] + ")";
				elem->SetAttribute("xlink:href", output.c_str());
				elem->SetAttribute("class", GetClassString(brush).c_str());
				SvgBrush* sbrush = (SvgBrush*)brush;
				if (sbrush->Style() == (int)BrushBSEnum::BS_HATCHED)
				{
					string id = "url(#pattern" + intToString(_patternNo++) + ")";
					elem->SetAttribute("fill", id.c_str() );
					_defsNode->InsertEndChild(sbrush->CreateFillPattern(id));
				}
				_parentNode->InsertEndChild(elem);
			}

			/// TODO
			void SvgGdi::FloodFill(int x, int y, int color)
			{
				// TODO
				printf("not implemented: floodFill \r\n");
			}

			/// TODO
			void SvgGdi::FrameRgn(IGdiRegion* rgn, IGdiBrush* brush, int width, int height)
			{
				// TODO
				printf("not implemented: frameRgn \r\n");
			}

			/// TODO
			void SvgGdi::IntersectClipRect(int left, int top, int right, int bottom)
			{
				// TODO
				printf("not implemented: intersectClipRect \r\n");
			}

			/// Inverts the colors in the specified region.
			void SvgGdi::InvertRgn(IGdiRegion* rgn)
			{
				if (rgn == NULL) return;

//				tinyxml2::XMLElement* elem = _doc->NewElement("use http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("use");

				string output = "";
				output = "url(#" + _nameMap[rgn] + ")";
				elem->SetAttribute("xlink:href", output.c_str());
				string ropFilter = _dc->GetRopFilter((int)GdiEnum::DSTINVERT);
				if (ropFilter != "")
					elem->SetAttribute("filter", ropFilter.c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// Draws a line from the current position up to, but not including, the specified point.
			void SvgGdi::LineTo(int ex, int ey)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("line http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("line");

				if (_dc->Pen() != NULL)
					elem->SetAttribute("class", this->GetClassString((WMFConverter::IGdiObject *)_dc->Pen()).c_str());

				elem->SetAttribute("fill", "none");

				elem->SetAttribute("x1", intToString((int)_dc->ToAbsoluteX(_dc->CurrentX())).c_str());
				elem->SetAttribute("y1", intToString((int)_dc->ToAbsoluteY(_dc->CurrentY())).c_str());
				elem->SetAttribute("x2", intToString((int)_dc->ToAbsoluteX(ex)).c_str());
				elem->SetAttribute("y2", intToString((int)_dc->ToAbsoluteY(ey)).c_str());
				_parentNode->InsertEndChild(elem);

				_dc->MoveToEx(ex, ey, NULL);
			}

			/// Updates the current position to the specified point and optionally returns the previous position.
			void SvgGdi::MoveToEx(int x, int y, WMFConverter::Point* old)
			{
				_dc->MoveToEx(x, y, old);
			}

			/// Moves the clipping region of a device context by the specified offsets.
			void SvgGdi::OffsetClipRgn(int x, int y)
			{
				_dc->OffSetClipRgn(x, y);
				tinyxml2::XMLElement* mask = _dc->Mask();
				if (mask != NULL)
				{
					mask = (tinyxml2::XMLElement*)mask->DeepClone(NULL);	// ->CloneNode(true);
					string name = "mask" + intToString(_maskNo++);
					mask->SetAttribute("id", name.c_str());
					if (_dc->OffsetClipX() != 0 || _dc->OffsetClipY() != 0)
					{
						string data = "translate(" + intToString(_dc->OffsetClipX()) + "," + intToString(_dc->OffsetClipY()) + ")";
						mask->SetAttribute("transform",data.c_str());
					}
					_defsNode->InsertEndChild(mask);

					if (!_parentNode->FirstChild())
						_doc->RootElement()->DeleteChild(_parentNode);
//					_parentNode = _doc->NewElement("g http://www.w3.org/2000/svg");
					_parentNode = _doc->NewElement("g");

					_parentNode->SetAttribute("mask", name.c_str());
					_doc->RootElement()->InsertEndChild(_parentNode);

					_dc->SetMask(mask);
				}
			}

			/// Modifies the viewport origin for a device context using the specified horizontal and vertical offsets.
			void SvgGdi::OffsetViewportOrgEx(int x, int y, WMFConverter::Point* point)
			{
				_dc->OffSetViewportOrgEx(x, y, point);
			}

			/// Modifies the window origin for a device context using the specified horizontal and vertical offsets.
			void SvgGdi::OffsetWindowOrgEx(int x, int y, WMFConverter::Point* point)
			{
				_dc->OffSetWindowOrgEx(x, y, point);
			}
			/// Paints the specified region by using the brush currently selected into the device context.
			void SvgGdi::PaintRgn(IGdiRegion* rgn)
			{
				FillRgn(rgn, _dc->Brush());
			}

			/// TODO
			void SvgGdi::PatBlt(int x, int y, int width, int height, long rop)
			{
				// TODO
				printf("not implemented: patBlt \r\n");
			}

			/// Draws a pie-shaped wedge bounded by the intersection of an ellipse and two radials. 
			/// The pie is outlined by using the current pen and filled by using the current brush.
			void SvgGdi::Pie(int sxr, int syr, int exr, int eyr, int sxa, int sya, int exa, int eya)
			{
				double rx = abs(exr - sxr) / 2.0;
				double ry = abs(eyr - syr) / 2.0;
				if (rx <= 0 || ry <= 0) return;

				double cx = min(sxr, exr) + rx;
				double cy = min(syr, eyr) + ry;

				tinyxml2::XMLElement* elem = NULL;
				if (sxa == exa && sya == eya)
				{
					if (rx == ry)
					{
//						elem = _doc->NewElement("circle http://www.w3.org/2000/svg");
						elem = _doc->NewElement("circle");

						elem->SetAttribute("cx",doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("r", doubleToString(_dc->ToRelativeX(rx)).c_str());
					}
					else
					{
//						elem = _doc->NewElement("ellipse http://www.w3.org/2000/svg");
						elem = _doc->NewElement("ellipse");

						elem->SetAttribute("cx", doubleToString(_dc->ToAbsoluteX(cx)).c_str());
						elem->SetAttribute("cy", doubleToString(_dc->ToAbsoluteY(cy)).c_str());
						elem->SetAttribute("rx", doubleToString(_dc->ToRelativeX(rx)).c_str());
						elem->SetAttribute("ry", doubleToString(_dc->ToRelativeY(ry)).c_str());
					}
				}
				else
				{
					double sa = atan2((sya - cy) * rx, (sxa - cx) * ry);
					//intf(sa + " " + cos(sa));
					double sx = rx * cos(sa);
					double sy = ry * sin(sa);

					double ea = atan2((eya - cy) * rx, (exa - cx) * ry);
					double ex = rx * cos(ea);
					double ey = ry * sin(ea);

					double a = atan2((ex - sx) * (-sy) - (ey - sy) * (-sx), (ex - sx) * (-sx) + (ey - sy) * (-sy));

//					elem = _doc->NewElement("path http://www.w3.org/2000/svg");
					elem = _doc->NewElement("path");

					string data = "M " + doubleToString(_dc->ToAbsoluteX(cx)) + "," + doubleToString(_dc->ToAbsoluteY(cy))
						+ " L " + doubleToString(_dc->ToAbsoluteX(sx + cx)) + "," + doubleToString(_dc->ToAbsoluteY(sy + cy))
						+ " A " + doubleToString(_dc->ToRelativeX(rx)) + "," + doubleToString(_dc->ToRelativeY(ry))
						+ " 0 " + (a > 0 ? "1" : "0") + " 0"
						+ " " + doubleToString(_dc->ToAbsoluteX(ex + cx)) + "," + doubleToString(_dc->ToAbsoluteY(ey + cy)) + " Z";
					elem->SetAttribute("d", data.c_str());
				}

				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill", id.c_str() );
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
				}
				_parentNode->InsertEndChild(elem);
			}

			/// Draws a polygon consisting of two or more vertices connected by straight lines. 
			/// The polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode.
			void SvgGdi::Polygon(vector< WMFConverter::Point*> points)
			{
				tinyxml2::XMLElement* elem = _doc->NewElement("polygon");

				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill", id.c_str());
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
					if (_dc->PolyFillMode() == (int)GdiEnum::WINDING)
						elem->SetAttribute("fill-rule", "nonzero");
				}

				_buffer = "";
				for (int i = 0; i < points.size(); i++)
				{
					if (i != 0)
						_buffer += " ";
					_buffer += intToString((int)_dc->ToAbsoluteX(points.at(i)->X)) + ",";
					_buffer += intToString((int)_dc->ToAbsoluteY(points.at(i)->Y));
				}
				elem->SetAttribute("points", _buffer.c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// Element is an SVG basic shape that creates straight lines connecting several points. 
			/// Typically a polyline is used to create open shapes as the last point doesn't have to be connected to the first point. 
			void SvgGdi::Polyline(vector<WMFConverter::Point*> points)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("polyline http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("polyline");

				if (_dc->Pen() != NULL)
					elem->SetAttribute("class", GetClassString(_dc->Pen()).c_str());
				elem->SetAttribute("fill", "none");

				_buffer = "";
				for (int i = 0; i < points.size(); i++)
				{
					if (i != 0)
						_buffer += " ";
					_buffer += intToString((int)_dc->ToAbsoluteX(points.at(i)->X)) + ",";
					_buffer += intToString((int)_dc->ToAbsoluteY(points.at(i)->Y));
				}
				elem->SetAttribute("points", _buffer.c_str());
				_parentNode->InsertEndChild(elem);
			}

			///  Draws a series of closed polygons. 
			///  Each polygon is outlined by using the current pen and filled by using the current brush and polygon fill mode. 
			///  The polygons drawn by this function can overlap.
			void SvgGdi::PolyPolygon(vector< WMFConverter::Point*> points, int* len)
			{
				//tinyxml2::XMLElement* elem = _doc->NewElement("path http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("path");

				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill",  id.c_str());
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
					if (_dc->PolyFillMode() == (int)GdiEnum::WINDING)
						elem->SetAttribute("fill-rule", "nonzero");
				}

				_buffer = "";
				for (int i = 0; i < sizeof(len) / sizeof(int); i++)
				{
					if (i != 0)
						_buffer += " ";
					int size = len[i];
					for (int j = 0; j < size; j++)
					{
						if (j == 0)
							_buffer += "M ";
						else if (j == 1)
							_buffer += " L ";
						int index = i * size + j;
						WMFConverter::Point* temp = points.at(index);
						int x = temp->X;
						int a = (int)_dc->ToAbsoluteX((int)x);
						_buffer += intToString((int)a)+",";

						int y = temp->Y;
						int b = _dc->ToAbsoluteY((int)y);
						_buffer += intToString((int)b) + " ";

						if (j == len[i] - 1)
							_buffer += "z";
					}
				}
				elem->SetAttribute("d", _buffer.c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// TODO
			void SvgGdi::RealizePalette()
			{
				// TODO
				printf("not implemented: realizePalette \r\n");
			}

			/// Restores a device context (DC) to the specified state. 
			/// The DC is restored by popping state information off a stack created by earlier calls to the SaveDC function.
			void SvgGdi::RestoreDC(int savedDC)
			{
				int limit = (savedDC < 0) ? -savedDC : _saveDC.size() - savedDC;
				for (int i = 0; i < limit; i++)
				{
					_dc = (SvgDc*)_saveDC.at(_saveDC.size() - 1);
					_saveDC.pop_back();
				}

				if (!_parentNode->FirstChild())
					_doc->RootElement()->DeleteChild(_parentNode);
//				_parentNode = _doc->NewElement("g http://www.w3.org/2000/svg");
				_parentNode = _doc->NewElement("g");

				tinyxml2::XMLElement* mask = _dc->Mask();
				if (mask != NULL)
				{
					string data = "url(#" + string(mask->FindAttribute("id")->Value()) + ")";
					_parentNode->SetAttribute("mask", data.c_str());
				}
				_doc->RootElement()->InsertEndChild(_parentNode);
			}

			/// Draws a rectangle. 
			/// The rectangle is outlined by using the current pen and filled by using the current brush.
			void SvgGdi::Rectangle(int sx, int sy, int ex, int ey)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("rect http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("rect");


				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", getClassString((WMFConverter::IGdiObject*)_dc->Pen(), (WMFConverter::IGdiObject*)_dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill", id.c_str() );
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
				}

				elem->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(sx)).c_str());
				elem->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(sy)).c_str());
				elem->SetAttribute("width", intToString((int)_dc->ToRelativeX(ex - sx)).c_str());
				elem->SetAttribute("height", intToString((int)_dc->ToRelativeY(ey - sy)).c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// TODO
			void SvgGdi::ResizePalette(IGdiPalette *palette)
			{
				// TODO
				printf("not implemented: ResizePalette \r\n");
			}

			/// Draws a rectangle with rounded corners. 
			/// The rectangle is outlined by using the current pen and filled by using the current brush.
			void SvgGdi::RoundRect(int sx, int sy, int ex, int ey, int rw, int rh)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("rect http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("rect");


				if (_dc->Pen() != NULL || _dc->Brush() != NULL)
				{
					elem->SetAttribute("class", getClassString(_dc->Pen(), _dc->Brush()).c_str());
					if (_dc->Brush() != NULL && _dc->Brush()->Style() == (int)BrushBSEnum::BS_HATCHED)
					{
						string id = "url(#pattern" + intToString(_patternNo++) + ")";
						elem->SetAttribute("fill", id.c_str() );
						_defsNode->InsertEndChild(_dc->Brush()->CreateFillPattern(id));
					}
				}

				elem->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(sx)).c_str());
				elem->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(sy)).c_str());
				elem->SetAttribute("width", intToString((int)_dc->ToRelativeX(ex - sx)).c_str());
				elem->SetAttribute("height", intToString((int)_dc->ToRelativeY(ey - sy)).c_str());
				elem->SetAttribute("rx", intToString((int)_dc->ToRelativeX(rw)).c_str());
				elem->SetAttribute("ry", intToString((int)_dc->ToRelativeY(rh)).c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// Save device context (DC).
			void SvgGdi::SeveDC()
			{
				_saveDC.push_back((SvgDc*)_dc->Clone());
			}

			/// Modifies the viewport for a device context using the ratios formed by the specified multiplicands and divisors.
			void SvgGdi::ScaleViewportExtEx(int x, int xd, int y, int yd, WMFConverter::Size* old)
			{
				_dc->ScaleViewportExtEx(x, xd, y, yd, old);
			}

			/// Modifies the window for a device context using the ratios formed by the specified multiplicands and divisors.
			void SvgGdi::ScaleWindowExtEx(int x, int xd, int y, int yd, WMFConverter::Size* old)
			{
				_dc->ScaleWindowExtEx(x, xd, y, yd, old);
			}

			/// Selects a region as the current clipping region for the specified device context.
			void SvgGdi::SelectClipRgn(IGdiRegion* rgn)
			{
				if (!_parentNode->FirstChild())
					_doc->RootElement()->DeleteChild(_parentNode);
//				_parentNode = _doc->NewElement("g http://www.w3.org/2000/svg");
				_parentNode = _doc->NewElement("g");


				if (rgn != NULL)
				{
//					tinyxml2::XMLElement* mask = _doc->NewElement("mask http://www.w3.org/2000/svg");
					tinyxml2::XMLElement* mask = _doc->NewElement("mask");

					string data = "mask" + intToString(_maskNo++);
					mask->SetAttribute("id", data.c_str());
					//mask.setIdAttribute("id", true);

					if (_dc->OffsetClipX() != 0 || _dc->OffsetClipY() != 0)
					{
						data = "translate(" + intToString(_dc->OffsetClipX()) + "," + intToString(_dc->OffsetClipY()) + ")";
						mask->SetAttribute("transform", data.c_str());
					}
					_defsNode->InsertEndChild(mask);

//					tinyxml2::XMLElement* clip = _doc->NewElement("use http://www.w3.org/2000/svg");
					tinyxml2::XMLElement* clip = _doc->NewElement("use");

					string output = "";
					output = "url(#" + _nameMap[rgn] + ")";
					clip->SetAttribute("xlink:href", output.c_str());
					clip->SetAttribute("fill", "white");

					mask->InsertEndChild(clip);

					data = "url(#" + string(mask->FindAttribute("id")->Value()) + ")";
					_parentNode->SetAttribute("mask", data.c_str());
				}

				_doc->RootElement()->InsertEndChild(_parentNode);
			}

			/// Selects an object into the specified device context (DC). The new object replaces the previous object of the same type.
			void SvgGdi::SelectObject(WMFConverter::IGdiObject *obj)
			{
				
				//if (obj->GetType() == "Brush")
				//	_dc->SetBrush((SvgBrush*)obj);
				//else if (obj->GetType() == "Font")
				//	_dc->SetFont((SvgFont*)obj);
				//else if (obj->GetType() == "Pen")
				//	_dc->SetPen((SvgPen*)obj);
				
			}

			void SvgGdi::SelectObject(WMFConverter::IGdiObject *obj, string type)
			{
				if (type == "Brush")
				{
					_dc->SetBrush((SvgBrush*)obj);
				}
				else if (type == "Font")
				{
					_dc->SetFont((SvgFont*)obj);
				}
				else if (type == "Pen")
				{
					_dc->SetPen((SvgPen*)obj);
				}
			}


			/// TODO
			void SvgGdi::SelectPalette(IGdiPalette *palette, bool mode)
			{
				// TODO
				printf("not implemented: selectPalette \r\n");
			}

			/// Sets the current background color to the specified color value, or to the nearest physical color if the device cannot represent the specified color value.
			void SvgGdi::SetBkColor(int color)
			{
				_dc->SetBkColor(color);
			}

			/// Sets the background mix mode of the specified device context. 
			/// The background mix mode is used with text, hatched brushes, and pen styles that are not solid lines.
			void SvgGdi::SetBkMode(int mode)
			{
				_dc->SetBkMode(mode);
			}

			/// Sets the pixels in the specified rectangle on the device that is associated with the destination device context using color data from a DIB, JPEG, or PNG image.
			void SvgGdi::SetDIBitsToDevice(int dx, int dy, int dw, int dh, int sx, int sy, int startscan, int scanlines, char* image, int colorUse)
			{
				StretchDIBits(dx, dy, dw, dh, sx, sy, dw, dh, image, colorUse, (int)GdiEnum::SRCCOPY);
			}

			/// Changes the layout of a device context (DC).
			void SvgGdi::SetLayout(long layout)
			{
				_dc->SetLayout(layout);
			}

			/// Sets the mapping mode of the specified device context. 
			/// The mapping mode defines the unit of measure used to transform page-space units into device-space units, and also defines the orientation of the device's x and y axes.
			void SvgGdi::SetMapMode(int mode)
			{
				_dc->SetMapMode(mode);
			}

			/// Alters the algorithm the font mapper uses when it maps logical fonts to physical fonts.
			void SvgGdi::SetMapperFlags(long flags)
			{
				_dc->SetMapperFlags(flags);
			}

			/// TODO
			void SvgGdi::SetPaletteEntries(IGdiPalette* palette, int startIndex, int* entries)
			{
				// TODO
				printf("not implemented: setPaletteEntries");
			}

			/// Sets the pixel at the specified coordinates to the specified color.
			void SvgGdi::SetPixel(int x, int y, int color)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("rect http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("rect");

				elem->SetAttribute("stroke", "none");
				elem->SetAttribute("fill", (SvgPen::ToColor(color)).c_str());
				elem->SetAttribute("x", intToString((int)_dc->ToAbsoluteX(x)).c_str());
				elem->SetAttribute("y", intToString((int)_dc->ToAbsoluteY(y)).c_str());
				elem->SetAttribute("width", intToString((int)_dc->ToRelativeX(1)).c_str());
				elem->SetAttribute("height", intToString((int)_dc->ToRelativeY(1)).c_str());
				_parentNode->InsertEndChild(elem);
			}

			/// Sets the polygon fill mode for functions that fill polygons.
			void SvgGdi::SetPolyFillMode(int mode)
			{
				_dc->SetPolyFillMode(mode);
			}

			void SvgGdi::SetRelAbs(int mode)
			{
				_dc->SetRelAbs(mode);
			}

			/// Sets the current foreground mix mode. 
			/// GDI uses the foreground mix mode to combine pens and interiors of filled objects with the colors already on the screen. 
			/// The foreground mix mode defines how colors from the brush or pen and the colors in the existing image are to be combined.
			void SvgGdi::SetROP2(int mode)
			{
				_dc->SetROP2(mode);
			}

			/// Sets the bitmap stretching mode in the specified device context.
			void SvgGdi::SetStretchBltMode(int mode)
			{
				_dc->SetStretchBltMode(mode);
			}

			/// Sets the text-alignment flags for the specified device context.
			void SvgGdi::SetTextAlign(int align)
			{
				_dc->SetTextAlign(align);
			}

			/// Sets the intercharacter spacing. 
			/// Intercharacter spacing is added to each character, including break characters, when the system writes a line of text.
			void SvgGdi::SetTextCharacterExtra(int extra)
			{
				_dc->SetTextCharacterExtra(extra);
			}

			/// Sets the text color for the specified device context to the specified color.
			void SvgGdi::SetTextColor(int color)
			{
				_dc->SetTextColor(color);
			}

			/// Specifies the amount of space the system should add to the break characters in a string of text. 
			/// The space is added when an application calls the TextOut or ExtTextOut functions.
			void SvgGdi::SetTextJustification(int breakExtra, int breakCount)
			{
				if (breakCount > 0)
					_dc->SetTextSpace(abs((int)_dc->ToRelativeX(breakExtra)) / breakCount);
			}

			/// Sets the horizontal and vertical extents of the viewport for a device context by using the specified values.
			void SvgGdi::SetViewportExtEx(int x, int y, WMFConverter::Size* old)
			{
				_dc->SetViewportExtEx(x, y, old);
			}

			/// Specifies which device point maps to the window origin (0,0).
			void SvgGdi::SetViewportOrgEx(int x, int y, WMFConverter::Point* old)
			{
				_dc->SetViewportOrgEx(x, y, old);
			}

			/// Sets the horizontal and vertical extents of the window for a device context by using the specified values.
			void SvgGdi::SetWindowExtEx(int width, int height, WMFConverter::Size *old)
			{
				_dc->SetWindowExtEx(width, height, old);
			}

			/// Specifies which window point maps to the viewport origin (0,0).
			void SvgGdi::SetWindowOrgEx(int x, int y, WMFConverter::Point* old)
			{
				_dc->SetWindowOrgEx(x, y, old);
			}

			/// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. 
			/// The system stretches or compresses the bitmap according to the stretching mode currently set in the destination device context.
			void SvgGdi::StretchBlt(char* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, long rop)
			{
				DibStretchBlt(image, dx, dy, dw, dh, sx, sy, sw, sh, rop);
			}

			/// Copies the color data for a rectangle of pixels in a DIB, JPEG, or PNG image to the specified destination rectangle. 
			/// If the destination rectangle is larger than the source rectangle, this function stretches the rows and columns of color data to fit the destination rectangle. If the destination rectangle is smaller than the source rectangle, this function compresses the rows and columns by using the specified raster operation.
			void SvgGdi::StretchDIBits(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, char* image, int usage, long rop)
			{
				bmpToSvg(image, dx, dy, dw, dh, sx, sy, sw, sh, usage, rop);
			}

			/// Writes a character string at the specified location, using the currently selected font, background color, and text color.
			void SvgGdi::TextOut(int x, int y, char* text)
			{
//				tinyxml2::XMLElement* elem = _doc->NewElement("text http://www.w3.org/2000/svg");
				tinyxml2::XMLElement* elem = _doc->NewElement("text");


				int escapement = 0;
				bool vertical = false;
				if (_dc->Font() != NULL)
				{
					elem->SetAttribute("class", GetClassString(_dc->Font()).c_str());
					if (_dc->Font()->FaceName()[0] == '@')
					{
						vertical = true;
						escapement = _dc->Font()->Escapement() - 2700;
					}
					else
						escapement = _dc->Font()->Escapement();
				}
				elem->SetAttribute("fill", SvgObject::ToColor(_dc->TextColor()).c_str());

				// style
				_buffer = "";
				int align = _dc->TextAlign();

				if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_RIGHT)
					_buffer += "text-anchor: end; ";
				else if ((align & ((int)GdiEnum::TA_LEFT | (int)GdiEnum::TA_RIGHT | (int)GdiEnum::TA_CENTER)) == (int)GdiEnum::TA_CENTER)
					_buffer += "text-anchor: middle; ";

				if (vertical)
				{
					elem->SetAttribute("writing-mode", "tb");
					_buffer += "dominant-baseline: ideographic; ";
				}
				else
				{
					if ((align & ((int)GdiEnum::TA_BOTTOM | (int)GdiEnum::TA_TOP | (int)GdiEnum::TA_BASELINE)) == (int)GdiEnum::TA_BASELINE)
						_buffer += "dominant-baseline: alphabetic; ";
					else
						_buffer += "dominant-baseline: text-before-edge; ";
				}

				if ((align & (int)GdiEnum::TA_RTLREADING) == (int)GdiEnum::TA_RTLREADING)
					_buffer += "unicode-bidi: bidi-override; direction: rtl; ";

				if (_dc->TextSpace() > 0)
					_buffer += "word-spacing: " + intToString(_dc->TextSpace()) + "; ";

				if (_buffer.size() > 0)
				{
					elem->SetAttribute("style", _buffer.c_str());
				}

				elem->SetAttribute("stroke", "none");

				int ax = (int)_dc->ToAbsoluteX(x);
				int ay = (int)_dc->ToAbsoluteY(y);
				elem->SetAttribute("x", intToString(ax).c_str());
				elem->SetAttribute("y", intToString(ay).c_str());

				if (escapement != 0)
				{
					string data = "rotate(" + doubleToString(-1 * escapement / 10.0) + ", " + intToString(ax) + ", " + intToString(ay) + ")";
					elem->SetAttribute("transform", data.c_str());

				}
				string str = "";
				if (_dc->Font() != NULL)
					str = GdiUtils::ConvertString(text, (FontCharsetEnum)_dc->Font()->Charset());
				else
					str = GdiUtils::ConvertString(text, FontCharsetEnum::DEFAULT_CHARSET);


				if (_dc->TextCharacterExtra() != 0)
				{
					_buffer = "";
					for (int i = 0; i < str.size() - 1; i++)
					{
						if (i != 0)
							_buffer += " ";
						_buffer += intToString((int)_dc->ToRelativeX(_dc->TextCharacterExtra()));
					}
					elem->SetAttribute("dx", _buffer.c_str());
				}

				if (_dc->Font() != NULL && _dc->Font()->Lang() != "")
					elem->SetAttribute("xml:lang", _dc->Font()->Lang().c_str());

				elem->SetAttribute("xml:space", "preserve");
				this->AppendText(elem, str);
				_parentNode->InsertEndChild(elem);
			}


			void SvgGdi::Footer()
			{
				tinyxml2::XMLElement *root = _doc->RootElement();
				if (!root->FindAttribute("width") && _dc->WindowWidth() != 0)
					root->SetAttribute("width",intToString(abs(_dc->WindowWidth())).c_str());

				if (!root->FindAttribute("height") && _dc->WindowHeight() != 0)
					root->SetAttribute("height", intToString(abs(_dc->WindowHeight())).c_str());

				if (_dc->WindowWidth() != 0 && _dc->WindowHeight() != 0)
				{
					string data = "0 0 " + intToString(abs(_dc->WindowWidth())) + " " + intToString(abs(_dc->WindowHeight()));
					root->SetAttribute("viewBox",data.c_str());
					root->SetAttribute("preserveAspectRatio", "none");
				}
				root->SetAttribute("stroke-linecap", "round");
				root->SetAttribute("fill-rule", "evenodd");

				if (!_styleNode->FirstChild())
					root->DeleteChild(_styleNode);
				else
				{
					try
					{
						_styleNode->InsertFirstChild(_doc->NewText("\r\n"));

						//_styleNode->InsertAfterChild(_doc->NewText("\r\n"), _styleNode->FirstChild());
					}
					catch (exception e)
					{
						printf("svggdi line 1483 error %s", e.what());
					}
				}
					

				if (!_defsNode->FirstChild())
					root->DeleteChild(_defsNode);
			}
			/// SVG Document - XML
			tinyxml2::XMLDocument * SvgGdi::Document()
			{
				return _doc;
			}
			tinyxml2::XMLElement * SvgGdi::DefsElement()
			{
				return _defsNode;
			}

			/// Style node element.
			tinyxml2::XMLElement * SvgGdi::StyleElement()
			{
				return _styleNode;
			}

			/// IE9-compatible style output
			bool SvgGdi::Compatible()
			{
				return _compatible;
			}
			void SvgGdi::SetCompatible(bool val){
				_compatible = val;
			}

			bool SvgGdi::ReplaceSymbolFont()
			{
				return _replaceSymbolFont;
			}
			void SvgGdi::SetReplaceSymbolFont(bool val){
				_replaceSymbolFont = val;
			}

			SvgDc* SvgGdi::DC()
			{
				return _dc;
			}


			string SvgGdi::getClassString(WMFConverter::IGdiObject* obj1, WMFConverter::IGdiObject* obj2)
			{
				string name1 = this->GetClassString(obj1);
				string name2 = this->GetClassString(obj2);
				if (name1 != "" && name2 != "")
					return name1 + " " + name2;

				if (name1 != "")
					return name1;

				if (name2 != "")
					return name2;

				return "";
			}

			/// Get class name.
			string SvgGdi::GetClassString(WMFConverter::IGdiObject *style)
			{
				if (style == NULL)
					return "";

				string output = "";
				output = _nameMap[style];
				return output;
			}

			/// Append specified string to specified element.
			void SvgGdi::AppendText(tinyxml2::XMLElement* elem, string str)
			{
				if (_compatible)
				{
					// TODO
					//str = System.Text.RegularExpressions.Regex.Replace(str, "\\r\\n", "\u00A0");
					//str = System.Text.RegularExpressions.Regex.Replace(str, "\\t\\r\\n", "\u00A0");
				}

				SvgFont* font = _dc->Font();
				if (_replaceSymbolFont && font != NULL)
				{
					if ("Symbol" == font->FaceName())
					{
						int state = 0; // 0: default, 1: serif, 2: sans-serif
						int start = 0;
						char* ca = (char*)(str.c_str());
						for (int i = 0; i < sizeof(ca); i++)
						{
							int nstate = state;
							switch (ca[i])
							{
/*	TODO
							case '"': ca[i] = '\u2200'; nstate = 1; break;
							case '$': ca[i] = '\u2203'; nstate = 1; break;
							case '\'': ca[i] = '\u220D'; nstate = 1; break;
							case '*': ca[i] = '\u2217'; nstate = 1; break;
							case '-': ca[i] = '\u2212'; nstate = 1; break;
							case '@': ca[i] = '\u2245'; nstate = 1; break;
							case 'A': ca[i] = '\u0391'; nstate = 1; break;
							case 'B': ca[i] = '\u0392'; nstate = 1; break;
							case 'C': ca[i] = '\u03A7'; nstate = 1; break;
							case 'D': ca[i] = '\u0394'; nstate = 1; break;
							case 'E': ca[i] = '\u0395'; nstate = 1; break;
							case 'F': ca[i] = '\u03A6'; nstate = 1; break;
							case 'G': ca[i] = '\u0393'; nstate = 1; break;
							case 'H': ca[i] = '\u0397'; nstate = 1; break;
							case 'I': ca[i] = '\u0399'; nstate = 1; break;
							case 'J': ca[i] = '\u03D1'; nstate = 1; break;
							case 'K': ca[i] = '\u039A'; nstate = 1; break;
							case 'L': ca[i] = '\u039B'; nstate = 1; break;
							case 'M': ca[i] = '\u039C'; nstate = 1; break;
							case 'N': ca[i] = '\u039D'; nstate = 1; break;
							case 'O': ca[i] = '\u039F'; nstate = 1; break;
							case 'P': ca[i] = '\u03A0'; nstate = 1; break;
							case 'Q': ca[i] = '\u0398'; nstate = 1; break;
							case 'R': ca[i] = '\u03A1'; nstate = 1; break;
							case 'S': ca[i] = '\u03A3'; nstate = 1; break;
							case 'T': ca[i] = '\u03A4'; nstate = 1; break;
							case 'U': ca[i] = '\u03A5'; nstate = 1; break;
							case 'V': ca[i] = '\u03C3'; nstate = 1; break;
							case 'W': ca[i] = '\u03A9'; nstate = 1; break;
							case 'X': ca[i] = '\u039E'; nstate = 1; break;
							case 'Y': ca[i] = '\u03A8'; nstate = 1; break;
							case 'Z': ca[i] = '\u0396'; nstate = 1; break;
							case '\\': ca[i] = '\u2234'; nstate = 1; break;
							case '^': ca[i] = '\u22A5'; nstate = 1; break;
							case '`': ca[i] = '\uF8E5'; nstate = 1; break;
							case 'a': ca[i] = '\u03B1'; nstate = 1; break;
							case 'b': ca[i] = '\u03B2'; nstate = 1; break;
							case 'c': ca[i] = '\u03C7'; nstate = 1; break;
							case 'd': ca[i] = '\u03B4'; nstate = 1; break;
							case 'e': ca[i] = '\u03B5'; nstate = 1; break;
							case 'f': ca[i] = '\u03C6'; nstate = 1; break;
							case 'g': ca[i] = '\u03B3'; nstate = 1; break;
							case 'h': ca[i] = '\u03B7'; nstate = 1; break;
							case 'i': ca[i] = '\u03B9'; nstate = 1; break;
							case 'j': ca[i] = '\u03D5'; nstate = 1; break;
							case 'k': ca[i] = '\u03BA'; nstate = 1; break;
							case 'l': ca[i] = '\u03BB'; nstate = 1; break;
							case 'm': ca[i] = '\u03BC'; nstate = 1; break;
							case 'n': ca[i] = '\u03BD'; nstate = 1; break;
							case 'o': ca[i] = '\u03BF'; nstate = 1; break;
							case 'p': ca[i] = '\u03C0'; nstate = 1; break;
							case 'q': ca[i] = '\u03B8'; nstate = 1; break;
							case 'r': ca[i] = '\u03C1'; nstate = 1; break;
							case 's': ca[i] = '\u03C3'; nstate = 1; break;
							case 't': ca[i] = '\u03C4'; nstate = 1; break;
							case 'u': ca[i] = '\u03C5'; nstate = 1; break;
							case 'v': ca[i] = '\u03D6'; nstate = 1; break;
							case 'w': ca[i] = '\u03C9'; nstate = 1; break;
							case 'x': ca[i] = '\u03BE'; nstate = 1; break;
							case 'y': ca[i] = '\u03C8'; nstate = 1; break;
							case 'z': ca[i] = '\u03B6'; nstate = 1; break;
							case '~': ca[i] = '\u223C'; nstate = 1; break;
							case '\u00A0': ca[i] = '\u20AC'; nstate = 1; break;
							case '\u00A1': ca[i] = '\u03D2'; nstate = 1; break;
							case '\u00A2': ca[i] = '\u2032'; nstate = 1; break;
							case '\u00A3': ca[i] = '\u2264'; nstate = 1; break;
							case '\u00A4': ca[i] = '\u2044'; nstate = 1; break;
							case '\u00A5': ca[i] = '\u221E'; nstate = 1; break;
							case '\u00A6': ca[i] = '\u0192'; nstate = 1; break;
							case '\u00A7': ca[i] = '\u2663'; nstate = 1; break;
							case '\u00A8': ca[i] = '\u2666'; nstate = 1; break;
							case '\u00A9': ca[i] = '\u2665'; nstate = 1; break;
							case '\u00AA': ca[i] = '\u2660'; nstate = 1; break;
							case '\u00AB': ca[i] = '\u2194'; nstate = 1; break;
							case '\u00AC': ca[i] = '\u2190'; nstate = 1; break;
							case '\u00AD': ca[i] = '\u2191'; nstate = 1; break;
							case '\u00AE': ca[i] = '\u2192'; nstate = 1; break;
							case '\u00AF': ca[i] = '\u2193'; nstate = 1; break;
							case '\u00B2': ca[i] = '\u2033'; nstate = 1; break;
							case '\u00B3': ca[i] = '\u2265'; nstate = 1; break;
							case '\u00B4': ca[i] = '\u00D7'; nstate = 1; break;
							case '\u00B5': ca[i] = '\u221D'; nstate = 1; break;
							case '\u00B6': ca[i] = '\u2202'; nstate = 1; break;
							case '\u00B7': ca[i] = '\u2022'; nstate = 1; break;
							case '\u00B8': ca[i] = '\u00F7'; nstate = 1; break;
							case '\u00B9': ca[i] = '\u2260'; nstate = 1; break;
							case '\u00BA': ca[i] = '\u2261'; nstate = 1; break;
							case '\u00BB': ca[i] = '\u2248'; nstate = 1; break;
							case '\u00BC': ca[i] = '\u2026'; nstate = 1; break;
							case '\u00BD': ca[i] = '\u23D0'; nstate = 1; break;
							case '\u00BE': ca[i] = '\u23AF'; nstate = 1; break;
							case '\u00BF': ca[i] = '\u21B5'; nstate = 1; break;
							case '\u00C0': ca[i] = '\u2135'; nstate = 1; break;
							case '\u00C1': ca[i] = '\u2111'; nstate = 1; break;
							case '\u00C2': ca[i] = '\u211C'; nstate = 1; break;
							case '\u00C3': ca[i] = '\u2118'; nstate = 1; break;
							case '\u00C4': ca[i] = '\u2297'; nstate = 1; break;
							case '\u00C5': ca[i] = '\u2295'; nstate = 1; break;
							case '\u00C6': ca[i] = '\u2205'; nstate = 1; break;
							case '\u00C7': ca[i] = '\u2229'; nstate = 1; break;
							case '\u00C8': ca[i] = '\u222A'; nstate = 1; break;
							case '\u00C9': ca[i] = '\u2283'; nstate = 1; break;
							case '\u00CA': ca[i] = '\u2287'; nstate = 1; break;
							case '\u00CB': ca[i] = '\u2284'; nstate = 1; break;
							case '\u00CC': ca[i] = '\u2282'; nstate = 1; break;
							case '\u00CD': ca[i] = '\u2286'; nstate = 1; break;
							case '\u00CE': ca[i] = '\u2208'; nstate = 1; break;
							case '\u00CF': ca[i] = '\u2209'; nstate = 1; break;
							case '\u00D0': ca[i] = '\u2220'; nstate = 1; break;
							case '\u00D1': ca[i] = '\u2207'; nstate = 1; break;
							case '\u00D2': ca[i] = '\u00AE'; nstate = 1; break;
							case '\u00D3': ca[i] = '\u00A9'; nstate = 1; break;
							case '\u00D4': ca[i] = '\u2122'; nstate = 1; break;
							case '\u00D5': ca[i] = '\u220F'; nstate = 1; break;
							case '\u00D6': ca[i] = '\u221A'; nstate = 1; break;
							case '\u00D7': ca[i] = '\u22C5'; nstate = 1; break;
							case '\u00D8': ca[i] = '\u00AC'; nstate = 1; break;
							case '\u00D9': ca[i] = '\u2227'; nstate = 1; break;
							case '\u00DA': ca[i] = '\u2228'; nstate = 1; break;
							case '\u00DB': ca[i] = '\u21D4'; nstate = 1; break;
							case '\u00DC': ca[i] = '\u21D0'; nstate = 1; break;
							case '\u00DD': ca[i] = '\u21D1'; nstate = 1; break;
							case '\u00DE': ca[i] = '\u21D2'; nstate = 1; break;
							case '\u00DF': ca[i] = '\u21D3'; nstate = 1; break;
							case '\u00E0': ca[i] = '\u25CA'; nstate = 1; break;
							case '\u00E1': ca[i] = '\u3008'; nstate = 1; break;
							case '\u00E2': ca[i] = '\u00AE'; nstate = 2; break;
							case '\u00E3': ca[i] = '\u00A9'; nstate = 2; break;
							case '\u00E4': ca[i] = '\u2122'; nstate = 2; break;
							case '\u00E5': ca[i] = '\u2211'; nstate = 1; break;
							case '\u00E6': ca[i] = '\u239B'; nstate = 1; break;
							case '\u00E7': ca[i] = '\u239C'; nstate = 1; break;
							case '\u00E8': ca[i] = '\u239D'; nstate = 1; break;
							case '\u00E9': ca[i] = '\u23A1'; nstate = 1; break;
							case '\u00EA': ca[i] = '\u23A2'; nstate = 1; break;
							case '\u00EB': ca[i] = '\u23A3'; nstate = 1; break;
							case '\u00EC': ca[i] = '\u23A7'; nstate = 1; break;
							case '\u00ED': ca[i] = '\u23A8'; nstate = 1; break;
							case '\u00EE': ca[i] = '\u23A9'; nstate = 1; break;
							case '\u00EF': ca[i] = '\u23AA'; nstate = 1; break;
							case '\u00F0': ca[i] = '\uF8FF'; nstate = 1; break;
							case '\u00F1': ca[i] = '\u3009'; nstate = 1; break;
							case '\u00F2': ca[i] = '\u222B'; nstate = 1; break;
							case '\u00F3': ca[i] = '\u2320'; nstate = 1; break;
							case '\u00F4': ca[i] = '\u23AE'; nstate = 1; break;
							case '\u00F5': ca[i] = '\u2321'; nstate = 1; break;
							case '\u00F6': ca[i] = '\u239E'; nstate = 1; break;
							case '\u00F7': ca[i] = '\u239F'; nstate = 1; break;
							case '\u00F8': ca[i] = '\u23A0'; nstate = 1; break;
							case '\u00F9': ca[i] = '\u23A4'; nstate = 1; break;
							case '\u00FA': ca[i] = '\u23A5'; nstate = 1; break;
							case '\u00FB': ca[i] = '\u23A6'; nstate = 1; break;
							case '\u00FC': ca[i] = '\u23AB'; nstate = 1; break;
							case '\u00FD': ca[i] = '\u23AC'; nstate = 1; break;
							case '\u00FE': ca[i] = '\u23AD'; nstate = 1; break;
							case '\u00FF': ca[i] = '\u2192'; nstate = 1; break;
*/
							default: nstate = 0; break;
							}

							if (nstate != state)
							{
								if (start < i)
								{
									tinyxml2::XMLNode* text = _doc->NewText(string(ca).substr(start, i - start).c_str());
									if (state == 0)
										elem->InsertEndChild(text);
									else if (state == 1)
									{
//										tinyxml2::XMLElement *span = _doc->NewElement("tspan http://www.w3.org/2000/svg");
										tinyxml2::XMLElement *span = _doc->NewElement("tspan");

										span->SetAttribute("font-family", "serif");
										span->InsertEndChild(text);
										elem->InsertEndChild(span);
									}
									else if (state == 2)
									{
//										tinyxml2::XMLElement *span = _doc->NewElement("tspan http://www.w3.org/2000/svg");
										tinyxml2::XMLElement *span = _doc->NewElement("tspan");

										span->SetAttribute("font-family", "sans-serif");
										span->InsertEndChild(text);
										elem->InsertEndChild(span);
									}
									start = i;
								}
								state = nstate;
							}
						}

						if (start < sizeof(ca))
						{
							tinyxml2::XMLNode* text = _doc->NewText((string(ca).substr(start, sizeof(ca) - start)).c_str());
							if (state == 0)
								elem->InsertEndChild(text);
							else if (state == 1)
							{
//								tinyxml2::XMLElement * span = _doc->NewElement("tspan http://www.w3.org/2000/svg");
								tinyxml2::XMLElement * span = _doc->NewElement("tspan");

								span->SetAttribute("font-family", "serif");
								span->InsertEndChild(text);
								elem->InsertEndChild(span);
							}
							else if (state == 2)
							{
//								tinyxml2::XMLElement * span = _doc->NewElement("tspan http://www.w3.org/2000/svg");
								tinyxml2::XMLElement * span = _doc->NewElement("tspan");

								span->SetAttribute("font-family", "sans-serif");
								span->InsertEndChild(text);
								elem->InsertEndChild(span);
							}
						}
						return;
					}
				}

				elem->InsertEndChild(_doc->NewText(str.c_str()));
			}



			/// Convert BMP to SVG.
			void SvgGdi::bmpToSvg(char* image, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, int usage, long rop)
			{
				printf("bmpToSvg: not implemented.");
			}

			/// Convert Dib to BMP.
			char* SvgGdi::dibToBmp(char* dib)
			{
				char* data = (char*)malloc(sizeof(dib) + 14);

				/* BitmapFileHeader */
				data[0] = 0x42; // 'B'
				data[1] = 0x4d; // 'M'

				long bfSize = sizeof(data);
				data[2] = (char)(bfSize & 0xff);
				data[3] = (char)((bfSize >> 8) & 0xff);
				data[4] = (char)((bfSize >> 16) & 0xff);
				data[5] = (char)((bfSize >> 24) & 0xff);

				// reserved 1
				data[6] = 0x00;
				data[7] = 0x00;

				// reserved 2
				data[8] = 0x00;
				data[9] = 0x00;

				// offset
				long bfOffBits = 14;

				/* BitmapInfoHeader */
				long biSize = (dib[0] & 0xff) + ((dib[1] & 0xff) << 8)
					+ ((dib[2] & 0xff) << 16) + ((dib[3] & 0xff) << 24);
				bfOffBits += biSize;

				int biBitCount = (dib[14] & 0xff) + ((dib[15] & 0xff) << 8);

				long clrUsed = (dib[32] & 0xff) + ((dib[33] & 0xff) << 8)
					+ ((dib[34] & 0xff) << 16) + ((dib[35] & 0xff) << 24);

				switch (biBitCount)
				{
				case 1:
					bfOffBits += (0x1L + 1) * 4;
					break;
				case 4:
					bfOffBits += (0xFL + 1) * 4;
					break;
				case 8:
					bfOffBits += (0xFFL + 1) * 4;
					break;
				case 16:
					bfOffBits += (clrUsed == 0L) ? 0 : (0xFFFFL + 1) * 4;
					break;
				case 24:
					bfOffBits += (clrUsed == 0L) ? 0 : (0xFFFFFFL + 1) * 4;
					break;
				case 32:
					bfOffBits += (clrUsed == 0L) ? 0 : (0xFFFFFFFFL + 1) * 4;
					break;
				}

				data[10] = (char)(bfOffBits & 0xff);
				data[11] = (char)((bfOffBits >> 8) & 0xff);
				data[12] = (char)((bfOffBits >> 16) & 0xff);
				data[13] = (char)((bfOffBits >> 24) & 0xff);

				memcpy(data + 14, dib, sizeof(dib));

				return data;
			}

			/// Init Document.
			void SvgGdi::init()
			{
				_dc = new SvgDc(this);
				tinyxml2::XMLElement* root = _doc->RootElement();
				root->SetAttribute("xmlns","http://www.w3.org/2000/svg");
				root->SetAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");

				_defsNode = _doc->NewElement("defs http://www.w3.org/2000/svg");
				root->InsertEndChild(_defsNode);


//				_styleNode = _doc->NewElement("style"," http://www.w3.org/2000/svg");
				_styleNode = _doc->NewElement("style");
				_styleNode->SetAttribute("type", "text/css");
				root->InsertEndChild(_styleNode);


//				_parentNode = _doc->NewElement("g", "http://www.w3.org/2000/svg");
				_parentNode = _doc->NewElement("g");
				_doc->RootElement()->InsertEndChild(_parentNode);

				_defaultBrush = (SvgBrush*)CreateBrushIndirect((int)BrushBSEnum::BS_SOLID,
					0x00FFFFFF, 0);
				_defaultPen = (SvgPen*)CreatePenIndirect((int)PenPSEnum::PS_SOLID, 1,
					0x00000000);
				_defaultFont = NULL;

				_dc->SetBrush(_defaultBrush);
				_dc->SetPen( _defaultPen);
				_dc->SetFont( _defaultFont);
			}

			void SvgGdi::initialPrivateData(){
				_compatible = false;
				_replaceSymbolFont = false;
				_saveDC.clear();
				_props = new Properties();
				_doc = NULL;
				_parentNode = NULL;
				_styleNode = NULL;
				_defsNode = NULL;
				_brushNo = 0;
				_fontNo = 0;
				_penNo = 0;
				_patternNo = 0;
				_rgnNo = 0;
				_clipPathNo = 0;
				_maskNo = 0;
				_buffer = "";
				_defaultBrush = NULL;
				_defaultPen = NULL;
				_defaultFont = NULL;
			}

}

