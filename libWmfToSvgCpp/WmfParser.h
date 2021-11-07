#ifndef _WMF_PARSE_H_
#define _WMF_PARSE_H_

#include <iostream>
#include <vector>
#include <exception>
#include "IGdi.h"
#include "DataInput.h"
#include "WmfConstants.h"

namespace WMFConverter{
	namespace Wmf{

		class WmfParser
		{
		public:
			WmfParser(){};
			/// Parse WMF file to SVG file.
			/// </summary>
			/// <param name="stream"></param>
			/// <param name="gdi"></param>
			void Parse(ifstream *stream, IGdi *gdi,string filename)
			{
				WMFConverter::DataInput *binReader = NULL;
				bool isEmpty = true;

				try
				{
					binReader = new WMFConverter::DataInput(filename, true);

					//binReader = new WMFConverter::DataInput(stream, true);

					int mtType = 0;
					int mtHeaderSize = 0;

					long key = binReader->ReadUint32();
					isEmpty = false;
					if (key == -1698247209)//0x9AC6CDD7)
					{
						int hmf = binReader->ReadInt16();
						int vsx = binReader->ReadInt16();
						int vsy = binReader->ReadInt16();
						int vex = binReader->ReadInt16();
						int vey = binReader->ReadInt16();
						int dpi = binReader->ReadUint16();
						long reserved = binReader->ReadUint32();
						int checksum = binReader->ReadUint16();

						gdi->PlaceableHeader(vsx, vsy, vex, vey, dpi);

						mtType = binReader->ReadUint16();
						mtHeaderSize = binReader->ReadUint16();
					}
					else
					{
						mtType = (int)(key & 0x0000FFFF);
						mtHeaderSize = (int)((key & 0xFFFF0000) >> 16);
					}

					int mtVersion = binReader->ReadUint16();
					long mtSize = binReader->ReadUint32();
					int mtNoObjects = binReader->ReadUint16();
					long mtMaxRecord = binReader->ReadUint32();
					int mtNoParameters = binReader->ReadUint16();

					if (mtType != 1 || mtHeaderSize != 9)
					{
						//throw new WmfParseException("invalid file format.");
						//throw exception("invalid file format.");
					}

					gdi->Header();

					//WMFConverter::IGdiObject* objs = {};
					//new WMFConverter.gdi->IGdiObject[mtNoObjects];

					vector<WMFConverter::IGdiObject*> objs;
					vector<string> objsType;
					for (int i = 0; i < mtNoObjects; i++)
					{
						WMFConverter::IGdiObject* obj	= NULL	;// = new WMFConverter::IGdiObject();
						objs.push_back(obj);
						objsType.push_back("");
					}

					while (true)
					{
						int size = (int)binReader->ReadUint32() - 3;
						int id = binReader->ReadUint16();

						int count_Flag = binReader->Count();

						if (id == (int)WmfConstants::RECORD_EOF)
							break; // Last record

						binReader->setCount(0);
						switch (id)
						{
						case (int)WmfConstants::RECORD_REALIZE_PALETTE:
							gdi->RealizePalette();
							break;
						case (int)WmfConstants::RECORD_SET_PALETTE_ENTRIES:
						{
							//int* entries = new int[binReader->ReadUint16()];

							int entriesSize = binReader->ReadUint16();

							int* entries = (int*)malloc(entriesSize * sizeof(int));

							int startIndex = binReader->ReadUint16();
							int objID = binReader->ReadUint16();
							for (int i = 0; i < entriesSize; i++)
								entries[i] = binReader->ReadInt32();

							gdi->SetPaletteEntries((IGdiPalette*)objs[objID], startIndex, entries);
							free(entries);
							break;
						}
						case (int)WmfConstants::RECORD_SET_BK_MODE:
						{
							int mode = binReader->ReadInt16();
							gdi->SetBkMode(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_MAP_MODE:
						{
							int mode = binReader->ReadInt16();
							gdi->SetMapMode(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_ROP2:
						{
							int mode = binReader->ReadInt16();
							gdi->SetROP2(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_REL_ABS:
						{
							int mode = binReader->ReadInt16();
							gdi->SetRelAbs(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_POLY_FILL_MODE:
						{
							int mode = binReader->ReadInt16();
							gdi->SetPolyFillMode(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_STRETCH_BLT_MODE:
						{
							int mode = binReader->ReadInt16();
							gdi->SetStretchBltMode(mode);
							break;
						}
						case (int)WmfConstants::RECORD_SET_TEXT_CHARACTER_EXTRA:
						{
							int extra = binReader->ReadInt16();
							gdi->SetTextCharacterExtra(extra);
							break;
						}
						case (int)WmfConstants::RECORD_RESTORE_DC:
						{
							int dc = binReader->ReadInt16();
							gdi->RestoreDC(dc);
							break;
						}
						case (int)WmfConstants::RECORD_RESIZE_PALETTE:
						{
							int objID = binReader->ReadUint16();
							gdi->ResizePalette((IGdiPalette*)objs[objID]);
							break;
						}
						case (int)WmfConstants::RECORD_DIB_CREATE_PATTERN_BRUSH:
						{
							int usage = binReader->ReadInt32();
							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->DibCreatePatternBrush(image, usage);
									objsType[i] = "Brush";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_SET_LAYOUT:
						{
							long layout = binReader->ReadUint32();
							gdi->SetLayout(layout);
							break;
						}
						case (int)WmfConstants::RECORD_SET_BK_COLOR:
						{
							int color = binReader->ReadInt32();
							gdi->SetBkColor(color);
							break;
						}
						case (int)WmfConstants::RECORD_SET_TEXT_COLOR:
						{
							int color = binReader->ReadInt32();
							gdi->SetTextColor(color);
							break;
						}
						case (int)WmfConstants::RECORD_OFFSET_VIEWPORT_ORG_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->OffsetViewportOrgEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_LINE_TO:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							gdi->LineTo(ex, ey);
							break;
						}
						case (int)WmfConstants::RECORD_MOVE_TO_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->MoveToEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_OFFSET_CLIP_RGN:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->OffsetClipRgn(x, y);
							break;
						}
						case (int)WmfConstants::RECORD_FILL_RGN:
						{
							int brushID = binReader->ReadUint16();
							int rgnID = binReader->ReadUint16();
							gdi->FillRgn((IGdiRegion*)objs[rgnID], (IGdiBrush*)objs[brushID]);
							break;
						}
						case (int)WmfConstants::RECORD_SET_MAPPER_FLAGS:
						{
							long flag = binReader->ReadUint32();
							gdi->SetMapperFlags(flag);
							break;
						}
						case (int)WmfConstants::RECORD_SELECT_PALETTE:
						{
							bool mode = (binReader->ReadInt16() != 0);
							if ((size * 2 - binReader->Count()) > 0)
							{
								int objID = binReader->ReadUint16();
								gdi->SelectPalette((IGdiPalette*)objs[objID], mode);
							}
							break;
						}
						case (int)WmfConstants::RECORD_POLYGON:
						{
							int pointSize = binReader->ReadInt16();
							vector<WMFConverter::Point*> points;	// = (WMFConverter::Point**)malloc(sizeof(WMFConverter::Point*) * pointSize);
							for (int i = 0; i < pointSize; i++)
							{
								short x = binReader->ReadInt16();
								short y = binReader->ReadInt16();
								points.push_back( new WMFConverter::Point(x, y));
							}

							gdi->Polygon(points);
							break;
						}
						case (int)WmfConstants::RECORD_POLYLINE:
						{
							int pointSize = binReader->ReadInt16();
							vector<WMFConverter::Point*> points;	// = new WMFConverter.gdi->Point[binReader->ReadInt16()];
							for (int i = 0; i < pointSize; i++)
							{
								short x = binReader->ReadInt16();	// C# �У�����������read���������ִ�С�C++�У��ұ���ִ�У����ֱ��ʹ�ûᵼ�� XY λ�û���
								short y = binReader->ReadInt16();
								points.push_back(new WMFConverter::Point(x, y));
							}
							gdi->Polyline(points);
							break;
						}
						case (int)WmfConstants::RECORD_SET_TEXT_JUSTIFICATION:
						{
							int breakCount = binReader->ReadInt16();
							int breakExtra = binReader->ReadInt16();
							gdi->SetTextJustification(breakExtra, breakCount);
							break;
						}
						case (int)WmfConstants::RECORD_SET_WINDOW_ORG_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->SetWindowOrgEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_SET_WINDOW_EXT_EX:
						{
							int height = binReader->ReadInt16();
							int width = binReader->ReadInt16();
							gdi->SetWindowExtEx(width, height, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_SET_VIEWPORT_ORG_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->SetViewportOrgEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_SET_VIEWPORT_EXT_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->SetViewportExtEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_OFFSET_WINDOW_ORG_EX:
						{
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->OffsetWindowOrgEx(x, y, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_SCALE_WINDOW_EXT_EX:
						{
							int yd = binReader->ReadInt16();
							int y = binReader->ReadInt16();
							int xd = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->ScaleWindowExtEx(x, xd, y, yd, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_SCALE_VIEWPORT_EXT_EX:
						{
							int yd = binReader->ReadInt16();
							int y = binReader->ReadInt16();
							int xd = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->ScaleViewportExtEx(x, xd, y, yd, NULL);
							break;
						}
						case (int)WmfConstants::RECORD_EXCLUDE_CLIP_RECT:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->ExcludeClipRect(sx, sy, ex, ey);
							break;
						}
						case (int)WmfConstants::RECORD_INTERSECT_CLIP_RECT:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->IntersectClipRect(sx, sy, ex, ey);
							break;
						}
						case (int)WmfConstants::RECORD_ELLIPSE:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->Ellipse(sx, sy, ex, ey);
							break;
						}
						case (int)WmfConstants::RECORD_FLOOD_FILL:
						{
							int color = binReader->ReadInt32();
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->FloodFill(x, y, color);
							break;
						}
						case (int)WmfConstants::RECORD_FRAME_RGN:
						{
							int height = binReader->ReadInt16();
							int width = binReader->ReadInt16();
							int brushID = binReader->ReadUint16();
							int rgnID = binReader->ReadUint16();
							gdi->FrameRgn((IGdiRegion*)objs[rgnID], (IGdiBrush*)objs[brushID], width, height);
							break;
						}
						case (int)WmfConstants::RECORD_ANIMATE_PALETTE:
						{
							int entriesSize = binReader->ReadUint16();
							int* entries = (int*)malloc(sizeof(int) * entriesSize);
							int startIndex = binReader->ReadUint16();
							int objID = binReader->ReadUint16();
							for (int i = 0; i < entriesSize; i++)
								entries[i] = binReader->ReadInt32();

							gdi->AnimatePalette((IGdiPalette*)objs[objID], startIndex, entries);
							free(entries);
							break;
						}
						case (int)WmfConstants::RECORD_TEXT_OUT:
						{
							int count = binReader->ReadInt16();
							char* text = binReader->ReadBytes(count);
							if (count % 2 == 1)
							{
								binReader->ReadByte();
							}
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->TextOut(x, y, text);
							break;
						}
						case (int)WmfConstants::RECORD_POLY_POLYGON:
						{
							vector<WMFConverter::Point*> points;	// = new WMFConverter.gdi->Point[][];
							points.clear();
							int sizeX = binReader->ReadInt16();

							int* sizeOfVector = (int*)malloc(sizeX * sizeof(int));	// ÿ��λ�洢���Ƕ�Ӧ�еĳ���

							for (int i = 0; i < sizeX; i++)
							{
								sizeOfVector[i]  = binReader->ReadInt16();								
							}

							for (int i = 0; i < sizeX; i++)
							{
								int sizeY = sizeOfVector[i];
								for (int j = 0; j < sizeY; j++)
								{
									if (j == 227)
									{
										//printf("AAAAAAAAA \r\n");
									}
									short x = binReader->ReadInt16();
									short y = binReader->ReadInt16();
									points.push_back(new WMFConverter::Point(x, y));
								}
							}

							gdi->PolyPolygon(points, sizeOfVector);
							free(sizeOfVector);
							break;
						}
						case (int)WmfConstants::RECORD_EXT_FLOOD_FILL:
						{
							int type = binReader->ReadUint16();
							int color = binReader->ReadInt32();
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->ExtFloodFill(x, y, color, type);
							break;
						}
						case (int)WmfConstants::RECORD_RECTANGLE:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->Rectangle(sx, sy, ex, ey);
							break;
						}
						case (int)WmfConstants::RECORD_SET_PIXEL:
						{
							int color = binReader->ReadInt32();
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->SetPixel(x, y, color);
							break;
						}
						case (int)WmfConstants::RECORD_ROUND_RECT:
						{
							int rh = binReader->ReadInt16();
							int rw = binReader->ReadInt16();
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->RoundRect(sx, sy, ex, ey, rw, rh);
							break;
						}
						case (int)WmfConstants::RECORD_PAT_BLT:
						{
							long rop = binReader->ReadUint32();
							int height = binReader->ReadInt16();
							int width = binReader->ReadInt16();
							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							gdi->PatBlt(x, y, width, height, rop);
							break;
						}
						case (int)WmfConstants::RECORD_SAVE_DC:
						{
							gdi->SeveDC();
							break;
						}
						case (int)WmfConstants::RECORD_PIE:
						{
							int eyr = binReader->ReadInt16();
							int exr = binReader->ReadInt16();
							int syr = binReader->ReadInt16();
							int sxr = binReader->ReadInt16();
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							gdi->Pie(sx, sy, ex, ey, sxr, syr, exr, eyr);
							break;
						}
						case (int)WmfConstants::RECORD_STRETCH_BLT:
						{
							long rop = binReader->ReadUint32();
							int sh = binReader->ReadInt16();
							int sw = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int dh = binReader->ReadInt16();
							int dw = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							gdi->StretchBlt(image, dx, dy, dw, dh, sx, sy, sw, sh, rop);
							break;
						}
						case (int)WmfConstants::RECORD_ESCAPE:
						{
							char* data = binReader->ReadBytes(2 * size);
							gdi->Escape(data);
							break;
						}
						case (int)WmfConstants::RECORD_INVERT_RGN:
						{
							int rgnID = binReader->ReadUint16();
							gdi->InvertRgn((IGdiRegion*)objs[rgnID]);
							break;
						}
						case (int)WmfConstants::RECORD_PAINT_RGN:
						{
							int objID = binReader->ReadUint16();
							gdi->PaintRgn((IGdiRegion*)objs[objID]);
							break;
						}
						case (int)WmfConstants::RECORD_SELECT_CLIP_RGN:
						{
							int objID = binReader->ReadUint16();
							IGdiRegion *rgn = (objID > 0) ? (IGdiRegion*)objs[objID] : NULL;
							gdi->SelectClipRgn(rgn);
							break;
						}
						case (int)WmfConstants::RECORD_SELECT_OBJECT:
						{
							int objID = binReader->ReadUint16();
							gdi->SelectObject(objs[objID], objsType[objID]);
							break;
						}
						case (int)WmfConstants::RECORD_SET_TEXT_ALIGN:
						{
							int align = binReader->ReadInt16();
							gdi->SetTextAlign(align);
							break;
						}
						case (int)WmfConstants::RECORD_ARC:
						{
							int eya = binReader->ReadInt16();
							int exa = binReader->ReadInt16();
							int sya = binReader->ReadInt16();
							int sxa = binReader->ReadInt16();
							int eyr = binReader->ReadInt16();
							int exr = binReader->ReadInt16();
							int syr = binReader->ReadInt16();
							int sxr = binReader->ReadInt16();
							gdi->Arc(sxr, syr, exr, eyr, sxa, sya, exa, eya);
							break;
						}
						case (int)WmfConstants::RECORD_CHORD:
						{
							int eya = binReader->ReadInt16();
							int exa = binReader->ReadInt16();
							int sya = binReader->ReadInt16();
							int sxa = binReader->ReadInt16();
							int eyr = binReader->ReadInt16();
							int exr = binReader->ReadInt16();
							int syr = binReader->ReadInt16();
							int sxr = binReader->ReadInt16();
							gdi->Chord(sxr, syr, exr, eyr, sxa, sya, exa, eya);
							break;
						}
						case (int)WmfConstants::RECORD_BIT_BLT:
						{
							long rop = binReader->ReadUint32();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int height = binReader->ReadInt16();
							int width = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							gdi->BitBlt(image, dx, dy, width, height, sx, sy, rop);
							break;
						}
						case (int)WmfConstants::RECORD_EXT_TEXT_OUT:
						{
							int rsize = size;

							int y = binReader->ReadInt16();
							int x = binReader->ReadInt16();
							int count = binReader->ReadInt16();
							int options = binReader->ReadUint16();
							rsize -= 4;

							int* rect = NULL;
							if ((options & 0x0006) > 0)
							{
								rect = (int*)malloc(4 * sizeof(int));
								for (int i = 0; i < 4; i++)
								{
									rect[i] = binReader->ReadInt16();
								}
								rsize -= 4;
							}
							char* text = binReader->ReadBytes(count);
							if (count % 2 == 1)
								binReader->ReadByte();

							rsize -= (count + 1) / 2;

							int* dx = NULL;
							if (rsize > 0)
							{
								dx = new int[rsize];
								dx = (int*)malloc(rsize * sizeof(int));
								for (int i = 0; i < rsize; i++)
									dx[i] = binReader->ReadInt16();
							}
							gdi->ExtTextOut(x, y, options, rect, text, dx);
							free(rect);
							free(dx);
							break;
						}
						case (int)WmfConstants::RECORD_SET_DIBITS_TO_DEVICE:
						{
							int colorUse = binReader->ReadUint16();
							int scanlines = binReader->ReadUint16();
							int startscan = binReader->ReadUint16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int dh = binReader->ReadInt16();
							int dw = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							gdi->SetDIBitsToDevice(dx, dy, dw, dh, sx, sy, startscan, scanlines, image, colorUse);
							break;
						}
						case (int)WmfConstants::RECORD_DIB_BIT_BLT:
						{
							bool isRop = false;

							long rop = binReader->ReadUint32();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int height = binReader->ReadInt16();
							if (height == 0)
							{
								height = binReader->ReadInt16();
								isRop = true;
							}
							int width = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							if (isRop)
								gdi->DibBitBlt(NULL, dx, dy, width, height, sx, sy, rop);
							else
							{
								char* image = binReader->ReadBytes(size * 2 - binReader->Count());

								gdi->DibBitBlt(image, dx, dy, width, height, sx, sy, rop);
							}
							break;
						}
						case (int)WmfConstants::RECORD_DIB_STRETCH_BLT:
						{
							long rop = binReader->ReadUint32();
							int sh = binReader->ReadInt16();
							int sw = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int dh = binReader->ReadInt16();
							int dw = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							gdi->DibStretchBlt(image, dx, dy, dw, dh, sx, sy, sw, sh, rop);
							break;
						}
						case (int)WmfConstants::RECORD_STRETCH_DIBITS:
						{
							long rop = binReader->ReadUint32();
							int usage = binReader->ReadUint16();
							int sh = binReader->ReadInt16();
							int sw = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							int dh = binReader->ReadInt16();
							int dw = binReader->ReadInt16();
							int dy = binReader->ReadInt16();
							int dx = binReader->ReadInt16();

							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							gdi->StretchDIBits(dx, dy, dw, dh, sx, sy, sw, sh, image, usage, rop);
							break;
						}
						case (int)WmfConstants::RECORD_DELETE_OBJECT:
						{
							int objID = binReader->ReadUint16();
							gdi->DeleteObject(objs[objID]);
							objsType[objID] = "";
							objs[objID] = NULL;
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_PALETTE:
						{
							int version = binReader->ReadUint16();
							int entriesSize = binReader->ReadUint16();
							int* entries = new int[entriesSize];
							for (int i = 0; i < entriesSize; i++)
								entries[i] = binReader->ReadInt32();


							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->CreatePalette(version, entries);
									objsType[i] = "Palette";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_PATTERN_BRUSH:
						{
							char* image = binReader->ReadBytes(size * 2 - binReader->Count());

							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->CreatePatternBrush(image);
									objsType[i] = "Brush";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_PEN_INDIRECT:
						{
							int style = binReader->ReadUint16();
							int width = binReader->ReadInt16();
							binReader->ReadInt16();
							int color = binReader->ReadInt32();
							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->CreatePenIndirect(style, width, color);
									objsType[i] = "Pen";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_FONT_INDIRECT:
						{
							int height = binReader->ReadInt16();
							int width = binReader->ReadInt16();
							int escapement = binReader->ReadInt16();
							int orientation = binReader->ReadInt16();
							int weight = binReader->ReadInt16();
							bool italic = (binReader->ReadByte() == 1);
							bool underline = (binReader->ReadByte() == 1);
							bool strikeout = (binReader->ReadByte() == 1);
							int charset = binReader->ReadByte();
							int outPrecision = binReader->ReadByte();
							int clipPrecision = binReader->ReadByte();
							int quality = binReader->ReadByte();
							int pitchAndFamily = binReader->ReadByte();
							char* faceName = binReader->ReadBytes(size * 2 - binReader->Count());

							IGdiObject *obj = gdi->CreateFontIndirect(height, width, escapement, orientation, weight, italic,
								underline, strikeout, charset, outPrecision, clipPrecision, quality, pitchAndFamily,
								faceName);

							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = obj;
									objsType[i] = "Font";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_BRUSH_INDIRECT:
						{
							int style = binReader->ReadUint16();
							int color = binReader->ReadInt32();
							int hatch = binReader->ReadUint16();
							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->CreateBrushIndirect(style, color, hatch);
									objsType[i] = "Brush";
									break;
								}
							}
							break;
						}
						case (int)WmfConstants::RECORD_CREATE_RECT_RGN:
						{
							int ey = binReader->ReadInt16();
							int ex = binReader->ReadInt16();
							int sy = binReader->ReadInt16();
							int sx = binReader->ReadInt16();
							for (int i = 0; i < objs.size(); i++)
							{
								if (objs[i] == NULL)
								{
									objs[i] = gdi->CreateRectRgn(sx, sy, ex, ey);
									objsType[i] = "Rgn";
									break;
								}
							}
							break;
						}
						default:
						{
							//log.fine("unsuppored id find: " + id + " (size=" + size + ")");
							//Console.Write();
							printf("unsuppored id find: %d (size= %d) \r\n", id, size);
							break;
						}
						}
						static int cnt = 0;
						//printf("now run time = %d, id = %d \r\n", cnt,id);
						cnt++;
						int rest = size * 2 - binReader->Count();
						for (int i = 0; i < rest; i++)
						{
							binReader->ReadByte();
						}
					}
					binReader->Close();

					gdi->Footer();
				}
				catch (exception ee)
				{
					printf("wmfparser error line 878: %s \r\n", ee.what());
					if (isEmpty)
						throw ("input file size is zero.");
				}
			}

		};
	}
}


#endif
