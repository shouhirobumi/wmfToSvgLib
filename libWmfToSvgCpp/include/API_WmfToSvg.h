#ifndef _API_WMFTOSVG_H_
#define _API_WMFTOSVG_H_

///!
// function:	wmf转svg转码库接口函数
// param:		input, 需要转码的 wmf 文件名
// param:		output, 转码后的FILE文件流，此文件流在调用函数里打开
// return:		正常返回 0 ,文件流写入错误 返回 -1, 转码错误，返回 -2
///!
extern "C" int inputWmfFile(const char* input, void* output);


#endif