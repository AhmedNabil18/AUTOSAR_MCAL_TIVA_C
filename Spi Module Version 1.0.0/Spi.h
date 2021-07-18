 /******************************************************************************
 *
 * Module: Spi
 *
 * File Name: Spi.h
 *
 * Description: Header file for Spi Module.
 *
 * Author: Ahmed Nabil
 ******************************************************************************/


#ifndef SPI_H_
#define SPI_H_


/* Id for the company in the AUTOSAR
 * for example Ahmed Nabil's ID = 2910 */
#define SPI_VENDOR_ID		(2910U)

/* SPI Module ID */
#define SPI_MODULE_ID		(83U)

/* SPI Instance ID */
#define SPI_INSTANCE_ID		(0U)

/*
 * Module Version 1.0.0
 */
#define SPI_SW_MAJOR_VERSION           (1U)
#define SPI_SW_MINOR_VERSION           (0U)
#define SPI_SW_PATCH_VERSION           (0U)

/*
 * AutoSAR Version 4.0.3
 */
#define SPI_AR_RELEASE_MAJOR_VERSION   (4U)
#define SPI_AR_RELEASE_MINOR_VERSION   (0U)
#define SPI_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard Types */
#include "Std_Types.h"
/* AUTOSAR checking between Std Types and SPI Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* SPI Pre-Compile Configuration Header file */
#include "Spi_Cfg.h"

