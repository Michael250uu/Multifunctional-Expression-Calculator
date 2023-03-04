/*
 * @Author: your name
 * @Date: 2021-06-04 09:25:09
 * @LastEditTime: 2021-06-17 20:18:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/src/process.cc
 */
#include "../inc/process.h"
#include "../inc/analysis.h"
#include "../inc/calculate.h"
#include <sstream>
#include <iostream>
using namespace std;

//----------------------------------------------------------求值（！！！！！！！！！！！！！！！）
double get_value(string exper, vector<var> vars, vector<fun> funs)
{

    if (check_pm(exper) == 0)
        return 999997;
    exper = tran(exper); //加减号的转化
    //cout << exper<<endl;
    exper = tran_2(exper, vars, funs);
    exper = tran_3(exper, vars, funs);
    //cout << exper << endl;
    if (check_form(exper) == 0)
        return 999997;
    //cout << "h\n";
    double result;

    //---------------------单独一个数

    if (check_all_num(exper))
        return get_single_num(exper);

    //---------------------单独一个变量
    if (check_fulle(exper))
        return get_single_eng(exper, vars, funs);

    //---------------------单独一个函数
    if (check_func(exper))
    {
        return get_fun(exper, vars, funs);
        //return 8;
    }

    //----------------------------------------------------存在二元运算
    int pos = 0;
    for (; pos <= exper.size() - 1;)
    {
        if ((exper[pos] >= '0' && exper[pos] <= '9') || exper[pos] == '.') //以数字开头
        {
            string temp;
            for (;; pos++)
                if ((exper[pos] >= '0' && exper[pos] <= '9') || exper[pos] == '.')
                    temp += exper[pos];
                else //pos到了符号
                    break;
            result = get_value(temp, vars, funs);
        }

        else if (exper[pos] == '(') //以括号开头
        {
            int num = 1;
            pos++;
            string temp;
            for (; pos <= exper.size() - 1; pos++)
            {
                if (exper[pos] == '(')
                    num++;
                if (exper[pos] == ')')
                    num--;
                if (num == 0)
                {
                    pos++;
                    if (get_value(temp, vars, funs) == 999997)
                    {
                        return 999997;
                    }
                    result = get_value(temp, vars, funs);
                    break;
                }
                temp += exper[pos];
            }
        }

        else if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z')) //以函数/变量开头
        {
            //cout << "hhh";
            bool flag;
            for (int t = pos;; t++)
            {
                if (exper[t] == '(') //函数开头
                {
                    flag = 1;
                    break;
                }
                else if (exper[t] == '+' || exper[t] == '-' || exper[t] == '*' || exper[t] == '/') //变量开头
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
            {
                string temp;
                for (;; pos++)
                    if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
                        temp += exper[pos];
                    else //pos到了符号
                        break;
                if (get_value(temp, vars, funs) == 999997)
                    return 999997;
                result = get_value(temp, vars, funs);
            }
            else //函数开头
            {
                int n = exper.find("(");
                string temp = exper.substr(0, n + 1);
                int t = 1;
                pos = n + 1;
                for (;; pos++)
                {
                    if (exper[pos] == '(')
                        t++;
                    if (exper[pos] == ')')
                        t--;
                    temp += exper[pos];
                    if (t == 0)
                    {
                        pos++;
                        //cout<<temp<<endl;break;
                        double y = get_value(temp, vars, funs);
                        if (y == 999997)
                            return 999997;
                        result = y;
                        break;
                    }
                }
            }
        }

        else if (exper[pos] == '*') //遇到乘号
        {
            pos++;
            if (exper[pos] >= '0' && exper[pos] <= '9') //后面是数字
            {
                string temp;
                for (; pos <= exper.size() - 1; pos++)
                    if ((exper[pos] >= '0' && exper[pos] <= '9') || exper[pos] == '.')
                        temp += exper[pos];
                    else //pos到了符号
                        break;

                result *= get_value(temp, vars, funs);
            }

            else if (exper[pos] == '(') //后面是括号
            {
                int num = 1;
                pos++;
                string temp;
                for (; pos <= exper.size() - 1; pos++)
                {
                    if (exper[pos] == '(')
                        num++;
                    if (exper[pos] == ')')
                        num--;
                    if (num == 0)
                    {
                        pos++;
                        if (get_value(temp, vars, funs) == 999997)
                        {
                            return 999997;
                        }
                        result *= get_value(temp, vars, funs);
                        break;
                    }
                    temp += exper[pos];
                }
            }

            else if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
            {
                bool flag;
                int t = pos;
                for (; t <= exper.size() - 1; t++)
                {
                    if (exper[t] == '(')
                    {
                        flag = 1;
                        break;
                    }
                    if (exper[t] == '+' || exper[t] == '-' || exper[t] == '*' || exper[t] == '/')
                    {
                        flag = 0;
                        break;
                    }
                }
                if (t == exper.size())
                    flag = 0;
                if (flag == 0) //后面是变量
                {
                    string temp;
                    for (; pos <= exper.size() - 1; pos++)
                        if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
                            temp += exper[pos];
                        else //pos到了符号
                            break;
                    double x = get_value(temp, vars, funs);
                    if (x == 999997)
                        return 999997;
                    result *= x;
                }
                else //函数
                {
                    string temp;
                    int n = exper.find("(", pos);
                    temp = exper.substr(pos, n - pos + 1);
                    pos = n + 1;
                    int t = 1;
                    for (;; pos++)
                    {
                        if (exper[pos] == '(')
                            t++;
                        if (exper[pos] == ')')
                            t--;
                        temp += exper[pos];
                        if (t == 0)
                        {
                            pos++;
                            //cout<<temp<<endl;break;
                            double y = get_value(temp, vars, funs);
                            if (y == 999997)
                                return 999997;
                            result *= y;
                            break;
                        }
                    }
                }
            }
        }

        else if (exper[pos] == '/') //遇到除号
        {
            pos++;
            if (exper[pos] >= '0' && exper[pos] <= '9') //后面是数字
            {
                string temp;
                for (; pos <= exper.size() - 1; pos++)
                    if ((exper[pos] >= '0' && exper[pos] <= '9') || exper[pos] == '.')
                        temp += exper[pos];
                    else //pos到了符号
                        break;

                if (get_value(temp, vars, funs) == 0)
                {
                    return 999997;
                }

                result /= get_value(temp, vars, funs);
            }

            else if (exper[pos] == '(') //后面是括号
            {
                int num = 1;
                pos++;
                string temp;
                for (; pos <= exper.size() - 1; pos++)
                {
                    if (exper[pos] == '(')
                        num++;
                    if (exper[pos] == ')')
                        num--;
                    if (num == 0)
                    {
                        pos++;
                        if (get_value(temp, vars, funs) == 999997 || get_value(temp, vars, funs) == 0)
                            return 999997;
                        result /= get_value(temp, vars, funs);
                        break;
                    }
                    temp += exper[pos];
                }
            }

            else if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
            {
                bool flag;
                int t = pos;
                for (; t <= exper.size() - 1; t++)
                {
                    if (exper[t] == '(')
                    {
                        flag = 1;
                        break;
                    }
                    if (exper[t] == '+' || exper[t] == '-' || exper[t] == '*' || exper[t] == '/')
                    {
                        flag = 0;
                        break;
                    }
                }
                if (t == exper.size())
                    flag = 0;
                if (flag == 0) //后面是变量
                {
                    string temp;
                    for (; pos <= exper.size() - 1; pos++)
                        if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
                            temp += exper[pos];
                        else //pos到了符号
                            break;
                    double x = get_value(temp, vars, funs);
                    if (x == 999997 || x == 0)
                        return 999997;
                    result /= x;
                }
                else //函数
                {
                    string temp;
                    int n = exper.find("(", pos);
                    temp = exper.substr(pos, n - pos + 1);
                    pos = n + 1;
                    int t = 1;
                    for (;; pos++)
                    {
                        if (exper[pos] == '(')
                            t++;
                        if (exper[pos] == ')')
                            t--;
                        temp += exper[pos];
                        if (t == 0)
                        {
                            pos++;
                            //cout<<temp<<endl;break;
                            double y = get_value(temp, vars, funs);
                            if (y == 999997 || y == 0)
                                return 999997;
                            result /= y;
                            break;
                        }
                    }
                }
            }
        }

        else if (exper[pos] == '+' || exper[pos] == '-') //遇到加减号
        {
            bool flag;
            if (exper[pos] == '+')
                flag = 0;
            else
                flag = 1;
            pos++;
            string temp;
            for (; pos <= exper.size() - 1;) //对后面惊醒融合
            {

                if (exper[pos] >= '0' && exper[pos] <= '9') //数字
                {
                    for (; pos <= exper.size() - 1; pos++)
                        if ((exper[pos] >= '0' && exper[pos] <= '9') || exper[pos] == '.')
                            temp += exper[pos];
                        else //pos到了符号
                            break;

                    if (pos == exper.size())
                        break;
                    if (exper[pos] == '+' || exper[pos] == '-')
                        break;
                    temp += exper[pos];
                    pos++;
                }

                else if (exper[pos] == '(') //括号
                {
                    int num = 1;
                    temp += '(';
                    pos++;
                    for (; pos <= exper.size() - 1; pos++)
                    {
                        if (exper[pos] == '(')
                            num++;
                        if (exper[pos] == ')')
                            num--;
                        if (num == 0)
                        {
                            pos++;
                            temp += ')';
                            break;
                        }
                        temp += exper[pos];
                    }

                    if (pos == exper.size())
                        break;
                    if (exper[pos] == '+' || exper[pos] == '-')
                        break;
                    temp += exper[pos];
                    pos++;
                }

                else if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
                {
                    bool flag;
                    int t = pos;
                    for (; t <= exper.size() - 1; t++)
                    {
                        if (exper[t] == '(')
                        {
                            flag = 1;
                            break;
                        }
                        if (exper[t] == '+' || exper[t] == '-' || exper[t] == '*' || exper[t] == '/')
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (t == exper.size())
                        flag = 0;
                    if (flag == 0) //变量
                    {
                        for (; pos <= exper.size() - 1; pos++)
                            if ((exper[pos] >= 'a' && exper[pos] <= 'z') || (exper[pos] >= 'A' && exper[pos] <= 'Z'))
                                temp += exper[pos];
                            else //pos到了符号
                                break;

                        if (pos == exper.size())
                            break;
                        if (exper[pos] == '+' || exper[pos] == '-')
                            break;
                        temp += exper[pos];
                        pos++;
                    }
                    else //函数
                    {

                        int n = exper.find("(", pos);
                        temp += exper.substr(pos, n - pos + 1);
                        pos = n + 1;
                        int t = 1;
                        for (;; pos++)
                        {
                            if (exper[pos] == '(')
                                t++;
                            if (exper[pos] == ')')
                                t--;
                            temp += exper[pos];
                            if (t == 0)
                            {
                                pos++;
                                break;
                            }
                        }
                        if (pos == exper.size())
                            break;
                        if (exper[pos] == '+' || exper[pos] == '-')
                            break;
                        temp += exper[pos];
                        pos++;
                    }
                }
            }
            if (flag == 0)
            {
                if (get_value(temp, vars, funs) == 999997)
                    return 999997;
                result += get_value(temp, vars, funs);
            }
            else
            {
                if (get_value(temp, vars, funs) == 999997)
                    return 999997;
                result -= get_value(temp, vars, funs);
            }
        }
    }
    return result;
}

//---------------------------------------------------------分割初始输入
vector<string> Cut(string str)
{

    vector<string> a;
    if (str.size() == 0)
        return a;
    stringstream input(str);
    string temp;
    while (input >> temp)
        a.push_back(temp);
    return a;
}

//-------------------------------------------------------判断赋值表达式(变量直接赋值)
bool check_eva_1(string eva)
{
    //先检查左边
    int n = 0;
    for (string::iterator it = eva.begin(); it < eva.end(); it++)
        if (*it == '=')
            n++;
    if (n != 1)
        return 0;
    if (!check_fulle(eva.substr(0, eva.find("="))))
        return 0;
    //在检查右边
    if (!check_num(eva.substr(eva.find("=") + 1, eva.size() - eva.find("=") - 1)))
        return 0;

    return 1;
}

//---------------------------------------------------检查是否为求值命令
bool check_get(string str)
{
    //cout << "panduanbioada\n";
    for (string::iterator it = str.begin(); it < str.end(); it++)
        if (*it == '=')
            return 0;
    return 1;
}

//------------------------------------------------------计算单个变量
double get_single_eng(string str, vector<var> vars, vector<fun> funs)
{
    //cout << "kaishi" << endl;
    for (vector<var>::iterator it = vars.begin(); it < vars.end(); it++)
    {
        if (it->name == str && it->con == 0)
            return it->value;
        if (it->name == str && it->con == 1)
            return get_value(it->exp, vars, funs);
    }
    return 999997;
    //cout << "cannot find!" << endl;
}

//---------------------------------------------------------判断赋值表达式(变量为表达式)
bool check_eva_2(string eva)
{
    //先检查左边
    int n = 0;
    for (string::iterator it = eva.begin(); it < eva.end(); it++)
        if (*it == '=')
            n++;
    if (n != 1)
        return 0;
    if (!check_fulle(eva.substr(0, eva.find("="))))
        return 0;
    //在检查右边
    if (!check_num(eva.substr(eva.find("=") + 1, eva.size() - eva.find("=") - 1)))
        return 1;

    return 0;
}

//---------------------------------------------------------展示所有变量
void show_var(vector<var> vars)
{
    for (vector<var>::iterator it = vars.begin(); it < vars.end(); it++)
    {
        if (it->con == 0)
            cout << it->name << "=" << it->value << endl;
        else
            cout << it->name << "=" << it->exp << endl;
    }
}

//--------------------------------------------------------------判断函数定义
bool check_eva_3(string str)
{
    int n = str.find("=");
    if (str[n - 1] == ')')
        return 1;
    return 0;
}

//-----------------------------------------------------------增加函数
vector<fun> add_fun(vector<fun> funs, string str)
{
    vector<int> pos;
    int n1 = str.find("("), n2 = str.find("=");
    pos.push_back(n1);
    for (int i = n1; i < n2; i++)
        if (str[i] == ',' || str[i] == ')')
            pos.push_back(i);

    fun temp;
    temp.name = str.substr(0, n1);
    temp.exp = str.substr(n2 + 1, str.size() - n2 - 1);
    for (int i = 0; i <= pos.size() - 1 - 1; i++)
    {
        string t = str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1);
        temp.unknown.push_back(t);
    }
    funs.push_back(temp);
    return funs;
}

void show_fun(vector<fun> funs)
{
    for (vector<fun>::iterator it = funs.begin(); it < funs.end(); it++)
    {
        cout << it->name << "(";
        for (int i = 0; i < it->unknown.size(); i++)
        {
            cout << it->unknown[i];
            if (i == it->unknown.size() - 1)
                cout << ")";
            else
                cout << ",";
        }
        cout << "=" << it->exp << endl;
    }
}

//------------------------------------------------------------计算单一函数值
double get_fun(string str, vector<var> vars, vector<fun> funs)
{
    vector<var> ttt = vars;
    vector<int> pos;
    int n1 = str.find("("), n2 = str.size() - 1;
    pos.push_back(n1);
    int n = 1;
    for (int i = n1 + 1; i <= n2; i++)
    {
        if (str[i] == '(')
            n++;
        if (str[i] == ')')
            n--;
        if (str[i] == ',' && n == 1)
            pos.push_back(i);
    }
    pos.push_back(n2);
    string x = str.substr(0, n1);
    for (vector<fun>::iterator it = funs.begin(); it < funs.end(); it++)
        if (it->name == x)
        {
            for (int i = 0; i <= pos.size() - 1 - 1; i++)
            {

                var temp;
                temp.con = 0;
                temp.name = it->unknown[i];
                double p = get_value(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1), vars, funs);
                if (p == 999997)
                    return 999997;
                temp.value = p;
                ttt.push_back(temp);
            }
            return get_value(it->exp, ttt, funs);
        }
}

