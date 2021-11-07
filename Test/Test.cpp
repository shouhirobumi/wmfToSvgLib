// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include "API_WmfToSvg.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	FILE *fp = NULL;

	string input = "e://bird.wmf";
	fopen_s(&fp, "e://aaa.svg", "w+");

	if (fp)
	{
		ret = inputWmfFile(input.c_str(), fp);
	}
	fclose(fp);

	printf("convert wmf to svg ret = %d \r\n", ret);
	return 0;
}

