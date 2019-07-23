//
//  Created by yyh on 2019/7/17.
//  东北大学 物联网1802 c++课程设计
//
#include <iostream>
#include <iomanip>
#include<time.h>
#include<stdlib.h>
//
//#include "Date.h"
#include "cmake-build-debug/Date.h"
#include "Data.h"
using namespace std;

void Date::InputTime() {
    string cYear, cMonth;
    int year = 0, month = 0;
    cout << "查询年份 月份:";
    bool cinFlag=true,valFlag=true;//cinFlag判断输入错误valFlag判断数值错误
    cin >> cYear >> cMonth;
    cin.good();
    //判断输入是否为数字
    for (int i = 0; i < cYear.size(); i++) {
        if (cYear[i] > '9' || cYear[i] < '0') cinFlag = false;
    }
    for (int i = 0; i < cMonth.size(); i++) {
        if (cMonth[i] > '9' || cMonth[i] < '0') cinFlag = false;
    }
    if(cinFlag){
//        cout<<"cYear="<<cYear<<' '<<"cMonth="<<cMonth<<endl;
        //转化为int类型
        year=intTransform(cYear);
        month=intTransform(cMonth);
        //??????????
        if(year<0||month>13||month<0){
            cout<<"value error"<<endl;
            return;
        }
    }
    else{//????
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
    time_t CurTime = time(NULL);
    tm LocalTime = *localtime(&CurTime);
    NowYear = LocalTime.tm_year + 1900;
    NowMonth = LocalTime.tm_mon + 1;
    NowDay = LocalTime.tm_mday;
}
void Date::GetFirstDays() {
/*  基姆拉尔森计算公式
    W = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) mod 7
*/
    int month = Month, year = Year, day = 1;
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    //周日是0 周一是1 以此类推
    FirstWeakDay = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;
    if (FirstWeakDay == 7) FirstWeakDay = 0;
}
void Date::GetMonthDays() {
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//月份天数表
    if ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0))//闰年判断
        day[1]++;
    MonthDays = day[Month - 1];//每个月天数
}
void Date::Constellation(){
//    cout<<"Constellation is run"<<endl;
    string ConsteList[12]={"白羊座","金牛座","双子座","巨蟹座","狮子座","处女座","天秤座","天蝎座","射手座","魔蝎座","水瓶座","双鱼座"};
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
    GetMonthDays();                 //得到每个月天数
    GetFirstDays();                 //得到第一天周几
    Constellation();                //得到星座
    //system("cls");

    int LineFlagBegin=1,LineFlagEnd=30;//每一行开始/结束的标志
    int loopflag=0;//标志第一次进入农历的输出循环
    cout <<"Constellation:"<<ConstellationDescribe<<endl;
    cout << "You find time is:" << Year << '.' << Month<<'.' <<Day<< endl;
    output(Year,Month,Day);
    //cout<<"firstday:"<<FirstWeakDay<<endl;
    cout << "星期日 星期一 星期二 星期三 星期四 星期五 星期六" << endl;
    if (FirstWeakDay<7)
        for (int i = 0; i < FirstWeakDay; i++)
            cout << "       ";
    for (int i = 1; i <= MonthDays; i++) {//一个公历月的循环
        if(((FirstWeakDay + i - 1) % 7 == 1)&&i!=1)//当日期为周日的时候记录行首日期，并且这一天是第一天的话不需要更新，使用默认的行首日期
            LineFlagBegin=i-1;//更新行首标志日期
        if ((FirstWeakDay + i - 1) % 7 == 0&&(FirstWeakDay + i - 1)!=0) {//第一天是周日不需要换行
            cout << endl;
            LineFlagEnd=i;//更新行末标志日期
            //cout<<"LineFlag1="<<LineFlagBegin<<"LineFlag="<<LineFlagEnd<<endl;
            loopflag++;//如果loopflag=1那么表示我们第一次进入循环，用于将农历第一行对齐
            if(loopflag==1){
                for (int k = 0; k < FirstWeakDay; k++)
                    cout << "       ";
                loopflag++;//递增此变量用于控制本循环不再在下一个日期运行
            }
            LunarPrint(LineFlagBegin,LineFlagEnd);
            cout<<endl;
            cout<<endl;
        }
        cout << setw(7) << left << i;
    }
    LineFlagBegin=LineFlagEnd;
    LineFlagEnd=MonthDays;
    //cout<<"LineFlag1="<<LineFlagBegin<<"LineFlag="<<LineFlagEnd<<endl;
    cout<<endl;
    LunarPrint(LineFlagBegin,LineFlagEnd+1);
    cout << endl;
}
void Date::LunarPrint(int LineFlagBegin,int LineFlagEnd){
    string Daystr,Monthstr;//定义农历输出字符串
    for(int j=LineFlagBegin;j<LineFlagEnd;j++){//换行之后开始输出农历
        Lunar(Year,Month,j);
        Monthstr=(LunarMonthList[LunarMonth])+"月";//记录农历月份
        Daystr=(LunarDayList[LunarDay]);//记录农历日份
        //如果这一天是初一的话 应该输出月份
        if(LunarDay==1)
            cout<<setw(7) << left << Monthstr;
        else
            cout<<setw(7) << left << Daystr;
    }
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
int Date::Lunar(int year, int month, int day)
{
    int SpanSpring,SpanDays,DayCount;
    int index,LeapFlag;
    //SpanSpring 记录春节离当年元旦的天数。
    //SpanDays 记录阳历日离当年元旦的天数。
    if ( ((LunarTable[year-1901] & 0x0060) >> 5) == 1)
        //0060=0000 0000 0110 0000和日期编码作与运算，能够得到春节所在的月份 这里是一月的情况
        //以1901年为例，得到春节在二月 编码位10
        SpanSpring = (LunarTable[year-1901] & 0x001F) - 1;
    else
        SpanSpring = (LunarTable[year-1901] & 0x001F) - 1 + 31;
    SpanDays =MonthAddList[month-1] + day - 1;//阳历日期相对序数
    if ( (!(year % 4)) && (month > 2))
        SpanDays++;
    //DayCount记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算
    //LeapFlag 是用来对闰月的特殊处理
    //判断阳历日在春节前还是春节后
    if (SpanDays >= SpanSpring)//阳历日在春节后（含春节那天）
    {
        SpanDays -= SpanSpring;
        month = 1;
        index = 1;
        LeapFlag = 0;
        if ( ( LunarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            //大小月判断 0x80000=0100 0000 0000 0000 0000 小月结果为0
            DayCount = 29;
        else
            DayCount = 30;
        while (SpanDays >= DayCount)
        {
            SpanDays -= DayCount;
            index++;//逐月判断
            if (month == ((LunarTable[year - 1901] & 0xF00000) >> 20) )
            //闰月判断 0xF00000=1111 0000 0000 0000 0000 0000得到闰月的月份
            {
                LeapFlag = ~LeapFlag;
                if (!LeapFlag)
                    month++;
            }
            else
                month++;
            if ( ( LunarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                //大小月判断 0x80000=0100 0000 0000 0000 0000 小月结果为0
                DayCount=29;
            else
                DayCount=30;
        }
        day = SpanDays + 1;//农历日份
    }
    else //阳历日在春节前
    {
        SpanSpring -= SpanDays;
        year--;
        month = 12;
        if ( ((LunarTable[year - 1901] & 0xF00000) >> 20) == 0)
            //闰月判断 0xF00000=1111 0000 0000 0000 0000 0000得到闰月的月份
            index = 12;
        else
            index = 13;
        LeapFlag = 0;
        if ( ( LunarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            DayCount = 29;
        else
            DayCount = 30;
        while (SpanSpring > DayCount)
        {
            SpanSpring -= DayCount;
            index--;
            if (LeapFlag == 0)
                month--;
            if (month == ((LunarTable[year - 1901] & 0xF00000) >> 20))
                //闰月判断 0xF00000=1111 0000 0000 0000 0000 0000得到闰月的月份
                LeapFlag = ~LeapFlag;
            if ( ( LunarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                //大小月判断 0x80000=0100 0000 0000 0000 0000 小月结果为0
                DayCount = 29;
            else
                DayCount = 30;
        }
        day = DayCount - SpanSpring + 1;
    }
    LunarCalendarDay=0;//一定要初始化！！！！否则之后的运算会带着非0值走下去 导致数组越界
    LunarCalendarDay |= day;//LunarCalendarDay用于存储农历日和月，低5位存日期，6位开始存月份
    LunarCalendarDay |= (month << 6);//6位开始存月份
    LunarMonth=(LunarCalendarDay & 0x3C0) >> 6;
    LunarDay=LunarCalendarDay & 0x3F;
    if (month == ((LunarTable[year - 1901] & 0xF00000) >> 20))
        return 1;
    else
        return 0;
}
void Date::output(int year,int month,int day)
{
    string str = "";
    str+="农历";
    if (Lunar(year,month,day))//闰月判断
        str+="闰";
    Lunar(year,month,day);
    int reeor=((LunarCalendarDay & 0x3C0) >> 6);
    str+=(LunarMonthList[(LunarCalendarDay & 0x3C0) >> 6]);//月份编码 和1111作与运算就是保留原位
    //0x3C0=0011 1100 0000
    //cout<<((LunarCalendarDay & 0x3C0) >> 6)<<endl;
    str+="月";
    str+=(LunarDayList[LunarCalendarDay & 0x3F]);//日份编码
    //0x3F=0011 1111
    cout<<str<<endl;
}
int main() {
    bool flag = true;//????????
    while (flag) {
        Date cal;
        cal.PrintNowTime();
        cal.InputTime();
        cal.Print();
        system("pause");
    }
    return 0;
}
