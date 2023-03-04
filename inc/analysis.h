/*
 * @Author: your name
 * @Date: 2021-06-04 09:11:40
 * @LastEditTime: 2021-06-10 20:16:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/inc/analysis.h
 */
#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include<iostream>
using namespace std;

//判断是否全为字母
bool check_fulle(string);

//判断是否无字母
bool check_num(string);

//判断常数是否含有小数点
bool check_dot(string);

//判断是否全为数字
bool check_all_num(string);

//判断是否为单一函数
bool check_func(string);

//检测加减号是否规范
bool check_pm(string);

//将加减转化
string tran(string);




#endif