/*file pedometer.h*/

#ifndef __PEDOMETER_H_
#define __PEDOMETER_H_

/* Function define. */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) (0 - (a)) > 0 ? (-(a)) : (a)

#define ORIGIN_FREQ       100                 /* Config origin input acc frequency. */
#define PEDOMETER_FREQ    25                  /* Cconfig current pedometer algorithm frequence. */
#define FILTER_CNT        4                   /* Filter size */
#define SAMPLE_SIZE       50
#define DYNAMIC_PRECISION 80                  /* 动态精度 */
#define ACTIVE_PRECISION  10                  /* 活跃轴最小变化值 */
#define MOST_ACTIVE_NULL  0	                  /* 未找到最活跃轴 */
#define MOST_ACTIVE_X     1		              /* 最活跃轴X */
#define MOST_ACTIVE_Y     2		              /* 最活跃轴Y */
#define MOST_ACTIVE_Z     3		              /* 最活跃轴Z */


#ifdef __cplusplus
extern "C" {
#endif

/* 三轴数据 */
typedef struct
{
	short x;
	short y;
	short z;
} Axis_Info_t;

/* 平均值结构 */
typedef struct Filter_Avg
{
	Axis_Info_t info[FILTER_CNT];
	unsigned char count;
} Filter_Avg_t;

/* 新旧三轴最值数据结构 */
typedef struct
{
	/*
		typedef struct {
		short x;
		short y;
		short z;
		}Axis_Info_t;
	*/
	Axis_Info_t newMax;
	Axis_Info_t newMin;
	Axis_Info_t oldMax;
	Axis_Info_t oldMin;
} Peak_Value_t;

/* 一个线性移位寄存器，用于过滤高频噪声 */
typedef struct Slide_Reg
{
	Axis_Info_t newSample;
	Axis_Info_t oldSample;
} Slide_Reg_t;

/* Initialize the pedometer data. */
void Pedomter_Init();

uint32_t Pedometer_Update(int ax, int ay, int az);

/* 读取xyz数据存入均值滤波器，存满进行计算，滤波后样本存入sample（FILTER_CNT个数据的平均值）*/
void FilterCalculate(Filter_Avg_t* FilterAvg, Axis_Info_t* Sample);

/* 初始化采样结构体的值 */ 
void PeakValueInit(Peak_Value_t* Peak);

/* 在动态阈值结构体初始化时，一定要将max的值都赋值为最小值，min赋值为最大值，这样才有利于动态更新 */
void PeakParaUpdate(Peak_Value_t* Peak, Axis_Info_t* AccSample);

/* 更新数据 */
char SlideUpdate(Slide_Reg_t* slid, Axis_Info_t* AccSample);

/* 判断当前最活跃轴 */
char SelectMostActiveAxis(Peak_Value_t* Peak);

/* 判断是否走步 */
unsigned int StepCalculate(Peak_Value_t* Peak, Slide_Reg_t* slid);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif