 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi.c
 *
 * Description: Source file for Spi Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/
 
 #include "Spi.h"
 #include "Spi_Regs.h"
 #include "Spi_Irq.h"
 /* AUTOSAR checking between Det and SPI Modules */
 #if (SPI_DEV_ERROR_DETECT == STD_ON)

 #include "Det.h"
 #if ((DET_AR_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
 ||	 (DET_AR_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
 #error "The AR version of Det.h does not match the AR version of Spi.h"
 #endif

 #endif

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/


typedef struct
{
    Spi_StatusType      spi_status;
    Spi_HWStateType     hw_status[SPI_MAX_HW_UNITS];
    Spi_JobResultType   job_status[SPI_CONFIGURED_JOBS];
    Spi_SeqResultType   seq_status[SPI_CONFIGURED_SEQUENCES];
#if(SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
    Spi_AsyncModeType   async_mode;
#endif
}Spi_GlobalType;

STATIC Spi_GlobalType Spi_GlobalInfo =
{
    SPI_UNINIT,
    {HWUnit_DISABLE},
    {SPI_JOB_OK},
    {SPI_SEQ_OK}
#if(SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
    ,SPI_POLLING_MODE
#endif
};

STATIC const Spi_ConfigType *Spi_ConfigPtr=NULL_PTR;
STATIC Spi_BufferInfoType   Spi_ChannelBuffers[SPI_CONFIGURED_CHANNELS];
/*******************************************************************************
 *                    Global Macros and Static Functions                       *
 *******************************************************************************/

STATIC void Spi_HWInit(const Spi_HWUnitConfigType* HWunitConfig)
{
    boolean error = FALSE;
    uint8 loop_index=0;
    Spi_HWUnitType   HWunit_id;
    const Spi_HWUnitConfigType  *Hwunit=NULL_PTR;
    for(loop_index=0;loop_index<SPI_MAX_HW_UNITS;loop_index++)
    {
        if(HWUnits_Configs[loop_index].HWunit_state == HWUnit_ENABLE)
        {
            Hwunit = &HWunitConfig[loop_index];
            HWunit_id = Hwunit->HWunit_id;
        /*
         * Error Detection and reporting to Det Module is enabled by
         * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
         */
        #if (SPI_DEV_ERROR_DETECT == STD_ON)
            /* Check if input pointer is not Null pointer */
            if(NULL_PTR == Hwunit)
            {
                /* Report to DET  */
                Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_HW_INIT_SID, SPI_E_PARAM_POINTER);
                error = TRUE;
            }
            /* Check if the spi driver is already initialized */
            if(SPI_MAX_HW_UNITS <= HWunit_id)
            {
                /* Report to DET  */
                Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_HW_INIT_SID, SPI_E_PARAM_UNIT);
                error = TRUE;
            }
        #endif
            if(FALSE == error)
            {
                /* Enable the clock according to the appropriate SSI module */
                SYSCTL_RCGCSSI_R |= 1<<HWunit_id;
                /* Disable the SSI Operation */
                SPI(HWunit_id)->CR1 &= ~(1<<SPI_CR1_SSE);
                /* Enable the SSI as a Master */
                SPI(HWunit_id)->CR1 &= ~(1<<SPI_CR1_MS);
                /* Select the clock source needed for the SSI module */
                SPI(HWunit_id)->CC = Hwunit->clk_source;
                /* Select the mode of operation as a FreeScale SPI */
                SPI(HWunit_id)->CR0 &= ~(3<<SPI_CR0_FRF);
            }
        }

    }
}

STATIC void Spi_SetBaudRate(Spi_HWUnitType hwunit_id, Spi_BaudeRateType baudrate)
{
    uint64 SysClk = 0;
    uint8 CPSR_Value=1;
    uint8 SCR_Value=0;
    if((HWUnits_Configs[hwunit_id].clk_source) == SPI_CLKSRC_PIOSC)
    {
        SysClk = 16000000;
    }else
    {
        /*TODO*/
        /* Should read the actual value of the System Clock */
        SysClk = 16000000;
    }
/*
 * Error Detection and reporting to Det Module is enabled by
 * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
 */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if((baudrate > SysClk/2) || (baudrate > SPI_MAX_BAUD_RATE))
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_INIT_SID, SPI_E_PARAM_CLOCK);
    }