/* AUTOSAR Version checking between Spi_Cfg.h and Spi.h files */
#if ((SPI_CFG_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
||  (SPI_CFG_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
||  (SPI_CFG_AR_RELEASE_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Spi_Cfg.h does not match the expected version"
#endif
/* AUTOSAR Version checking between Spi.h and Dio.h files */
#if ((SPI_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
||  (SPI_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
||  (SPI_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Spi_Cfg.h does not match the expected version"
#endif
/* Software Version checking between Spi_Cfg.h and Spi.h files */
#if ((SPI_CFG_SW_MAJOR_VERSION != SPI_SW_MAJOR_VERSION)\
||  (SPI_CFG_SW_MINOR_VERSION != SPI_SW_MINOR_VERSION)\
||  (SPI_CFG_SW_PATCH_VERSION != SPI_SW_PATCH_VERSION))
#error "The SW version of Spi_Cfg.h does not match the expected version"
#endif

/* Including non AutoSAR files */
#include "Common_Macros.h"

/* Number of SPI HW peripherals/buses in the microcontroller */
#define SPI_MAX_HW_UNITS            (4U)

#define SPI_MAX_BAUD_RATE           (25000000U) /* in Hz */

#define SPI_MAX_DATA_WIDTH          (16U) /* in Bits */

#define SPI_MAX_ELEMENTS_NUM        (65536U)
/******************************************************************************
 *                        API Service Id Macros                               *
 ******************************************************************************/
/* Service ID for Spi_Init API */
#define SPI_INIT_SID							(uint8)0x00

/* Service ID for Spi_DeInit API */
#define SPI_DEINIT_SID							(uint8)0x01

/* Service ID for Spi_WriteIB API */
#define SPI_WRITE_IB_SID        				(uint8)0x02

/* Service ID for Spi_AsyncTransmit API */
#define SPI_ASYNC_TRANSMIT_SID			    	(uint8)0x03

/* Service ID for Spi_ReadIB API */
#define SPI_READ_IB_SID		    				(uint8)0x04

/* Service ID for Spi_SetupEB API */
#define SPI_SETUP_EB_SID						(uint8)0x05

/* Service ID for Spi_GetStatus API */
#define SPI_GET_STATUS_SID		        		(uint8)0x06

/* Service ID for Spi_GetJobResult API */
#define SPI_GET_JOB_RESULT_SID	        		(uint8)0x07

/* Service ID for Spi_GetSequenceResult API */
#define SPI_GET_SEQUENCE_RESULT_SID             (uint8)0x08

/* Service ID for Spi_GetVersionInfo API */
#define SPI_GET_VERSION_INFO_SID                (uint8)0x09

/* Service ID for Spi_SyncTransmit API */
#define SPI_SYNC_TRANSMIT_SID					(uint8)0x0A

/* Service ID for Spi_GetHWUnitStatus API */
#define SPI_GET_HW_UNIT_STATUS_SID				(uint8)0x0B

/* Service ID for Spi_Cancel API */
#define SPI_CANCEL_SID	        				(uint8)0x0C

/* Service ID for Spi_SetAsyncMode API */
#define SPI_SET_ASYNC_MODE_SID                  (uint8)0x0D

/* Service ID for Spi_HWInit API */
#define SPI_HW_INIT_SID                         (uint8)0x0E

/* Service ID for Spi_ExternalDeviceInit API */
#define SPI_EXT_DEV_INIT_SID                    (uint8)0x0F
/*******************************************************************************
 *                          DET Error Codes                                    *
 *******************************************************************************/
/* DET code for passing an invalid channel as a parameter to an API */
#define SPI_E_PARAM_CHANNEL                     (uint8)0x0A

/* DET code for using values out of the specified range on the Job Parameter */
#define SPI_E_PARAM_JOB 						(uint8)0x0B

/* DET code for using values out of the specified range on the Sequence Parameter */
#define SPI_E_PARAM_SEQ							(uint8)0x0C

/* DET code for using a data length out of the specified range */
#define SPI_E_PARAM_LENGTH                      (uint8)0x0D

/* DET code for using a HWUnit with a value out of the specified range */
#define SPI_E_PARAM_UNIT						(uint8)0x0E

/* DET code for passing a NULL pointer as a parameter to any API */
#define SPI_E_PARAM_POINTER                     (uint8)0x10

/* DET code for calling API service when module is uninitialized */
#define SPI_E_UNINIT                            (uint8)0x1A

/* DET code for calling API service when module is Busy */
#define SPI_E_BUSY                              (uint8)0x2A

/* DET code for calling Spi_Init while the SPI has already been initialized before */
#define SPI_E_ALREADY_INITIALIZED				(uint8)0x4A

/* DET code for assigning out ranged clock rate */
#define SPI_E_PARAM_CLOCK                       (uint8)0xAA
/*******************************************************************************
 *                          DEM Error Codes                                    *
 *******************************************************************************/
/* DEM code for calling services in a wrong sequence */
#define SPI_E_SEQ_PENDING                       (uint8)0x2A

/* DEM code for calling synchronus transmission service at wrong time */
#define SPI_E_SEQ_IN_PROCESS                    (uint8)0x3A

/*
 * Production Error issued when any error bit inside the SPI hardware
 * transmit status register is raised
 * This Error is reported to the Dem module using Dem_SetEventStatus() API
 * Defining the status of the Detection
 *      if Failed >> DEM_EVENT_STATUS_FAILED
 *      if Passed >> DEM_EVENT_STATUS_PASSED
 */
#define SPI_E_HARDWARE_ERROR                    (uint8)0x5A

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Module Pins and PCTL values
 */
typedef uint8 Spi_ClkPinType;
typedef uint8 Spi_MOSIPinType;
typedef uint8 Spi_MISOPinType;
typedef uint8 Spi_FSSPinType;

/*
 * Clock Source Type
 */
typedef uint8 Spi_ClkSourceType;

/*
 * Enumeration Type >> Spi_StatusType <<
 * Description: Data type for the status of the SPI driver
 * Can be obtained by calling the API Spi_GetStatus(), or Spi_GetHWUnitStatus()
 */
typedef enum
{
    SPI_UNINIT=0,   /* The driver is not initialized or not usable */
    SPI_IDLE,       /* The driver is not currently transmitting any job */
    SPI_BUSY        /* The driver is currently performing an SPI Job */
}Spi_StatusType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_BufferType <<
 * Description: Data type to specify the usage type of the channel
 */
typedef enum
{
    HWUnit_DISABLE = 0,
    HWUnit_ENABLE
}Spi_HWStateType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_JobResultType <<
 * Description: Data type for the status of Jobs
 * Can be obtained by calling the API Spi_GetJobResult() with the Job ID
 * Default value after reset is SPI_JOB_OK
 */
typedef enum
{
    SPI_JOB_OK = 0, /* The last transmission of the Job has been finished successfully */
    SPI_JOB_PENDING,/* The driver is performing an SPI Job same as SPI_BUSY */
    SPI_JOB_FAILED, /* The last transmission of the job has failed */
    SPI_JOB_QUEUED  /* An asynchronous transmit Job has been accepted and queued waiting to start */
}Spi_JobResultType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_SeqResultType <<
 * Description: Data type for the status of Jobs
 * Can be obtained by calling the API Spi_GetSequenceResult() with the Sequence ID
 * Default value after reset is SPI_SEQ_OK
 */
typedef enum
{
    SPI_SEQ_OK = 0, /* The last transmission of the Sequence has been finished successfully */
    SPI_SEQ_PENDING,/* The driver is performing an SPI Sequence same as SPI_BUSY */
    SPI_SEQ_FAILED, /* The last transmission of the Sequence has failed */
    SPI_SEQ_QUEUED  /* An asynchronous transmit Sequence has been accepted and queued waiting to start */
}Spi_SeqResultType;
/*******************************************************************************/

/*
 * uint64 Type >> Spi_BaudeRateType <<
 * Description: Data type to specify the baudrate for communicating with external device
 */
typedef uint64 Spi_BaudeRateType;
/*******************************************************************************/

/*
 * uint8 Type >> Spi_CSIDType <<
 * Description: Data type to specify the ID for Chip Select
 */
typedef uint8 Spi_CSType;
/*******************************************************************************/


/*
 * uint8 Type >> Spi_CSIDType <<
 * Description: Data type to specify the ID for Chip Select
 */
typedef struct
{
    Spi_CSType        CS_ID;
    Dio_ChannelType   Dio_channel;    /* CS equivalent Channel in Dio Configurations */
}Spi_CSConfigType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_CSPolarityType <<
 * Description: Data type to specify the Chip Select active polarity
 */
typedef enum
{
    CS_POLARITY_LOW = 0,
    CS_POLARITY_HIGH
}Spi_CSPolarityType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_CSSelectionType <<
 * Description: Data type to specify the Chip Select functionality
 * (Manual by GPIO or Automatic by Hardware Peripheral Engine
 */
typedef enum
{
    CS_VIA_GPIO = 0,
    CS_VIA_PERIPHERAL_ENGINE
}Spi_CSSelectionType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_ShiftEdgeType <<
 * Description: Data type to specify the Shift edge mode
 */
typedef enum {
    SPI_EDGE_LEADING = 0,
    SPI_EDGE_TRAILING
} Spi_ShiftEdgeType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_ClockIdleLevelType <<
 * Description: Data type to specify the clock idle state
 */
typedef enum {
    SPI_CLOCK_IDLE_LOW = 0,
    SPI_CLOCK_IDLE_HIGH
} Spi_ClockIdleLevelType;
/*******************************************************************************/

/*
 * float32 Type >> Spi_DelayType <<
 * Description: Data type to specify the delay between clock and Cs
 */
typedef float32 Spi_DelayType;
/*******************************************************************************/

/*
 * uint16 Type >> Spi_NumberOfDataType <<
 * Description: Data type of defining the number of data elements of the type
 *              Spi_DataBufferType to send or receive by Channel
 */
typedef uint16 Spi_NumberOfDataType;
/*******************************************************************************/

/*
 * uint8 Type >> Spi_ChannelType <<
 * Description: Data type to specify the ID for a Channel
 */
typedef uint8 Spi_ChannelType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_DataWidthType <<
 * Description: Data type to specify the width of the data
 */
typedef enum
{
    SPI_DATA_WIDTH_4Bits = 3,
    SPI_DATA_WIDTH_5Bits,
    SPI_DATA_WIDTH_6Bits,
    SPI_DATA_WIDTH_7Bits,
    SPI_DATA_WIDTH_8Bits,
    SPI_DATA_WIDTH_9Bits,
    SPI_DATA_WIDTH_10Bits,
    SPI_DATA_WIDTH_11Bits,
    SPI_DATA_WIDTH_12Bits,
    SPI_DATA_WIDTH_13Bits,
    SPI_DATA_WIDTH_14Bits,
    SPI_DATA_WIDTH_15Bits,
    SPI_DATA_WIDTH_16Bits
}Spi_DataWidthType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_TransferStartType <<
 * Description: Data type to specify the first bit to be transmitted
 */
typedef enum
{
  SPI_TRANSFER_START_LSB = 0,
  SPI_TRANSFER_START_MSB,
} Spi_TransferStartType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_BufferUsageType <<
 * Description: Data type to specify the usage type of the channel
 */
typedef enum
{
    SPI_EB = 0,
    SPI_IB
}Spi_BufferUsageType;
/*******************************************************************************/

/*
 * uint8 Type >> Spi_DataBufferType <<
 * Description: Data type for the application data buffer elements
 */
typedef uint8 Spi_DataBufferType;
/*******************************************************************************/
/*
 * uint16 Type >> Spi_HWUnitType <<
 * Description: Data type to specify the ID for
 *              an SPI HW microcontroller peripheral (unit)
 */
typedef uint8 Spi_HWUnitType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_AsyncModeType <<
 * Description: Specifies the asynchronous mechanism mode
 *              for SPI busses handled asynchronously in LEVEL 2
 * Can be obtained by calling the API Spi_SetAsyncMode() with the needed mode to be set
 */
#if(SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
typedef enum
{
    SPI_POLLING_MODE = 0,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;
#endif
/*******************************************************************************/

/*
 * Structure >> Spi_HWUnitConfigType <<
 * Description: Data type to contain the configuration parameters of a HW Unit
 */
typedef struct
{
    Spi_HWUnitType         HWunit_id;
    Spi_ClkSourceType      clk_source;
    Spi_HWStateType        HWunit_state;
}Spi_HWUnitConfigType;
/*******************************************************************************/

/*
 * Structure >> Spi_BufferDescriptorType <<
 * Description: Data type to hold pointers to channel buffers
 */
typedef struct
{
    Spi_DataBufferType      *tx_data_ptr;
    Spi_DataBufferType      *rx_data_ptr;
}Spi_BufferDescriptorType;
/*******************************************************************************/

/*
 * Structure >> Spi_ChannelConfigType <<
 * Description: Data type to contain the configuration parameters of a Channel
 */
typedef struct
{
    Spi_ChannelType         channel_id;     /* Channel's ID */
    Spi_BufferUsageType     buff_usage;     /* Type of Buffer IB or EB */
    Spi_DataWidthType       data_width;     /* Width of a single data element */
    Spi_DataBufferType      default_data;   /* Default data to be sent */
    Spi_NumberOfDataType    data_length;    /* Number of data elements */
    Spi_TransferStartType   transfer_start; /* Starting position MSB or LSB */
    Spi_BufferDescriptorType buff_descrip;  /* Buffer pointers */
}Spi_ChannelConfigType;
//typedef struct
//{
//    Spi_ChannelType          channel_id;
//    Spi_DataWidthType        data_width;
//    Spi_NumberOfDataType     data_length;
//    Spi_DataType            *tx_data_ptr;
//    Spi_DataType            *rx_data_ptr;
//}Spi_ChannelIBsType;
/*******************************************************************************/
/*
 * uint16 Type >> Spi_ExtDeviceType <<
 * Description: Data type to specify the ID for
 *              an SPI External Device
 */
typedef uint8 Spi_ExtDeviceType;
/*******************************************************************************/

/*
 * Structure >> Spi_ExternalDeviceConfigType <<
 * Description: Data type to contain the configuration parameters of an external device
 */
typedef struct
{
    Spi_HWUnitType          hwunit_id;          /* SPI Module ID */
    Spi_BaudeRateType       baudrate;           /* Clock rate in Hz */
    Spi_CSType              CS_Id;              /* Clock Select ID */
    Spi_CSPolarityType      CS_Polarity;        /* Active polarity of CS */
    Spi_CSSelectionType     CS_Selection;       /* Control of CS */
    Spi_ShiftEdgeType       shift_edge;         /* SPI Clock Phase */
    Spi_ClockIdleLevelType  Clk_Level;          /* SPI Clock Polarity */
    uint8                   CS_Enable;          /* Enable or Disable CS */
//    Spi_DelayType           clk2cs;
//    Spi_DelayType           cs2clk;
}Spi_ExternalDeviceConfigType;
/*******************************************************************************/

/*
 * uint16 Type >> Spi_JobType <<
 * Description: Data type to specify the ID for a Job
 */
typedef uint16 Spi_JobType;
/*******************************************************************************/

/*
 * Pointer to Function Type >> SpiJobEndNotification_Type <<
 * Description: Data type for the end of a job notification function
 */
typedef void (*Spi_JobEndNotificationType)(void);
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_JobPriorityType <<
 * Description: Data type to specify the priority of jobs inside the sequence
 */
typedef enum
{
    JOB_PRIORITY_0 = 0,
    JOB_PRIORITY_1,
    JOB_PRIORITY_2,
    JOB_PRIORITY_3
}Spi_JobPriorityType;
/*******************************************************************************/

/*
 * Structure >> Spi_ChannelListType <<
 * Description: Data type to contain the channels allocated in a job
 */
typedef struct
{
    Spi_ChannelType         channel_index;
    Spi_ChannelType         channel_id;
}Spi_ChannelListType;
/*******************************************************************************/

/*
 * Structure >> Spi_JobConfigType <<
 * Description: Data type to contain the configuration parameters of a Job
 */
typedef struct
{
    Spi_JobType                     job_id;
    Spi_JobPriorityType             job_priority;
    Spi_JobEndNotificationType      job_endNotifi_p2fun;
    Spi_ExtDeviceType               external_dev_id;
    Spi_ChannelListType             Channels[SPI_CONFIGURED_CHANNELS];
}Spi_JobConfigType;
/*******************************************************************************/

/*
 * uint16 Type >> Spi_SequenceType <<
 * Description: Data type to specify the ID for a Sequence
 */
typedef uint8 Spi_SequenceType;
/*******************************************************************************/

/*
 * uint16 Type >> Spi_JobsNumType <<
 * Description: Data type to specify the number of jobs in each sequence
 */
typedef uint16 Spi_JobsNumType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_SeqPriorityType <<
 * Description: Data type to specify the priority of sequences
 * only available if SPI_INTERRUPTIBLE_SEQ_ALLOWED is ON
 */
#if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
typedef enum
{
    SEQ_PRIORITY_0 = 0,
    SEQ_PRIORITY_1,
    SEQ_PRIORITY_2,
    SEQ_PRIORITY_3
}Spi_SeqPriorityType;
/*******************************************************************************/

/*
 * Enumeration Type >> Spi_InterruptibleSeqType <<
 * Description: Data type to specify the interrupt mode of a sequence after each job
 * only available if SPI_INTERRUPTIBLE_SEQ_ALLOWED is ON
 */
typedef enum
{
    SEQ_NON_INTERRUPTIBLE = 0,
    SEQ_INTERRUPTIBLE
}Spi_InterruptibleSeqType;
#endif
/*******************************************************************************/

/*
 * Pointer to Function Type >> Spi_SeqEndNotificationType <<
 * Description: Data type for the end of a sequence notification function
 */
typedef void (*Spi_SeqEndNotificationType)(void);
/*******************************************************************************/

/*
 * Structure >> Spi_SequenceConfigType <<
 * Description: Data type to contain the configuration parameters of a Sequence
 */
typedef struct
{
    Spi_SequenceType                sequence_id;
    Spi_SeqEndNotificationType      seq_endNotifi_p2fun;
    Spi_JobsNumType                 jobsINsequence;
    Spi_JobType                     jobs_id[SPI_CONFIGURED_JOBS];
#if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
    Spi_InterruptibleSeqType        interrupt_mode;
    Spi_SeqPriorityType             seq_priority;
#endif
}Spi_SequenceConfigType;
/*******************************************************************************/

/*
 * Structure >> Spi_ConfigType <<
 * Description: Data type to contain the initialization data for the SPI
 */
typedef struct
{
    Spi_ChannelConfigType       channels[SPI_CONFIGURED_CHANNELS];
    Spi_JobConfigType           jobs[SPI_CONFIGURED_JOBS];
    Spi_SequenceConfigType      sequences[SPI_CONFIGURED_SEQUENCES];
}Spi_ConfigType;
/*******************************************************************************/

/*
 * Structure >> Spi_BufferInfoType <<
 * Description: Data type to contain the Channel buffer information
 */
typedef struct
{
    Spi_ChannelType          channel_id;
    Spi_DataWidthType        data_width;
    Spi_NumberOfDataType     data_length;
    Spi_DataBufferType      *tx_data_ptr;
    Spi_DataBufferType      *rx_data_ptr;
}Spi_BufferInfoType;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Used to initialize the driver */
void Spi_Init (const Spi_ConfigType* ConfigPtr);

/* Used to Deinitialize the driver */
Std_ReturnType Spi_DeInit (void);

/* Writes Data to an IB Channel */
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel,
                            const Spi_DataBufferType* DataBufferPtr);

/* Transmit Data Asynchronously */
Std_ReturnType Spi_AsyncTransmit (Spi_SequenceType Sequence);

/* Read data from an IB Channel */
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel,
                           Spi_DataBufferType* DataBufferPointer);

/* Setup data from EB Channel */
Std_ReturnType Spi_SetupEB (Spi_ChannelType Channel,
                            const Spi_DataBufferType* SrcDataBufferPtr,
                            Spi_DataBufferType* DesDataBufferPtr,
                            Spi_NumberOfDataType Length);

/* Get the status of the driver */
Spi_StatusType Spi_GetStatus (void);

/* Get the status of a Job */
Spi_JobResultType Spi_GetJobResult (Spi_JobType Job);

/* Get the status of a sequence */
Spi_SeqResultType Spi_GetSequenceResult (Spi_SequenceType Sequence);

/* Return the Version info of the Module */
void Spi_GetVersionInfo (Std_VersionInfoType* versioninfo);

/* Transmit Data Synchronously */
Std_ReturnType Spi_SyncTransmit (Spi_SequenceType Sequence);

/* Get the status of the HW unit */
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit);

/* Cancels the specified ongoing sequence */
void Spi_Cancel (Spi_SequenceType Sequence);

/* Set the Asynchronous mode for SPI Busses */
Std_ReturnType Spi_SetAsyncMode (Spi_AsyncModeType Mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

extern const Spi_HWUnitConfigType  HWUnits_Configs[SPI_MAX_HW_UNITS];
extern const Spi_ExternalDeviceConfigType  ExtDevices_Configs[SPI_EXTERNAL_DEVICES_NUM];
extern const Spi_ConfigType SpiConfigurations;
/*******************************************************************************
 *                                 MACROS                                      *
 *******************************************************************************/


#endif
