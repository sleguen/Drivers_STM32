#ifndef _LIB_FIFO_H_

/* macros ============================================================== */
/* constants =========================================================== */
typedef unsigned char u8;
/* types =============================================================== */
/* structures ========================================================== */
/* internal public functions =========================================== */
/* entry points ======================================================== */
/* public variables ==================================================== */
typedef struct
{
    u8* u8p_FrameData;
    u8 u8p_Read;
    u8 u8p_Write;
    u8 U8p_Flag;
}s_Fifo;

typedef enum
{
    FIFO_OK,
    FIFO_EMPTY,
    FIFO_OVF,
    FIFO_FULL,
    FIFO_NB_ERROR,
}e_FifoStatus;

//extern s_Fifo s_FifoUartRead;
/* inline public functions  ============================================ */
/* public functions  =================================================== */
extern void vd_lib_fifo_Init(void);
extern u8 u8_lib_fifo_Set(const u8 iu8_DataIn);
extern u8 u8_lib_fifo_Get(u8* iu8p_DataRead);

#endif //_LIB_FIFO_H_