#endif
    /* Clock Rate (BaudRate) Setting */
    for(CPSR_Value=1;CPSR_Value<254;CPSR_Value++)
    {
        CPSR_Value++;
        SCR_Value = (SysClk/(CPSR_Value*baudrate))-1;

        if(SCR_Value < 1)
        {
        #if (SPI_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_INIT_SID, SPI_E_PARAM_CLOCK);
        #endif
        }
        else if(SCR_Value <= 255)
        {
            /*@violate MISRA Rules*/
            break;
        }else{ /* Run the next loop */ }
    }
    SPI(hwunit_id)->CPSR = CPSR_Value;
    SPI(hwunit_id)->CR0 &= ~(0xFF<<SPI_CR0_SCR);
    SPI(hwunit_id)->CR0 |= (SCR_Value<<SPI_CR0_SCR);
}

STATIC void Spi_ExternalDeviceInit(const Spi_ExternalDeviceConfigType* ExtDevConfigs)
{
    boolean error = FALSE;
    uint8 loop_index=0;
    const Spi_ExternalDeviceConfigType  *external_dev=NULL_PTR;
    for(loop_index=0;loop_index<SPI_EXTERNAL_DEVICES_NUM;loop_index++)
    {
        external_dev = &ExtDevConfigs[loop_index];
    /*
     * Error Detection and reporting to Det Module is enabled by
     * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
     */
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* Check if input pointer is not Null pointer */
        if(NULL_PTR == external_dev)
        {
            /* Report to DET  */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_EXT_DEV_INIT_SID, SPI_E_PARAM_POINTER);
            error = TRUE;
        }
        /* Check if the spi driver is already initialized */
        if(SPI_MAX_HW_UNITS <= external_dev->hwunit_id)
        {
            /* Report to DET  */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_EXT_DEV_INIT_SID, SPI_E_PARAM_UNIT);
            error = TRUE;
        }
    #endif
        if(FALSE == error)
        {
            /* Chip Select Idle State */
            if((external_dev->CS_Polarity) == CS_POLARITY_LOW) /* Means that the chip select is active low */
            {
                Dio_WriteChannel(external_dev->CS_Id, STD_HIGH);
            }else /* Means that the chip select is active high */
            {
                Dio_WriteChannel(external_dev->CS_Id, STD_LOW);
            }
            /* Disable the SSI Operation */
            SPI(external_dev->hwunit_id)->CR1 &= ~(1<<SPI_CR1_SSE);
            /* Clock Polarity and Phase Settings (SPO and SPH) */
            SPI(external_dev->hwunit_id)->CR0 &= ~(1<<SPI_CR0_SPO);
            SPI(external_dev->hwunit_id)->CR0 |= ((external_dev->Clk_Level)<<SPI_CR0_SPO);

            if((external_dev->shift_edge) == SPI_EDGE_LEADING)
            {
                if((external_dev->Clk_Level) == SPI_CLOCK_IDLE_HIGH)
                {
                    SPI(external_dev->hwunit_id)->CR0 |= (1<<SPI_CR0_SPH);
                }else
                {
                    SPI(external_dev->hwunit_id)->CR0 &= ~(1<<SPI_CR0_SPH);
                }
            }else
            {
                if((external_dev->Clk_Level) == SPI_CLOCK_IDLE_HIGH)
                {
                    SPI(external_dev->hwunit_id)->CR0 &= ~(1<<SPI_CR0_SPH);
                }else
                {
                    SPI(external_dev->hwunit_id)->CR0 |= (1<<SPI_CR0_SPH);
                }
            }
        }
    }
}


/*******************************************************************************
 *                      AutoSAR Function Definitions                           *
 *******************************************************************************/

