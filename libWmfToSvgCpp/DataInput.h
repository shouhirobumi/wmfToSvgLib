#ifndef _IO_DATA_INPUT_H_
#define _IO_DATA_INPUT_H_

#include <iostream> 
#include <fstream>  
#include <memory.h>

using namespace std;

namespace WMFConverter{

//#define USE_CPP_IOSTREAM		//是否使用C++的 ifstreeam进行读写

	
		enum BitConverter
		{
			IsLittleEndian = 0,
			IsBigEndian = 1
		};




		/// Read input stream of wmf file.
		class DataInput
		{
		private:
			string fileName;
			FILE *fp;
			
			
			ifstream *_inputStream;
			bool _isLittleEndian ;
			char _buf [4];
			int _count ;

			long hasRead ;

			void dataInitial(){
				fileName = "";
				fp = NULL;
				_isLittleEndian = (bool)IsLittleEndian;
				_buf[4];
				memset(_buf, 0x00, sizeof(_buf));
				_count = 0;
				hasRead = 0;
			}

		public:
			/// Represents the count of bytes read
			int Count(){
				return _count;
			}
			void setCount(int val){
				_count = val; 
			}

			long HasRead(){
				return hasRead;
			}

			/// Default constructor.
			/// Create a DataInput instance using native order.
			DataInput(ifstream *inputStream)
			{
				dataInitial();
				_isLittleEndian = (bool)IsLittleEndian;
				_inputStream = inputStream;
			}

			DataInput(string file, bool endian){
				fileName = file;
				_isLittleEndian = endian;
				fp = fopen(fileName.c_str(), "rb");
			}

			/// Default contructor.
			/// Create a DataInput instance receving the order.
			DataInput(ifstream *inputStream, bool endian)
			{
				dataInitial();
				_inputStream = inputStream;
				_isLittleEndian = endian;
			}

			/// Reads the next one byte of this input stream as a signed 8-bit integer.
			int ReadByte()
			{
				memset(_buf, 0x00, sizeof(_buf));
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();
				if (_inputStream->read(_buf, 1))
				{
					_count += 1;
					hasRead++;
					return (0xff & _buf[0]);
				}
#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (1 == fread(_buf, 1, 1, fp)){
						_count += 1;
						hasRead++;
						return (0xff & _buf[0]);
					}
				}
#endif
			}

			/// Reads the next two bytes of this input stream as a signed 16-bit integer.
			int ReadInt16()
			{
				memset(_buf, 0x00, sizeof(_buf));
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();
				if (_inputStream->read(_buf, 2) )
				{
					short value = 0;
					if (_isLittleEndian == false)
					{
						value |= (short)(0xff & _buf[1]);
						value |= (short)((0xff & _buf[0]) << 8);
					}
					else
					{
						value |= (short)(0xff & _buf[0]);
						value |= (short)((0xff & _buf[1]) << 8);
					}
					_count += 2;
					hasRead += 2;
					return value;
				}
#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (2 == fread(_buf, 1, 2, fp)){
						short value = 0;
						if (_isLittleEndian == false)
						{
							value |= (short)(0xff & _buf[1]);
							value |= (short)((0xff & _buf[0]) << 8);
						}
						else
						{
							value |= (short)(0xff & _buf[0]);
							value |= (short)((0xff & _buf[1]) << 8);
						}
						_count += 2;
						hasRead += 2;
						return value;
					}
				}
