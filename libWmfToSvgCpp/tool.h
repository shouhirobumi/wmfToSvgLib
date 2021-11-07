#ifndef  _TOOL_H_
#define _TOOL_H_

#include <string>

inline double stringToDouble(std::string num)
{
    bool minus = false;      //标记是否是负数  
	std::string real = num;       //real表示num的绝对值
    if (num[0] == '-')
    {
        minus = true;
        real = num.substr(1, num.size()-1);
    }

    char c;
    int i = 0;
    double result = 0.0 , dec = 10.0;
    bool isDec = false;       //标记是否有小数
    unsigned long size = real.size();
    while(i < size)
    {
        c = real.at(i);
        if (c == '.')
        {//包含小数
            isDec = true;
            i++;
            continue;
        }
        if (!isDec) 
        {
           result = result*10 + c - '0';
        }
        else
        {//识别小数点之后都进入这个分支
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