/************************************************************************************
* Service Name: Spi_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
void Spi_Init (const Spi_ConfigType* ConfigPtr)
{
    boolean error = FALSE;
    uint16 loop_index=0;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/*
 * Error Detection and reporting to Det Module is enabled by
 * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
 */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_INIT_SID, SPI_E_PARAM_POINTER);
        error = TRUE;
    }
    /* Check if the spi driver is already initialized */
    if(SPI_UNINIT != Spi_GlobalInfo.spi_status)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_INIT_SID, SPI_E_ALREADY_INITIALIZED);
        error = TRUE;
    }
#endif
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
    /* In case there are no errors */
    if(FALSE == error)
    {
      /* Assign a pointer to the configuration structure */
      Spi_ConfigPtr = &SpiConfigurations;
      /* Initialize the HW peripherals units */
      Spi_HWInit(HWUnits_Configs);
      /* Initialize the connected external devices */
      Spi_ExternalDeviceInit(ExtDevices_Configs);

      /* Set the SPI driver state to IDLE */
      Spi_GlobalInfo.spi_status = SPI_IDLE;
      /* Set the jobs status to JOB_OK */
      for(loop_index=0; loop_index<SPI_CONFIGURED_JOBS; loop_index++)
      {
          Spi_GlobalInfo.job_status[loop_index] = SPI_JOB_OK;
      }
      /* Set the sequences status to SEQ_OK */
      for(loop_index=0; loop_index<SPI_CONFIGURED_SEQUENCES; loop_index++)
      {
          Spi_GlobalInfo.seq_status[loop_index] = SPI_SEQ_OK;
      }
      /* Set the asynchronous mode to POLLING mode ***Only in LEVEL_2*** */
#if(SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
      Spi_GlobalInfo.async_mode = SPI_POLLING_MODE;
#endif
      /* Disable the global interrupts for the Spi modules */
      for(loop_index=0; loop_index<SPI_MAX_HW_UNITS; loop_index++)
      {
          Spi_NVICDisable(Spi_IRQNum[loop_index]);
      }

      /* Initialize the IB Channels */
      for(loop_index=0; loop_index<SPI_CONFIGURED_CHANNELS; loop_index++)
      {
          if(SPI_IB == (Spi_ConfigPtr->channels[loop_index].buff_usage))
          {
              Spi_ChannelBuffers[loop_index].channel_id = Spi_ConfigPtr->channels[loop_index].channel_id;
              Spi_ChannelBuffers[loop_index].data_width = Spi_ConfigPtr->channels[loop_index].data_width;
              Spi_ChannelBuffers[loop_index].data_length = Spi_ConfigPtr->channels[loop_index].data_length;
              Spi_ChannelBuffers[loop_index].tx_data_ptr = Spi_ConfigPtr->channels[loop_index].buff_descrip.tx_data_ptr;
              Spi_ChannelBuffers[loop_index].rx_data_ptr = Spi_ConfigPtr->channels[loop_index].buff_descrip.rx_data_ptr;
          }else
          {
              Spi_ChannelBuffers[loop_index].tx_data_ptr = NULL_PTR;
              Spi_ChannelBuffers[loop_index].rx_data_ptr = NULL_PTR;
          }
      }
    }else{/* Nothing to do here */}
}

/************************************************************************************
* Service Name: Spi_DeInit
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - E_OK (DeInit Accepted) or E_NOT_OK (DeInit Not Accepted)
* Description: Function to DeInitialize the Spi module.
************************************************************************************/
Std_ReturnType Spi_DeInit (void)
{
    Std_ReturnType error = E_OK;
    uint16 loop_index=0;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/*
 * Error Detection and reporting to Det Module is enabled by
 * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
 */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if the spi driver is uninitialized */
    if(SPI_UNINIT == Spi_GlobalInfo.spi_status)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_DEINIT_SID, SPI_E_UNINIT);
        error = E_NOT_OK;
    }
    /* Check if the spi driver is Busy */
    if(SPI_BUSY == Spi_GlobalInfo.spi_status)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_DEINIT_SID, SPI_E_BUSY);
        error = E_NOT_OK;
    }