//----------------------------------------------判断表达式格式
bool check_form(string str)
{
    string a;
    for (string::iterator it = str.begin(); it < str.end(); it++)
    {
        if (*it == '(')
            a += '(';
        if (*it == ')')
            a += ')';
    }
    int len = a.size();
    int c = 0;
    int x = 0;
    int i = 0;
    for (; i <= len - 2 - x; i++)
    {
        if (a[i] == '(' && a[i + 1] == ')')
        {
            c += 2;

            for (int j = i; j <= len - 3 - x; j += 2)
                a[j] = a[j + 2];
            for (int j = i + 1; j <= len - 3 - x; j += 2)
                a[j] = a[j + 2];
            i = -1;
            x += 2;
        }
    }
    if (c != len)
        return 0;
    for (int i = 0; i + 1 <= str.size() - 1; i++)
        if (str[i] == '(' && str[i + 1] == ')')
            return 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if (i - 1 < 0 || i + 1 > str.size() - 1)
                return 0;
            if (!((str[i - 1] >= '0' && str[i - 1] <= '9') || (str[i - 1] >= 'a' && str[i - 1] <= 'z') || (str[i - 1] >= 'A' && str[i - 1] <= 'Z') || str[i - 1] == ')'))
                return 0;
            if (!((str[i + 1] >= '0' && str[i + 1] <= '9') || (str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= 'A' && str[i + 1] <= 'Z') || str[i + 1] == '('))
                return 0;
        }

    return 1;
}

