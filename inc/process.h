/*
 * @Author: your name
 * @Date: 2021-06-04 09:10:20
 * @LastEditTime: 2021-06-07 01:40:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/inc/process.h
 */
#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <vector>
#include <iostream>
#include "data.h"
using namespace std;

//分割初始输入
vector<string> Cut(string);

//判断赋值表达式(变量直接赋值)
bool check_eva_1(string);

//判断赋值表达式(变量为表达式)
bool check_eva_2(string);

//求值（！！！！！！！！！！！！！！！）
double get_value(string, vector<var>, vector<fun>);

//检查是否为求值命令
bool check_get(string);

//计算单个变量
double get_single_eng(string, vector<var>, vector<fun>);

void show_var(vector<var>);

//判断函数定义
bool check_eva_3(string);

//增加函数
vector<fun> add_fun(vector<fun>, string);

void show_fun(vector<fun>);

//计算单一函数值
double get_fun(string, vector<var>, vector<fun>);

//判断表达式格式
bool check_form(string);

//三目运算的转化
string tran_2(string str, vector<var>, vector<fun>);

//展现历史
void show_his(vector<history>, vector<var>, vector<fun>);

//绝对值运算
string tran_3(string, vector<var>, vector<fun>);
#endif