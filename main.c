
#include "BSM_API.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <float.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))  
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int main(int argc, char* argv[])
{
	unsigned short uw_DataCnt = DEF_CHANNEL_NUM * DEF_DTRB_NUM;
	int	ui_TestCnt,T;
	DTRB_DATA	*pInputDataTable;
	DTRB_DATA	*pOutputDataTable;
	DTRB_DATA	*pCriterDataTable;
		
	clock_t startTime, endTime;
  	double dProcessExcuteTime;
	double dAveRuntime1, dAveRuntime2, dMinRuntime1, dMinRuntime2, dMaxRuntime1, dMaxRuntime2;
	
	dMinRuntime1 = dMinRuntime2 =  DBL_MAX;
	dAveRuntime1 = dAveRuntime2 = dMaxRuntime1 = dMaxRuntime2 = 0;
	
	srand(time(NULL));

	if(argc == 1)
	{
		printf("please input test count.\r\n");
		return 0;
	}

	printf("Hello\r\n");
	
	pInputDataTable 	= (DTRB_DATA *)malloc(sizeof(DTRB_DATA) * uw_DataCnt);
	pOutputDataTable	= (DTRB_DATA *)malloc(sizeof(DTRB_DATA) * uw_DataCnt);
	pCriterDataTable 	= (DTRB_DATA *)malloc(sizeof(DTRB_DATA) * uw_DataCnt);

	ui_TestCnt = atoi(argv[1]);
	T = ui_TestCnt;
	printf("Test Count : %d\r\n", ui_TestCnt);	
	printf("=====================================================================\n");
	while(T--)
	{
		for(int i = 0; i < uw_DataCnt; i++ )
		{
			pCriterDataTable[i].sw_Amplitude 	= 	255;
			pCriterDataTable[i].sw_Phase		=	255;
			pInputDataTable[i].sw_Amplitude		=	rand () % 512;
			pInputDataTable[i].sw_Phase			=	rand () % 512;
		}

		startTime = clock();
		BSM_API_Correction(pCriterDataTable, pInputDataTable, pOutputDataTable);
		endTime = clock();
		dProcessExcuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC;
		dAveRuntime1+= dProcessExcuteTime;
		dMinRuntime1 = MIN(dMinRuntime1, dProcessExcuteTime);
		dMaxRuntime1 = MAX(dMaxRuntime1, dProcessExcuteTime);
	  	printf("Method#1(with Look Up Table)	:	%f(ms)\n", dProcessExcuteTime);

		startTime = clock();
		BSM_API_Correction_Seq(pCriterDataTable, pInputDataTable, pOutputDataTable);
		endTime = clock();
		dProcessExcuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC;
		dAveRuntime2+= dProcessExcuteTime;		
		dMinRuntime2 = MIN(dMinRuntime2, dProcessExcuteTime);
		dMaxRuntime2 = MAX(dMaxRuntime2, dProcessExcuteTime);
		
	  	printf("Method#2(Sequential input)	:	%f(ms)\n", dProcessExcuteTime);
	}

	dAveRuntime1 /= (double)ui_TestCnt;
	dAveRuntime2 /= (double)ui_TestCnt;	
	printf("=====================================================================\n");
	printf("Method#1(with Look Up Table)	: MIN(%fms) MAX(%fms) AVE(%fms)\n", dMinRuntime1, dMaxRuntime1, dAveRuntime1);
	printf("Method#2(Sequential input)	: MIN(%fms) MAX(%fms) AVE(%fms)\n", dMinRuntime2, dMaxRuntime2, dAveRuntime2);

	//BSM_API_Display(pCriterDataTable, pInputDataTable, pOutputDataTable);
	

	free(pCriterDataTable);
	free(pInputDataTable);
	free(pOutputDataTable);
	
	return 0;
}
