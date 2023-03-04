/*
 * @Author: your name
 * @Date: 2021-06-02 21:13:02
 * @LastEditTime: 2021-06-02 21:47:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/inc/data.h
 */
#ifndef _DATA_H_
#define _DATA_H_
#include <iostream>
#include <vector>
using namespace std;

struct var
{
    bool con;
    string name;
    double value;
    string exp;
};

struct fun
{
    string name;
    string exp;
    vector<string> unknown;
};

struct history
{
    string order;
    string result="done!";
    double n=777;
};

#endif