/*******************************************************************************
 FileName:  MotionAGV.h
 Platform:   DSP 32-bit TMS320C6713
 Description:  AGV MOtion Function
 History:
 <author>   <time>   <version >  <desc>
 wlqunr  2017-7-25  1.00     build this file
 ********************************************************************************/
 /*******************************************************************************
  * 1.绝对坐标以世界坐标系为参考，相对坐标模式以小车坐标系为参考
  * 2.公式分析时，小车坐标、4个轮毂坐标的X轴正方向统一水平向右
  ********************************************************************************/
#ifndef MOTIONAGV_H_
#define MOTIONAGV_H_
#include "MotionDataType.h"

//+++++++++++++++++++++++++++++++++车型参数接口++++++++++++++++++++++++++++++++++
typedef struct AGVmoDa000 {
	//AGV运动车型参数
	double wheelBaseL;		// 纵向轴距(m)
	double wheelBaseW;		// 横向轮距(m)
	double wheelWMax;		// 最大轮速(rad/s)
	double wheelRadius;		// 轮毂半径(m)
} AgvMotionPara;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++轮速参数接口++++++++++++++++++++++++++++++++++
typedef struct AGVmoDa100 {
	//轮速参数
	INT8U OrderType;		// R/W 指令方式(1、2、3、4)（见车速接口）
	double Rx;				// R/W 世界坐标系以小车坐标系为参考，小车x轴相对于世界坐标系X轴的夹角
	double W1;				// R/W 左前轮速度(rad/s)
	double W2;				// R/W 右前轮速度
	double W3;				// R/W 左后速度
	double W4;				// R/W 右后速度
} AgvWwheel;       

typedef struct AGVmoDa101 {
	//PWM输出参数
	INT8U AxisNum;			// W 轴号范围0-3对应W1-W4；即Axi(i)=W(i+1)
	INT16U Freq[4];			// W 各轴PWM频率(10Hz--10Khz)
	INT8U Duty[4];			// W 各轴PWM占空比(0-100)
	INT8U Dir[4];			// W 方向IO传递信号(1、0)
} AgvPwm;       

typedef struct AGVmoDa102 {
	//脉冲输出参数
	INT8U AxisNum;			// W 轴号范围0-3对应W1-W4；即Axi(i)=W(i+1)
	INT16U Freq[4];			// W 各轴PWM频率(10Hz--10Khz)
	INT8U Duty[4];			// W 各轴PWM占空比(0-100)
	INT8U Dir[4];			// W 方向IO传递信号(1、0)
} AgvPls;       

typedef struct AGVmoDa103 {
	//光电编码器输入参数
	INT8U AxisNum;			// W 轴号范围0-3对应W1-W4；即Axi(i)=W(i+1)
	INT16U Freq[4];			// W 各轴PWM频率(10Hz--10Khz)
	INT8U Duty[4];			// W 各轴PWM占空比(0-100)
	INT8U Dir[4];			// W 方向IO传递信号(1、0)
} AgvOptc;

typedef struct AGVmoDa104 {
	//Hall传感器输入参数
	INT8U AxisNum;			// W 轴号范围0-3对应W1-W4；即Axi(i)=W(i+1)
	INT16U Freq[4];			// W 各轴PWM频率(10Hz--10Khz)
	INT8U Duty[4];			// W 各轴PWM占空比(0-100)
	INT8U Dir[4];			// W 方向IO传递信号(1、0)
} AgvHall;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++车速参数接口++++++++++++++++++++++++++++++++++
//	从速度方向描述，AGV可以分为直线、折线、圆弧、曲线、自旋、停车等运动形式，
//	折线可由直线运动拼接而成，圆弧可由直线插补或差速实现，已知参数的曲线可由
//	圆弧拼接，不规则曲线可由插补实现，自旋由差速实现，自旋其实是一种特殊的差
//  速圆弧运动。
//  （1）直线运动描述
//		直角坐标系：Vx、Vy
//		极坐标系：V、angle
//	（2）差速圆弧运动描述
//		Wz、Rz
//		注：绝对坐标系即世界坐标系，相对坐标系即小车坐标系，Rx为小车坐标系转换
//			到世界坐标系的X轴夹角。
typedef struct Or1 {
	//速度绝对直角坐标模式
	double Rx;				// R/W 小车当前姿态角(x轴于绝对坐标系之间的旋转角)
	double line_Vx;			// R/W 小车X方向速度
	double line_Vy;			// R/W 小车Y方向速度
	double arc_Wz;			// R/W 圆弧运动角速度(rad/s)，正值顺时针、负值逆时针
	double arc_Rz;			// R/W 圆弧半径（m），为0时做自旋运动
} Ord1;

typedef struct Or2 {
	//速度相对直角坐标模式
	double line_vx;			// R/W 小车X方向速度
	double line_vy;			// R/W 小车Y方向速度
	double arc_wz;			// R/W 圆弧运动角速度(rad/s)，正值顺时针、负值逆时针
	double arc_rz;			// R/W 圆弧半径（m），为0时做自旋运动
} Ord2;

typedef struct Or3 {
	//速度绝对极坐标模式
	double Rx;				// R/W 小车当前姿态角(x轴于绝对坐标系之间的旋转角)
	double line_V;			// R/W 小车速度矢量模
	double line_Angle;		// R/W 小车速度矢量方向（与X轴的夹角弧度值）
	double arc_Wz;			// R/W 圆弧运动角速度(rad/s)，正值顺时针、负值逆时针
	double arc_Rz;			// R/W 圆弧半径（m），为0时做自旋运动
} Ord3;

typedef struct Or4 {
	//速度相对极坐标模式
	double line_v;			// R/W 小车速度矢量模
	double line_angle;		// R/W 小车速度矢量方向（与X轴的夹角弧度值）
	double arc_wz;			// R/W 圆弧运动角速度(rad/s)，正值顺时针、负值逆时针
	double arc_rz;			// R/W 圆弧半径（m），为0时做自旋运动
} Ord4;

typedef struct AGVmoDa200 {
	//车速接口
	INT8U OrderType;		// R/W 指令方式(1、2、3、4)
	Ord1 Ord1;				// Order1 Velocity  Absolute Rectangle coordinate
	Ord2 Ord2;				// Order2 Velocity  Relative Polar     coordinate
	Ord3 Ord3;				// Order3 Velocity  Absolute Rectangle coordinate
	Ord4 Ord4;				// Order4 Velocity  Relative Polar     coordinate
} AgvVcar;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//后期记得把运动层的函数全部声明
extern double Angle2rad(double angleTemp);
extern AgvPwm Wwheel2PWM(AgvWwheel AgvWwheel0);
extern AgvWwheel Vcar2Wwheel(AgvVcar AgvVcar0);
extern AgvWwheel StopAgv(void);
extern AgvPls Wwheel2PLS(AgvWwheel AgvWwheel0);
extern AgvVcar Wwheel2Vcar(AgvWwheel AgvWwheel1);


#endif /* MOTIONAGV_H_ */