#endif
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
    /* In case there are no errors */
    if(E_OK == error)
    {
        for(loop_index=0; loop_index<SPI_MAX_HW_UNITS; loop_index++)
        {
            SPI(loop_index)->CR1 = 0x00;
            SPI(loop_index)->CPSR = 0x00;
            SPI(loop_index)->CR0 = 0x00;
            SPI(loop_index)->IM = 0x00;
            SPI(loop_index)->CC = 0x00;
        }
        Spi_GlobalInfo.spi_status = SPI_UNINIT;
    }else
    {
        /* Nothing to do here yet */
    }
    return error;
}

/************************************************************************************
* Service Name: Spi_WriteIB
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - The Channel's ID
*                  DataBufferPtr - Pointer to the source of the data to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - E_OK (WriteIB Accepted) or E_NOT_OK (WriteIB Not Accepted)
* Description: Function to write data in an existing IB Channel Buffer.
************************************************************************************/
#if(SPI_CHANNEL_BUFFERS_ALLOWED != SPI_BUFF_USAGE_EB)
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel,
                            const Spi_DataBufferType* DataBufferPtr)
{
    Std_ReturnType error = E_OK;
    uint16 loop_index=0;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/*
 * Error Detection and reporting to Det Module is enabled by
 * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
 */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if the spi driver is uninitialized */
    if(SPI_UNINIT == Spi_GlobalInfo.spi_status)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_WRITE_IB_SID, SPI_E_UNINIT);
        error = E_NOT_OK;
    }
    /* Check if the channel id is out of range */
    if(SPI_CONFIGURED_CHANNELS <= Channel)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_WRITE_IB_SID, SPI_E_PARAM_CHANNEL);
        error = E_NOT_OK;
    }
#endif
    /* Check if the channel doesn't have IB buffer */
    if(SPI_EB == Spi_ConfigPtr->channels[Channel].buff_usage)
    {
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_WRITE_IB_SID, SPI_E_PARAM_CHANNEL);
#endif
        error = E_NOT_OK;
    }
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
    /* In case there are no errors */
    if(E_OK == error)
    {
        if(NULL_PTR == DataBufferPtr)
        {
            /* Store the default data value in the channel's buffer */
            *(Spi_ChannelBuffers[Channel].tx_data_ptr) = Spi_ConfigPtr->channels[Channel].default_data;
        }else
        {
            for(loop_index=0; loop_index<(Spi_ChannelBuffers[Channel].data_length) ;loop_index++)
            {
                *(Spi_ChannelBuffers[Channel].tx_data_ptr) = *(DataBufferPtr+loop_index);
                (Spi_ChannelBuffers[Channel].tx_data_ptr)++;
            }
        }
    }else
    {
        /* Nothing to do here yet */
    }
    return error;
}
#endif

/************************************************************************************
* Service Name: Spi_AsyncTransmit
* Service ID[hex]: 0x03
* Sync/Async: Asynchronous
* Reentrancy: Reentrant
* Parameters (in): Sequence - The ID of the sequence.
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - E_OK (Transmission Accepted) or E_NOT_OK (Transmission Not Accepted)
* Description: Function to trigger the asynchronous transmission of a sequence.
************************************************************************************/
#if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
Std_ReturnType Spi_AsyncTransmit (Spi_SequenceType Sequence)
{
    return 0;
}
#endif

