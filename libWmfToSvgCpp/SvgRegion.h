#ifndef _SVG_REGION_H_
#define _SVG_REGION_H_

#include "SvgObject.h"
#include "IGdiRegion.h"
#include "tinyxml2.h"



namespace WMFConverter{

		class SvgGdi;
		//class SvgObject;
		//class IGdiRegion;

		class SvgRegion : public SvgObject, public IGdiRegion
		{
		public:
			SvgRegion(SvgGdi* gdi);

			virtual tinyxml2::XMLElement *CreateElement(){
				return NULL;
			};
		};

}

#endif