//-----------------------------------------------------三目运算的转化
string tran_2(string str, vector<var> vars, vector<fun> funs)
{
    struct node
    {
        int pos1, pos2;
    };
    if (str.find("?") == -1)
        return str;
    vector<node> v;
    for (int n = 0; str.find("?", n) != -1;)
    {
        node temp;
        temp.pos1 = str.find("?", n);
        temp.pos2 = str.find(":", n);
        v.push_back(temp);
        n = str.find(":", n) + 1;
    }
    for (vector<node>::iterator it = v.end()-1; it >= v.begin(); it--)
    {
        string str1, str2, str3;
        str2 = str.substr(it->pos1 + 1, it->pos2 - it->pos1 - 1);
        int i1 = it->pos1 - 1;
        for (int n = 0; i1 > -1; i1--)
        {
            if (str[i1] == ')')
                n++;
            if (str[i1] == '(')
                n--;
            if (n == 0 && (str[i1] == '+' || str[i1] == '-'))
                break;
            str1 = str[i1] + str1;
        }
        int i2 = it->pos2 + 1;
        for (int n = 0; i2 < str.size(); i2++)
        {
            if (str[i2] == '(')
                n++;
            if (str[i2] == ')')
                n--;
            if (n == 0 && (str[i2] == '+' || str[i2] == '-'))
                break;
            str3 += str[i2];
        }
        if (get_value(str1, vars, funs) != 0)
            str.replace(i1 + 1, i2 - i1 - 1, str2);
        else
            str.replace(i1 + 1, i2 - i1 - 1, str3);
    }
    return str;
}