#endif
			}

			/// Reads the next four bytes of this input stream as a signed 32-bit integer.
			int ReadInt32()
			{
				memset(_buf, 0x00, sizeof(_buf));
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();
				if (_inputStream->read(_buf, 4) )
				{
					int value = 0;
					if (_isLittleEndian == false)
					{
						value |= (0xff & _buf[3]);
						value |= (0xff & _buf[2]) << 8;
						value |= (0xff & _buf[1]) << 16;
						value |= (0xff & _buf[0]) << 24;
					}
					else
					{
						value |= (0xff & _buf[0]);
						value |= (0xff & _buf[1]) << 8;
						value |= (0xff & _buf[2]) << 16;
						value |= (0xff & _buf[3]) << 24;
					}
					_count += 4;
					hasRead += 4;
					return value;
				}
#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (4 == fread(_buf, 1, 4, fp)){
						int value = 0;
						if (_isLittleEndian == false)
						{
							value |= (0xff & _buf[3]);
							value |= (0xff & _buf[2]) << 8;
							value |= (0xff & _buf[1]) << 16;
							value |= (0xff & _buf[0]) << 24;
						}
						else
						{
							value |= (0xff & _buf[0]);
							value |= (0xff & _buf[1]) << 8;
							value |= (0xff & _buf[2]) << 16;
							value |= (0xff & _buf[3]) << 24;
						}
						_count += 4;
						hasRead += 4;
						return value;
					}
				}
#endif
			}

			/// Reads the next two bytes of this input stream as a unsigned 16-bit integer.
			int ReadUint16()
			{
				memset(_buf, 0x00, sizeof(_buf));
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();
				if (_inputStream->read(_buf, 2))
				{
					int value = 0;
					if (_isLittleEndian == false)
					{
						value |= (0xff & _buf[1]);
						value |= (0xff & _buf[0]) << 8;
					}
					else {
						value |= (0xff & _buf[0]);
						value |= (0xff & _buf[1]) << 8;
					}
					_count += 2;
					hasRead += 2;
					return value;
				}
#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (2 == fread(_buf, 1, 2, fp)){
						int value = 0;
						if (_isLittleEndian == false)
						{
							value |= (0xff & _buf[1]);
							value |= (0xff & _buf[0]) << 8;
						}
						else {
							value |= (0xff & _buf[0]);
							value |= (0xff & _buf[1]) << 8;
						}
						_count += 2;
						hasRead += 2;
						return value;
					}
				}
#endif
			}

			/// Reads the next four bytes of this input stream as a unsigned 32-bit integer.
			long ReadUint32()
			{
				memset(_buf, 0x00, sizeof(_buf));
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();
				if (_inputStream->read(_buf, 4))
				{
					long value = 0;
					if (_isLittleEndian == false)
					{
						value |= (0xff & _buf[3]);
						value |= (0xff & _buf[2]) << 8;
						value |= (0xff & _buf[1]) << 16;
						value |= (0xff & _buf[0]) << 24;
					}
					else
					{
						value |= (0xff & _buf[0]);
						value |= (0xff & _buf[1]) << 8;
						value |= (0xff & _buf[2]) << 16;
						value |= (0xff & _buf[3]) << 24;
					}
					_count += 4;
					hasRead += 4;
					return value;
				}
#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (4 == fread(_buf, 1, 4, fp)){
						long value = 0;
						if (_isLittleEndian == false)
						{
							value |= (0xff & _buf[3]);
							value |= (0xff & _buf[2]) << 8;
							value |= (0xff & _buf[1]) << 16;
							value |= (0xff & _buf[0]) << 24;
						}
						else
						{
							value |= (0xff & _buf[0]);
							value |= (0xff & _buf[1]) << 8;
							value |= (0xff & _buf[2]) << 16;
							value |= (0xff & _buf[3]) << 24;
						}
						_count += 4;
						hasRead += 4;
						return value;
					}
				}
#endif
			}

			/// Reads the next n bytes.
			char* ReadBytes(int n)
			{
				char* array = (char*)malloc(n);
#ifdef USE_CPP_IOSTREAM
				long curpos = _inputStream->tellg();

				if (_inputStream->read(array, n))
				{
					_count += n;
					hasRead += n;
					return array;
				}

#else
				if (fp != NULL){
					long curpos = ftell(fp);
					if (4 == fread(array, 1, 4, fp)){
						_count += n;
						hasRead += n;
					}
				}
#endif
				return array;
			}


			/// Close the input stream.
			void Close()
			{
				try
				{
#ifdef USE_CPP_IOSTREAM
					_inputStream->close();
#else
					if (fp != NULL)
					{
						fclose(fp);
					}
#endif
				}
				catch (exception ex)
				{
					printf("datainput error line 206: %s \r\n",ex.what());
				}
			}
		};

}



#endif
