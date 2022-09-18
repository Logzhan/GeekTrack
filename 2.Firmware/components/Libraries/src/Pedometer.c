#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "Pedometer.h"

static uint32_t      StepCnt = 0;		// step_cnt为步数
static Axis_Info_t   Sample;
static Filter_Avg_t  FilterAvg;
static Axis_Info_t   AccSample;
static Peak_Value_t  Peak;
static Slide_Reg_t   Slide;

//读取xyz数据存入均值滤波器，存满进行计算，滤波后样本存入sample（FILTER_CNT个数据的平均值）
void FilterCalculate(Filter_Avg_t* FilterAvg, Axis_Info_t* Sample)
{
	uint8_t i;
	short XSum = 0, YSum = 0, ZSum = 0;
	for (i = 0; i < FILTER_CNT; i++)
	{
		XSum += FilterAvg->info[i].x;
		YSum += FilterAvg->info[i].y;
		ZSum += FilterAvg->info[i].z;
	}
	Sample->x = XSum / FILTER_CNT;
	Sample->y = YSum / FILTER_CNT;
	Sample->z = ZSum / FILTER_CNT;
}

//初始化采样结构体的值
void PeakValueInit(Peak_Value_t* Peak)
{
	Peak->newMax.x = -2047;
	Peak->newMax.y = -2047;
	Peak->newMax.z = -2047;

	Peak->newMin.x = 2048;
	Peak->newMin.y = 2048;
	Peak->newMin.z = 2048;
}

//在动态阈值结构体初始化时，一定要将max的值都赋值为最小值，min赋值为最大值，这样才有利于动态更新。
void PeakParaUpdate(Peak_Value_t* Peak, Axis_Info_t* AccSample)
{
	static unsigned int sampleSize = 0;
	sampleSize++;
	if (sampleSize > SAMPLE_SIZE)
	{
		/*采样达到50个，更新一次*/
		sampleSize = 1;
		Peak->oldMax = Peak->newMax;
		Peak->oldMin = Peak->newMin;
		//初始化
		PeakValueInit(Peak);
	}
	Peak->newMax.x = MAX(Peak->newMax.x, AccSample->x);
	Peak->newMax.y = MAX(Peak->newMax.y, AccSample->y);
	Peak->newMax.z = MAX(Peak->newMax.z, AccSample->z);

	Peak->newMin.x = MIN(Peak->newMin.x, AccSample->x);
	Peak->newMin.y = MIN(Peak->newMin.y, AccSample->y);
	Peak->newMin.z = MIN(Peak->newMin.z, AccSample->z);
}

//更新数据
char SlideUpdate(Slide_Reg_t* Slide, Axis_Info_t* AccSample)
{
	char res = 0;
	if (ABS((AccSample->x - Slide->newSample.x)) > DYNAMIC_PRECISION)
	{
		Slide->oldSample.x = Slide->newSample.x;
		Slide->newSample.x = AccSample->x;
		res = 1;
	}
	else
	{
		Slide->oldSample.x = Slide->newSample.x;
	}
	if (ABS((AccSample->y - Slide->newSample.y)) > DYNAMIC_PRECISION)
	{
		Slide->oldSample.y = Slide->newSample.y;
		Slide->newSample.y = AccSample->y;
		res = 1;
	}
	else
	{
		Slide->oldSample.y = Slide->newSample.y;
	}

	if (ABS((AccSample->z - Slide->newSample.z)) > DYNAMIC_PRECISION)
	{
		Slide->oldSample.z = Slide->newSample.z;
		Slide->newSample.z = AccSample->z;
		res = 1;
	}
	else
	{
		Slide->oldSample.z = Slide->newSample.z;
	}
	return res;
}

/*判断当前最活跃轴*/
char SelectMostActiveAxis(Peak_Value_t* Peak)
{
	char res = MOST_ACTIVE_NULL;
	short xChange = ABS((Peak->newMax.x - Peak->newMin.x));
	short yChange = ABS((Peak->newMax.y - Peak->newMin.y));
	short zChange = ABS((Peak->newMax.z - Peak->newMin.z));

	if (xChange > yChange && xChange > zChange && xChange >= ACTIVE_PRECISION)
	{
		res = MOST_ACTIVE_X;
	}
	else if (yChange > xChange && yChange > zChange && yChange >= ACTIVE_PRECISION)
	{
		res = MOST_ACTIVE_Y;
	}
	else if (zChange > xChange && zChange > yChange && zChange >= ACTIVE_PRECISION)
	{
		res = MOST_ACTIVE_Z;
	}
	return res;
}

/*判断是否走步*/
unsigned int StepCalculate(Peak_Value_t* Peak, Slide_Reg_t* Slide)
{
	char res = SelectMostActiveAxis(Peak);
	switch (res)
	{
	case MOST_ACTIVE_NULL:
	{
		//fix
		break;
	}
	case MOST_ACTIVE_X:
	{
		short ThresholX = (Peak->oldMax.x + Peak->oldMin.x) / 2;
		if (Slide->oldSample.x > ThresholX && Slide->newSample.x < ThresholX)
		{
			StepCnt++;
		}
		break;
	}
	case MOST_ACTIVE_Y:
	{
		short ThresholdY = (Peak->oldMax.y + Peak->oldMin.y) / 2;
		if (Slide->oldSample.y > ThresholdY && Slide->newSample.y < ThresholdY)
		{
			StepCnt++;
		}
		break;
	}
	case MOST_ACTIVE_Z:
	{
		short ThresholdZ = (Peak->oldMax.z + Peak->oldMin.z) / 2;
		if (Slide->oldSample.z > ThresholdZ && Slide->newSample.z < ThresholdZ)
		{
			StepCnt++;
		}
		break;
	}
	default:
		break;
	}
	return StepCnt;
}

uint32_t Pedometer_Update(int ax, int ay, int az) {

	static uint8_t Idx = 0;
	static uint8_t DownSampleCount = 0;

	if((++DownSampleCount) < (ORIGIN_FREQ / PEDOMETER_FREQ)){
		return StepCnt;
	}
	DownSampleCount = 0;

	AccSample.x = ax;
	AccSample.y = ay;
	AccSample.z = az;

	//平均值结构体数据存储
	FilterAvg.info[Idx].x = AccSample.x;
	FilterAvg.info[Idx].y = AccSample.y;
	FilterAvg.info[Idx].z = AccSample.z;
	
	/* Update the filter data index. */
	Idx++;
	Idx = Idx > 4 ? 0 : Idx;
	/* Mean data filter.             */
	FilterCalculate(&FilterAvg, &Sample);	
	/* Dymaic update peak max and peak min. */
	PeakParaUpdate(&Peak, &Sample);		
	SlideUpdate(&Slide, &Sample);	
	/* Calculate the step.     */
	StepCalculate(&Peak, &Slide);

	return StepCnt;
}

void Pedomter_Init()
{
	/* Reset the step count. */
	StepCnt = 0;
	/* Init step peak struct. */
	PeakValueInit(&Peak);
}

