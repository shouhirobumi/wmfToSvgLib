#ifndef _WMF_OBJECT_H_
#define _WMF_OBJECT_H_

namespace WMFConverter{
	namespace Wmf{
		class WmfObject
		{
		public:
			WmfObject(int id){
				_id = id;
			}

			int Id()
			{
				return _id;
			}
		private:
			int _id;
		};
	}
}


#endif