#ifndef _BSM_API_H_
#define _BSM_API_H_


#define DEF_DTRB_NUM		128  // 4 * 32
#define DEF_CHANNEL_NUM		16	


typedef struct DTRB_Data_t
{
	short	sw_Amplitude;
	short	sw_Phase;
}DTRB_DATA;

extern void BSM_API_Correction(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable);
extern void BSM_API_Correction_Seq(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable);
extern void BSM_API_Display(DTRB_DATA *pCriterDataTable, DTRB_DATA *pInputDataTable, DTRB_DATA *pOutputDataTable);
#endif // #ifndef _BSM_API_H_