//------------------------------------------------------展现历史
void show_his(vector<history> his, vector<var> vars, vector<fun> funs)
{
    cout << "历史记录：\n";
    for (vector<history>::iterator it = his.begin(); it < his.end(); it++)
    {
        if (it->order == "SHOW VAR")
        {
            cout << "--------------------------\n";
            cout << it->order << endl;
            show_var(vars);
            continue;
        }
        if (it->order == "SHOW FUNC")
        {
            cout << "--------------------------\n";
            cout << it->order << endl;
            show_fun(funs);
            continue;
        }
        if (it->n == 777)
        {
            cout << "--------------------------\n";
            cout << it->order << endl
                 << it->result << endl;
            continue;
        }
        else
        {
            cout << "--------------------------\n";
            cout << it->order << endl
                 << it->n << endl;
            continue;
        }
    }
    cout << "--------------------------\n";
}

//绝对值运算
string tran_3(string str, vector<var> vars, vector<fun> funs)
{
    if (str.find("abs") == -1)
        return str;
    struct node
    {
        int pos1, pos2;
    };
    vector<node> v;
    for (int n = 0; str.find("abs", n) != -1;)
    {
        node temp;
        temp.pos1 = str.find("abs", n);
        n = str.find("abs", n) + 3;
        for (int i = 0; n < str.size(); n++)
        {
            if (str[n] == '(')
                i++;
            if (str[n] == ')')
                i--;
            if (i == 0)
                break;
        }
        temp.pos2 = n;
        v.push_back(temp);
    }
    for (vector<node>::iterator it = v.end()-1; it > v.begin()-1; it--)
    {
        string exper = str.substr(it->pos1 + 4, it->pos2 - it->pos1-4);
        if (get_value(exper, vars, funs) > 0)
            str.replace(it->pos1, it->pos2 - it->pos1 + 1, '(' + exper + ')');
        else
            str.replace(it->pos1, it->pos2 - it->pos1 + 1, "(0-(" + exper + "))");
    }
    return str;
}