/************************************************************************************
* Service Name: Spi_ReadIB
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
#if(SPI_CHANNEL_BUFFERS_ALLOWED != SPI_BUFF_USAGE_EB)
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel,
                           Spi_DataBufferType* DataBufferPointer)
{
    return 0;
}
#endif

/************************************************************************************
* Service Name: Spi_SetupEB
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Std_ReturnType Spi_SetupEB (Spi_ChannelType Channel,
                            const Spi_DataBufferType* SrcDataBufferPtr,
                            Spi_DataBufferType* DesDataBufferPtr,
                            Spi_NumberOfDataType Length)
{
    return 0;
}

/************************************************************************************
* Service Name: Spi_GetStatus
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Spi_StatusType Spi_GetStatus (void)
{
    return (Spi_StatusType)0;
}

/************************************************************************************
* Service Name: Spi_GetJobResult
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Spi_JobResultType Spi_GetJobResult (Spi_JobType Job)
{
    return (Spi_JobResultType)0;
}

/************************************************************************************
* Service Name: Spi_GetSequenceResult
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Spi_SeqResultType Spi_GetSequenceResult (Spi_SequenceType Sequence)
{
    return (Spi_SeqResultType)0;
}

/************************************************************************************
* Service Name: Spi_GetVersionInfo
* Service ID[hex]: 0x09
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfoPtr - Pointer to Structure type with the version's parameters (major, minor, patch)
* Return value: None
* Description: Function to return the version information of the Spi module.
************************************************************************************/
#if (SPI_VERSION_INFO_API == STD_ON)
void Spi_GetVersionInfo( Std_VersionInfoType* VersionInfoPtr )
{
    boolean error = FALSE;
/**************************************************************************************/
/*                              Start of Error Checking                               */
/**************************************************************************************/
/*
 * Error Detection and reporting to Det Module is enabled by
 * assigning STD_ON to SPI_DEV_ERROR_DETECT in Spi_Cfg.h
 */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Report to DET  */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,SPI_GET_VERSION_INFO_SID, SPI_E_PARAM_POINTER);
        error = TRUE;
    }
#endif
/**************************************************************************************/
/*                              End of Error Checking                                 */
/**************************************************************************************/

/**************************************************************************************/
/*                              Function Implementation                               */
/**************************************************************************************/
    /* In case there are no errors */
    if(FALSE == error)
    {
        /* Send the SPI Module ID */
        VersionInfoPtr->moduleID         = (uint16)SPI_MODULE_ID;
        /* Send the SPI Module Software Major Version */
        VersionInfoPtr->sw_major_version = (uint8)SPI_SW_MAJOR_VERSION;
        /* Send the SPI Module Software Minor Version */
        VersionInfoPtr->sw_minor_version = (uint8)SPI_SW_MINOR_VERSION;
        /* Send the SPI Module Software Patch Version */
        VersionInfoPtr->sw_patch_version = (uint8)SPI_SW_PATCH_VERSION;
        /* Send the SPI Module Vendor ID */
        VersionInfoPtr->vendorID         = (uint16)SPI_VENDOR_ID;
    }else
    {
        /* Nothing to do here yet */
    }
}
#endif

/************************************************************************************
* Service Name: Spi_SyncTransmit
* Service ID[hex]: 0x0A
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Std_ReturnType Spi_SyncTransmit (Spi_SequenceType Sequence)
{
    return 0;
}

/************************************************************************************
* Service Name: Spi_GetHWUnitStatus
* Service ID[hex]: 0x0B
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit)
{
    return (Spi_StatusType)0;
}

/************************************************************************************
* Service Name: Spi_Cancel
* Service ID[hex]: 0x0C
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
void Spi_Cancel (Spi_SequenceType Sequence)
{

}

/************************************************************************************
* Service Name: Spi_SetAsyncMode
* Service ID[hex]: 0x0D
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Spi module.
************************************************************************************/
Std_ReturnType Spi_SetAsyncMode (Spi_AsyncModeType Mode)
{
    return 0;
}

/************************************************************************************/
/************************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% NON AUTOSAR FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/************************************************************************************/
/************************************************************************************/

/************************************************************************************
* Service Name: Spi_StateChange
* Service ID[hex]: 0xEE
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel - Id of the channel in the configuration struct.
*                  State   - The state of the channel to be changed
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Non AutoSAR Function to change the state of the channel in the Static Global Struct.
*              Specially used by another source files to change this static struct
************************************************************************************/
Std_ReturnType SSI_Write(SSI_ID ssid, uint16_t data)
{
    SSI_WaitFIFO_NotFull(ssid);
    SSI(ssid)->DR = data;
    SSI_BusyWait(ssid);
    return SSI_OK;
}

uint16_t SSI_Read(SSI_ID ssid)
{
    if(isRxFIFIO_NotEMPTY(ssid))
        return SSI(ssid)->DR;
    return SSI_ERROR_FIFO_EMPTY;
}
