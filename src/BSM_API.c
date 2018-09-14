
#include "BSM_API.h"

#include <stdio.h>

#define BSM_MACRO_SATURATION(input, criter)	( input > criter ? criter : input)

static unsigned char g_Table_LOOKUP[128] = { 1, 2,	5,	6,	7,	11, 12, 13, 14, 19, 20, 21,
			22, 23, 29, 30, 31, 32, 33, 34, 41, 42, 43, 44, 45, 46, 53, 54, 55, 56, 57, 58,
			65, 66, 67, 68, 69, 70, 77, 78, 79, 80, 81, 82, 89, 90, 91, 92, 93, 94, 101,102,
			103,104,105,111,112,113,114,119,120,121,125,126,71, 72, 73, 74, 75, 76, 83, 84,
			85, 86, 87, 88, 95, 96, 97, 98, 99, 100, 106, 107, 108, 109, 110, 115, 116, 117,
			118, 122, 123, 124,	127, 128, 3, 4,	8, 9, 10, 15, 16, 17, 18, 24, 25, 26, 27, 28,
			35, 36, 37, 38, 39, 40, 47, 48, 49, 50, 51, 52, 59, 60, 61, 62, 63, 64 };

void BSM_API_Correction(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable)
{
	register int l_idx, t_idx, c_idx;
	for(c_idx = 0; c_idx < 16; c_idx++)
	{
		for(l_idx = 0; l_idx < 128; l_idx++)
		{
			t_idx = (g_Table_LOOKUP[l_idx] - 1) +  c_idx * 128;
			pOutputDataTable[t_idx].sw_Amplitude = BSM_MACRO_SATURATION(pInputDataTable[t_idx].sw_Amplitude, pCriterDataTable[t_idx].sw_Amplitude);
			pOutputDataTable[t_idx].sw_Phase 	 = BSM_MACRO_SATURATION(pInputDataTable[t_idx].sw_Phase, pCriterDataTable[t_idx].sw_Phase);	
		}
	}
}

void BSM_API_Correction_Seq(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable)
{
	register int i;
	for(i = 0; i < 2048; i++)
	{
		pOutputDataTable[i].sw_Amplitude = BSM_MACRO_SATURATION(pInputDataTable[i].sw_Amplitude, pCriterDataTable[i].sw_Amplitude);
		pOutputDataTable[i].sw_Phase 	 = BSM_MACRO_SATURATION(pInputDataTable[i].sw_Phase, pCriterDataTable[i].sw_Phase);	
	}
}
void BSM_API_Display(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable)
{
	unsigned short uw_DataCnt = DEF_CHANNEL_NUM * DEF_DTRB_NUM;
	register int i;

	for(i = 0; i < uw_DataCnt; i++)
	{
		printf("%d ", pInputDataTable[i].sw_Amplitude);
	}
	printf("\r\n\r\n\r\n");

	for(i = 0; i < uw_DataCnt; i++)
	{
		printf("%d ", pOutputDataTable[i].sw_Amplitude);
	}

	printf("\r\n\r\n\r\n");
	
}