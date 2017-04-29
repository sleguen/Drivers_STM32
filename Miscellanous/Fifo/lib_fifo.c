/**
 * \file lib_fifo.c
 * \brief File who provides function to manage a fifo
 * \author S. LE GUEN
 * \date 11 Septembre 2016
 */
#include "lib_fifo.h"

/* macros ============================================================== */
#define FIFO_READ_SIZE (128u)
/* constants =========================================================== */
/* types =============================================================== */
/* structures ========================================================== */
/* private variables =================================================== */
s_Fifo s_FifoUartRead;
u8 u8_FifoRead[FIFO_READ_SIZE];
/* private functions =================================================== */
/* internal public functions =========================================== */
/* entry points ======================================================== */
/* public variables ==================================================== */
/* public function ===================================================== */

/**
 * \fn void vd_lib_fifo_Init(s_Fifo* s_InitFifo)
 * \brief Initialisation de la librairie Fifo
 *
 * \param none
 * \return none
 */
void vd_lib_fifo_Init(void)
{
    s_FifoUartRead.u8p_FrameData = &u8_FifoRead[0];
    s_FifoUartRead.u8p_Read      = 0u;
    s_FifoUartRead.u8p_Write     = 0u;
    s_FifoUartRead.U8p_Flag      = 0u;
}

/**
 * \fn u8 u8_lib_fifo_Set(const u8 iu8_DataIn)
 * \brief Write a data into the fifo
 *
 * \param[IN] iu8_DataIn Data to be written in the fifo
 * \return e_FifoStatus
 */
u8 u8_lib_fifo_Set(const u8 iu8_DataIn)
{

    //Verify if the write index is not equal to the fifo size
    /**
    *@todo Tester pour la première condition du IF. Reste à faire pour la deuxième
    *      c'est à dire quand on écrase en écriture une donnée non-lue !
    */
    if( ( s_FifoUartRead.u8p_Write == FIFO_READ_SIZE ) ||
        ( (s_FifoUartRead.u8p_Write + 1) == s_FifoUartRead.u8p_Read) )
    {
        //Fifo is full
        s_FifoUartRead.U8p_Flag = FIFO_FULL;
    }

    if( s_FifoUartRead.U8p_Flag == FIFO_OK )
    {
        s_FifoUartRead.u8p_FrameData[s_FifoUartRead.u8p_Write] = iu8_DataIn;
        s_FifoUartRead.u8p_Write++;
    }

    return s_FifoUartRead.U8p_Flag;
}

/**
 * \fn u8 u8_lib_fifo_Get(u8* iu8p_DataRead)
 * \brief Write a data into the fifo
 *
 * \param[OUT] *iu8p_DataRead the value read in the fifo
 * \return e_FifoStatus
 */
u8 u8_lib_fifo_Get(u8* iu8p_DataRead)
{
    //Verify if there is no read overun
    if( (s_FifoUartRead.u8p_Read + 1) > s_FifoUartRead.u8p_Write )
    {
        //Fifo is full
        s_FifoUartRead.U8p_Flag = FIFO_OVF;
    }

    if( s_FifoUartRead.U8p_Flag == FIFO_OK )
    {
        *iu8p_DataRead = s_FifoUartRead.u8p_FrameData[s_FifoUartRead.u8p_Read];
        s_FifoUartRead.u8p_Read++;
    }

    return s_FifoUartRead.U8p_Flag;
}
