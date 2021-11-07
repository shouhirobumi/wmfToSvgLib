#ifndef _IGDI_SIZE_H_
#define _IGDI_SIZE_H_

#include <string>

namespace WMFConverter{

		/// Represents a size object.
		class Size
		{
		public:
			/// Width of the object.
			int Width;
			/// Height of the object.
			int Height;

			/// Default constructor.
			Size(int width, int height)
			{
				Width = width;
				Height = height;
			}

			/// Serves as the default hash function.
			int GetHashCode(){
				int prime = 31;
				int result = 1;
				result = prime * result + Height;
				result = prime * result + Width;
				return result;
			}

			/// Determines whether the specified object is equal to the current object.
			bool Equals(Size *obj){
				if (this == obj)
					return true;
				if (obj == NULL)
					return false;
				if (Height != obj->Height)
					return false;
				if (Width != obj->Width)
					return false;
				return true;
			}

			/// Returns a string that represents the current object.
			std::string ToString()
			{
				char str[100] = {};
				sprintf(str, "Size [width = %d, height = %d ]", Width, Height);
				return (std::string)str;
			}

		};

}

#endif //_IGDI_SIZE_H_