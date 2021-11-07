#ifndef _BASE64_H_
#define _BASE64_H_

#include <string>
using namespace std;
namespace WMFConverter{
	namespace Util{
		class Base64
		{
		public:
			/// Encode byte array.
			static string Encode(char* data)
			{
				char* buffer = NULL;
				int size = sizeof(data);
				if (size % 3 == 0)
					buffer = new char[size / 3 * 4];
				else
					buffer = new char[(size / 3 + 1) * 4];


				int buf = 0;
				for (int i = 0; i < size; i++)
				{
					switch (i % 3)
					{
					case 0:
						buffer[i / 3 * 4] = ENCODE_DATA[(data[i] & 0xFC) >> 2];
						buf = (data[i] & 0x03) << 4;
						if (i + 1 == size)
						{
							buffer[i / 3 * 4 + 1] = ENCODE_DATA[buf];
							buffer[i / 3 * 4 + 2] = '=';
							buffer[i / 3 * 4 + 3] = '=';
						}
						break;
					case 1:
						buf += (data[i] & 0xF0) >> 4;
						buffer[i / 3 * 4 + 1] = ENCODE_DATA[buf];
						buf = (data[i] & 0x0F) << 2;
						if (i + 1 == size)
						{
							buffer[i / 3 * 4 + 2] = ENCODE_DATA[buf];
							buffer[i / 3 * 4 + 3] = '=';
						}
						break;
					case 2:
						buf += (data[i] & 0xC0) >> 6;
						buffer[i / 3 * 4 + 2] = ENCODE_DATA[buf];
						buffer[i / 3 * 4 + 3] = ENCODE_DATA[data[i] & 0x3F];
						break;
					}
				}

				return string(buffer);
			}

		private:
			static char ENCODE_DATA[64]; 
		};


		char Base64::ENCODE_DATA[64]= {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9', '+', '/'
		};

	}
}







#endif