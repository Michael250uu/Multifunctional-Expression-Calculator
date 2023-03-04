/*
 * @Author: your name
 * @Date: 2021-06-02 21:09:49
 * @LastEditTime: 2021-06-16 23:41:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /proj4/src/main.cc
 */
#include <iostream>
#include <vector>
#include "../inc/process.h"
#include "../inc/data.h"
#include <iomanip>
using namespace std;

vector<var> vars;
vector<fun> funs;
vector<history> his;

int main()
{

    while (true)
    {

        string all;
        getline(cin, all);
        history T;
        T.order = all;
        //if (all.size() == 0)
        //{
        //    cout << "error!\n";
        //    continue;
        //}
        vector<string> parts = Cut(all);
        //cout << parts.size()<<endl;
        //break;
        if (parts.size() == 1 && parts[0] == "exit") //---------------------------------------退出
            break;

        else if (parts.size() == 2 && parts[0] == "Var") //------------------------------------------变量初始化
        {
            if (check_eva_1(parts[1])) //变量且con=0
            {
                var temp;
                temp.value = get_value(parts[1].substr(parts[1].find("=") + 1, parts[1].size() - parts[1].find("=") - 1), vars, funs);
                if (temp.value == 999997)
                {
                    cout << " error!\n";
                    T.result = "error!";
                    his.push_back(T);
                    continue;
                }
                temp.con = 0;
                temp.name = parts[1].substr(0, parts[1].find("="));

                vars.push_back(temp);
                T.result = "done!";
                his.push_back(T);
            }
            else if (check_eva_2(parts[1])) //变量且con==1
            {
                var temp;

                temp.con = 1;
                temp.name = parts[1].substr(0, parts[1].find("="));
                temp.exp = parts[1].substr(parts[1].find("=") + 1, parts[1].size() - parts[1].find("=") - 1);
                vars.push_back(temp);
                T.result = "done!";
                his.push_back(T);
                //for (vector<var>::iterator it = vars.begin(); it < vars.end(); it++)
                //   cout << it->con << " " << it->exp << " " << it->name << endl;
            }

            else
            {
                cout << " error!\n";
                T.result = "error!";
                his.push_back(T);
                continue;
            }
        }
        else if (parts.size() == 2 && parts[0] == "Func") //定义函数
        {
            funs = add_fun(funs, parts[1]);
            T.result = "done!";
            his.push_back(T);
            continue;
        }

        else if (parts.size() == 1 && (check_eva_2(parts[0]) || check_eva_1(parts[0]))) //后期改变变量
        {
            if (check_eva_1(parts[0]))
            {
                //cout << "hhh";
                string x = parts[0].substr(0, parts[0].find("="));
                double temp = get_value(parts[0].substr(parts[0].find("=") + 1, parts[0].size() - parts[0].find("=") - 1), vars, funs);
                if (temp == 999997)
                {
                    cout << "error!\n";
                    T.result = "error!";
                    his.push_back(T);
                    continue;
                }
                for (vector<var>::iterator it = vars.begin(); it < vars.end(); it++)
                    if (it->name == x)
                    {
                        it->con = 0;
                        it->value = temp;
                        T.result = "done!";
                        his.push_back(T);
                        continue;
                    }
                //cout << "cannot find!\n";
                continue;
            }
            else
            {
                string x = parts[0].substr(0, parts[0].find("="));
                for (vector<var>::iterator it = vars.begin(); it < vars.end(); it++)
                    if (it->name == x)
                    {
                        it->con = 1;
                        it->exp = parts[0].substr(parts[0].find("=") + 1, parts[0].size() - parts[0].find("=") - 1);
                        T.result = "done!";
                        his.push_back(T);
                        continue;
                    }
                // cout << "cannot find!\n";
                continue;
            }
        }

        else if (parts.size() == 1 && check_get(parts[0])) //求值
        {
            //cout << "qiuzhi\n";
            //cout << parts[0] << endl;
            double x = get_value(parts[0], vars, funs);
            if (x == 999997)
            {
                cout << "error!\n";
                T.result = "error!";
                his.push_back(T);
                continue;
            }
            cout << fixed << setprecision(6) << x << endl;
            T.n = x;
            his.push_back(T);
        }

        else if (parts.size() == 2 && parts[0] == "SHOW" && parts[1] == "VAR")

        {
            show_var(vars);
            his.push_back(T);
        }

        else if (parts.size() == 2 && parts[0] == "SHOW" && parts[1] == "FUNC")
        {
            show_fun(funs);
            his.push_back(T);
        }
        else if (parts.size() == 2 && parts[0] == "SHOW" && parts[1] == "HISTORY")
            show_his(his, vars, funs);
        else
        {
            cout << "error!\n";
            T.result = "error!";
            his.push_back(T);
        }
    }
}