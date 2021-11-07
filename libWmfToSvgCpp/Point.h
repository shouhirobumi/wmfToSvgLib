#ifndef _IGDI_POINT_H_
#define _IGDI_POINT_H_

#include <string>
#include <stdio.h>

namespace WMFConverter{

		/// Represents a point (x,y).
		class Point
		{
		public:
	
			/// Default constructor.
			Point(int x, int y){
				X = x;
				Y = y;
			}
			int X;
			int Y;
			/// Serves as the default hash function.
			int GetHashCode(){
				int prime = 31;
				int result = 1;
				result = prime * result + X;
				result = prime * result + Y;
				return result;
			}

			/// Determines whether the specified object is equal to the current object.
			bool Equals(Point *obj){
				if (this == obj)
					return true;
				if (obj == NULL)
					return false;
				if (X != obj->X)
					return false;
				if (Y != obj->Y)
					return false;
				return true;
			}

			/// Returns a string that represents the current object.
			std::string ToString()
			{
				char str[100] = {};
				sprintf(str, "Point [x= %d, y = %d ]",X,Y);
				return (std::string)str;
			}

		};
}

#endif