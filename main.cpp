//
// Created by yyh on 2019/7/17.
//
#include <iostream>
#include <iomanip>
#include<time.h>
#include<stdlib.h>
//
#include "Date.h"

using namespace std;

void Date::InputTime() {
    string cYear, cMonth;
    int year = 0, month = 0;
    cout << "查找年份 月份:";
    bool cinFlag=true,valFlag=true;//cinFlag用于判断输入是否合法，valFlag判断月份和年份是否合法
    cin >> cYear >> cMonth;
    cin.good();
    //异常输入处理
    for (int i = 0; i < cYear.size(); i++) {
        if (cYear[i] > '9' || cYear[i] < '0') cinFlag = false;
    }
    for (int i = 0; i < cMonth.size(); i++) {
        if (cMonth[i] > '9' || cMonth[i] < '0') cinFlag = false;
    }
    if(cinFlag){
//        cout<<"cYear="<<cYear<<' '<<"cMonth="<<cMonth<<endl;
        //年份月份转换为整型
        year=intTransform(cYear);
        month=intTransform(cMonth);
        //异常月份数年份数处理
        if(year<0||month>13||month<0){
            cout<<"value error"<<endl;
            return;
        }
    }
    else{//输入有误
        cout<<"cin error"<<endl;
        return;
    }
    Year = year;
    Month = month;
}
int Date::intTransform(string str) {
    int val=0;
    for(int i=0;i<str.size();i++){
        val=(str[i]-'0')+10*val;
    }
    //cout<<"val="<<val<<endl;
    return val;
}
void Date::GetNowTime() {
    time_t CurTime = time(0);
    tm LocalTime = *localtime(&CurTime);
    NowYear = LocalTime.tm_year + 1900;
    NowMonth = LocalTime.tm_mon + 1;
    NowDay = LocalTime.tm_mday;
}
void Date::GetFirstDays() {
/*    基姆拉尔森计算公式
    W = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) mod 7*/
    int month = Month, year = Year, day = 1;
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    //计算结果 周日为0，周一为1，以此类推
    FirstWeakDay = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;
    if (FirstWeakDay == 7) FirstWeakDay = 0;
}
void Date::GetMonthDays() {
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//每月天数
    if ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0))//闰年判断
        day[1]++;
    MonthDays = day[Month - 1];//求得月份的天数
}
void Date::Constellation(){
//    cout<<"Constellation is run"<<endl;
    string ConsteList[12]={"白羊座","金牛座","双子座","巨蟹座","狮子座","处女座","天秤座","天蝎座","射手座","摩羯座","水瓶座","双鱼座"};
    if(Month==3){
        if(Day>=21) ConstellationDescribe=ConsteList[0];
        else ConstellationDescribe=ConsteList[11];
    }
    if(Month==4){
        if(Day>=21) ConstellationDescribe=ConsteList[1];
        else ConstellationDescribe=ConsteList[0];
    }
    if(Month==5){
        if(Day>=21) ConstellationDescribe=ConsteList[2];
        else ConstellationDescribe=ConsteList[1];
    }
    if(Month==6){
        if(Day>=22) ConstellationDescribe=ConsteList[3];
        else ConstellationDescribe=ConsteList[2];
    }
    if(Month==7){
        if(Day>=23) ConstellationDescribe=ConsteList[4];
        else ConstellationDescribe=ConsteList[3];
    }
    if(Month==8){
        if(Day>=23) ConstellationDescribe=ConsteList[5];
        else ConstellationDescribe=ConsteList[4];
    }
    if(Month==9){
        if(Day>=23) ConstellationDescribe=ConsteList[6];
        else ConstellationDescribe=ConsteList[7];
    }
    if(Month==10){
        if(Day>=23) ConstellationDescribe=ConsteList[7];
        else ConstellationDescribe=ConsteList[8];
    }
    if(Month==11){
        if(Day>=22) ConstellationDescribe=ConsteList[8];
        else ConstellationDescribe=ConsteList[7];
    }
    if(Month==12){
        if(Day>=22) ConstellationDescribe=ConsteList[9];
        else ConstellationDescribe=ConsteList[8];
    }
    if(Month==1){
        if(Day>=20) ConstellationDescribe=ConsteList[10];
        else ConstellationDescribe=ConsteList[9];
    }
    if(Month==2){
        if(Day>=19) ConstellationDescribe=ConsteList[11];
        else ConstellationDescribe=ConsteList[10];
    }
}
void Date::Print() {
    GetMonthDays();                 //获取当前月份天数
    GetFirstDays();                 //获取第一天周几
    Constellation();                //获取星座
    //system("cls");
    cout <<"Constellation:"<<ConstellationDescribe<<endl;
    cout << "You find time is:" << Year << '.' << Month << endl;
    //cout<<"firstday:"<<FirstWeakDay<<endl;
    cout << "日 一 二 三 四 五 六" << endl;
    if (FirstWeakDay<7)
        for (int i = 0; i < FirstWeakDay; i++)
            cout << "   ";
    for (int i = 1; i <= MonthDays; i++) {
        if ((FirstWeakDay + i - 1) % 7 == 0&&(FirstWeakDay + i - 1)!=0) {//当第一天就是周日的时候不要输出换行
            cout << endl;
        }
        cout << setw(3) << left << i;
    }
    cout << endl;
}
void Date::PrintNowTime() {
    GetNowTime();
    Year = NowYear;
    Month = NowMonth;
    Day = NowDay;
    system("cls");
    cout << "Now the time is:" << NowYear << '.' << NowMonth << '.' << NowDay << endl;
    //cout<<"Now the time is:"<<Year<<'.'<<Month<<'.'<<Day<<endl;
    GetMonthDays();
    GetFirstDays();
    Print();
}
int main() {
    bool flag = true;//判断是否异常退出
    while (flag) {
        Date cal;
        cal.PrintNowTime();
        cal.InputTime();
        cal.Print();
        system("pause");
    }
    return 0;
}
