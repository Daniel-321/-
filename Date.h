#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

//
// Created by yyh on 2019/7/17.
//
#include <iomanip>
#include<stdlib.h>
#include <iostream>
//Date类不需要拷贝构造函数，因为对于任意两个日期 他们总是不一样的
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
/*
 1.调用系统时间，输出当前月的日历
 2.指定某年某月 输出该月的日历
*/
using namespace std;
class Date {
public:
    Date() {
//        TotalDays = 0;
//        TotalMonths = 0;
//        TotalYears = 0;
        system("cls");
        cout << "欢迎使用" << endl;
    }
    void InputTime();       //输入时间
    void GetNowTime();      //获取系统时间
    void GetFirstDays();    //计算当前月份第一天周几
    void GetMonthDays();    //计算当前月份总天数
    void Print();           //打印当前月份日历
    void PrintNowTime();    //打印当前时间
    void LunarPrint(int LineFlagBegin,int LineFlagEnd);      //打印农历
    void Constellation();   //星座判断
    int Lunar(int year, int month, int day);        //农历
    void output(int year, int month, int day);      //农历输出
    int intTransform(string str);     //将输入的字符串改变为整数
    ~Date() {
        cout << "thanks to use" << endl;
    }
private:
    ISALLOW_COPY_AND_ASSIGN(Date);
    int NowYear;//当前年
    int NowMonth;//当前月
    int NowDay;//当前日
    int Year;//查询年
    int Month;//查询月
    int Day;//查询日
    int LunarYear;//农历年
    int LunarMonth;//农历月
    int LunarDay;//农历日
    unsigned int LunarCalendarDay;//农历编码数
    int MonthDays;//这个月的天数
    int FirstWeakDay;//每个月第一天周几
    string ConstellationDescribe;//星座描述


};

#endif // DATE_H_INCLUDED
