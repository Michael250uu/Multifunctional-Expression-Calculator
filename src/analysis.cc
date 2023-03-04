/*
 * @Author: your name
 * @Date: 2021-06-04 09:11:51
 * @LastEditTime: 2021-06-14 19:18:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/src/analysis.cc
 */
#include "../inc/analysis.h"

//---------------------------------------------------------------------判断是否全为字母
bool check_fulle(string str)
{
    if (str.size() < 1)
        return 0;
    for (string::iterator it = str.begin(); it < str.end(); it++)
        if (!((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z')))
            return 0;
    return 1;
}

//------------------------------------------------------------------------判断是否全无字母
bool check_num(string str)
{
    if (str.size() < 1)
        return 0;
    for (string::iterator it = str.begin(); it < str.end(); it++)
        if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))
            return 0;
    return 1;
}

//-------------------------------------------------------------------------判断常数是否含有小数点
bool check_dot(string str)
{
    for (string::iterator it = str.begin(); it < str.end(); it++)
        if (*it == '.')
            return 0;
    return 1;
}

//----------------------------------------------------------------------------判断是否全为数字
bool check_all_num(string str)
{
    for (string::iterator it = str.begin(); it < str.end(); it++)
        if ((*it < '0' || *it > '9') && *it != '.')
            return 0;
    return 1;
}

//----------------------------------------------------------------------------判断是否为单一函数
bool check_func(string str)
{
    if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
        return 0;
    for (string::iterator it = str.begin(); it < str.end(); it++)
    {
        if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
            return 0;
        if (((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z')) && *(it + 1) == '(')
        {
            int n = 1;
            for (string::iterator j = it + 2; j < str.end(); j++)
            {
                if (*j == '(')
                    n++;
                if (*j == ')')
                    n--;
                if (n == 0 && (j + 1) == str.end())
                    return 1;
                if (n == 0 && (j + 1) != str.end())
                    return 0;
            }
        }
    }
}

//--------------------------------------------------------------------------------检测加减号是否规范
bool check_pm(string str)
{
    if (*(str.end() - 1) == '+' || *(str.end() - 1) == '-')
        return 0;
    for (int i = 0; i + 1 < str.size(); i++)
        if ((str[i] == '+' || str[i] == '-') && str[i + 1] == ')')
            return 0;
    return 1;
}

//------------------------------------------------------------------------------将加减转化
string tran(string str)
{
    int i = 0;
    for (; i + 1 < str.size(); i++)
    {

        if ((str[i] == '+' || str[i] == '-') && (str[i + 1] == '+' || str[i + 1] == '-'))
        { //cout<<"k\n";
            int b = i;
            int n = 0, flag1, flag2;
            for (; str[i] == '+' || str[i] == '-'; i++)
                if (str[i] == '-')
                    n++;
            if (n % 2 == 0)
                flag1 = 0; //加法
            else
                flag1 = 1; //剑法

            if (b == 0)
                flag2 = 0;
            else if (str[b - 1] == '(')
                flag2 = 0; //需要补0
            else
                flag2 = 1; //不需要补0
            int len = i - b;
            if (flag2 == 0)
            {
                if (flag1 == 0)
                    str.replace(b, len, "0+");
                else
                    str.replace(b, len, "0-");
            }
            else
            {
                if (flag1 == 0)
                    str.replace(b, len, "+");
                else
                    str.replace(b, len, "-");
            }
            i = 0;
        }
    }
    if (*str.begin() == '+' || *str.begin() == '-')
        str = '0' + str;
    for (int i = 0; i + 1 < str.size(); i++)
    {
        if (str[i] == '(' && (str[i + 1] == '+' || str[i + 1] == '-'))
        {
            str.replace(i, 1, "(0");
            i = 0;
        }
    }

    return str;
}