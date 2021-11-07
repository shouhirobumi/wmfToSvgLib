#ifndef _WMF_PARSE_EXCEPTION_H_
#define _WMF_PARSE_EXCEPTION_H_

#include <exception>

#include <string>
using namespace std;

namespace WMFConverter{
	namespace Wmf{

		class WmfParseException : public Exception
		{
		public:
			WmfParseException()
				:Exception()
			{

			}

			WmfParseException(string message)
				: Exception(message)
			{

			}

			WmfParseException(string message, Exception t)
				: Exception(message, t)
			{

			}

		};
	}

}


#endif