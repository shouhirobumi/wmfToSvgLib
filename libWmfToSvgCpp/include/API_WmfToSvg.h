#ifndef _API_WMFTOSVG_H_
#define _API_WMFTOSVG_H_

///!
// function:	wmfתsvgת���ӿں���
// param:		input, ��Ҫת��� wmf �ļ���
// param:		output, ת����FILE�ļ��������ļ����ڵ��ú������
// return:		�������� 0 ,�ļ���д����� ���� -1, ת����󣬷��� -2
///!
extern "C" int inputWmfFile(const char* input, void* output);


#endif