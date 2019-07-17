#include <iostream>
#include <iomanip>
#include "cmake-build-debug/Date.h"

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
void Date::Print() {
    GetMonthDays();                 //获取当前月份天数
    GetFirstDays();                 //获取第一天周几
    //system("cls");
    cout << "Now the time is:" << NowYear << '.' << NowMonth << '.' << NowDay << endl;
    cout << "You find time is:" << Year << '.' << Month << endl;
    cout << "日 一 二 三 四 五 六" << endl;
    if (FirstWeakDay<7)
        for (int i = 0; i < FirstWeakDay; i++)
            cout << "   ";
    for (int i = 1; i <= MonthDays; i++) {
        if ((FirstWeakDay + i - 1) % 7 == 0) {
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