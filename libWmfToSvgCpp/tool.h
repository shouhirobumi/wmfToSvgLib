#ifndef  _TOOL_H_
#define _TOOL_H_

#include <string>

inline double stringToDouble(std::string num)
{
    bool minus = false;      //����Ƿ��Ǹ���  
	std::string real = num;       //real��ʾnum�ľ���ֵ
    if (num[0] == '-')
    {
        minus = true;
        real = num.substr(1, num.size()-1);
    }

    char c;
    int i = 0;
    double result = 0.0 , dec = 10.0;
    bool isDec = false;       //����Ƿ���С��
    unsigned long size = real.size();
    while(i < size)
    {
        c = real.at(i);
        if (c == '.')
        {//����С��
            isDec = true;
            i++;
            continue;
        }
        if (!isDec) 
        {
           result = result*10 + c - '0';
        }
        else
        {//ʶ��С����֮�󶼽��������֧
            result = result + (c - '0')/dec;
            dec *= 10;
        }
        i++;
    }

    if (minus == true) {
        result = -result;
    }
 
    return result;
}

inline std::string doubleToString(double num)
{
	char str[256];
	sprintf(str, "%lf", num);
	std::string result = str;
	return result;
}

inline std::string intToString(int num)
{
	char str[256];
	sprintf(str, "%d", num);
	std::string result = str;
	return result;
}


inline unsigned int stringGetHashCode(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str){
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}




#endif