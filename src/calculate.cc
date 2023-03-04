/*
 * @Author: your name
 * @Date: 2021-06-04 09:11:15
 * @LastEditTime: 2021-06-08 17:00:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/src/calculate.cc
 */
#include "../inc/calculate.h"

#include <iostream>
#include <math.h>
using namespace std;

//计算单个数值
double get_single_num(string str)
{
    double a = 0;
    if (check_dot(str))
    {
        for (int i = str.size() - 1, j = 0; i >= 0; i--, j++)
            a += (str[j] - 48) * pow(10, i);
    }
    else
    {
        string b = str.substr(0, str.find("."));
        string l = str.substr(str.find(".") + 1, str.size() - str.find(".") - 1);
        for (int i = b.size() - 1, j = 0; i >= 0; i--, j++)
            a += (b[j] - 48) * pow(10, i);

        for (int i = 0; i <= l.size() - 1; i++)
            a += (l[i] - 48) * pow(10, -i - 1);
    }
    return a;
}

