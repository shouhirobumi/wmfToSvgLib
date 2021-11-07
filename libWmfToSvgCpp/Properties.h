#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <map>
using namespace std;

namespace WMFConverter{
	
		class Properties //: public map<string,string>
		{
		public:
			Properties();
			string findVal(string val);
			void load();

		private:
			map<string, string> dictMap;
		};
	
}

#endif	//_PROPERTIES_H_