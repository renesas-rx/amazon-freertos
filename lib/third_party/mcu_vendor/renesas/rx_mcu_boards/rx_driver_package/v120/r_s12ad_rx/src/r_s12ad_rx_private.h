/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/******************************************************************************
* File Name    : r_s12ad_rx_private.h
* Description  : Definitions and structures used internally by the driver.
*******************************************************************************/
/******************************************************************************
* History : DD.MM.YYYY Version Description
*           22.07.2013 1.00    Initial Release.
*           21.04.2014 1.20    Updated for RX210 advanced features; RX110/63x support.
*           06.11.2014 1.40    Added RX113 support.
*           20.05.2015 1.50    Added RX231 support.
*           01.03.2016 2.11    Added RX130 and RX230 support.
*           01.10.2016 2.20    Added RX65x support.
*           03.04.2017 2.30    Added RX65N-2MB and RX130-512KB support.
*           03.09.2018 3.00    Added RX66T support.
*           28.12.2018 3.10    Added RX72T support.
*                              Added RX65N 64pins support.
*           05.04.2019 4.00    Deleted the bellow macro definition of RX210, RX631, and RX63N.
*                              - ADC_INVALID_CH_MASK
*                              Added support for GNUC and ICCRX.
*******************************************************************************/

#ifndef S12AD_PRIVATE_H
#define S12AD_PRIVATE_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"
#include "r_s12ad_rx_if.h"

/******************************************************************************
Macro definitions
*******************************************************************************/

#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/* Macro for accessing RX64M/RX65x/RX66T/RX71M/RX72T data register pointers for a given unit (0, 1 or 2) */
#if (defined(BSP_MCU_RX66T) || defined(BSP_MCU_RX72T))
#define GET_DATA_ARR(x)         ((x==0) ? dreg0_ptrs : \
                                 (x==1) ? dreg1_ptrs : \
                                          dreg2_ptrs)
#else
#define GET_DATA_ARR(x)         ((x==0) ? dreg0_ptrs : dreg1_ptrs)
#endif

#if (defined(BSP_MCU_RX110) || defined(BSP_MCU_RX111))

#if BSP_PACKAGE_PINS == 64

/* valid: 1111 1111 0101 1111; invalid 0000 0000 1010 0000 */
#define ADC_INVALID_CH_MASK     (0xFFFF00A0)

#elif BSP_PACKAGE_PINS == 48

/* valid: 1001 1111 0100 0111; invalid 0110 0000 1011 1000 */
#define ADC_INVALID_CH_MASK     (0xFFFF60B8)

#elif BSP_PACKAGE_PINS == 40

/* valid: 0001 1111 0100 0110; invalid 1110 0000 1011 1001 */
#define ADC_INVALID_CH_MASK     (0xFFFFE0B9)

#elif BSP_PACKAGE_PINS == 36

/* valid: 0001 1111 0000 0110; invalid 1110 0000 1111 1001 */
#define ADC_INVALID_CH_MASK     (0xFFFFE0F9)

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif


#ifdef BSP_MCU_RX113

#if BSP_PACKAGE_PINS == 100

/* valid: 0010 0000 1111 1111 1111 1111; invalid 1101 1111 0000 0000 0000 0000 */
#define ADC_INVALID_CH_MASK     (0xFFDF0000)

#elif BSP_PACKAGE_PINS == 64

/* valid: 1111 1111 0000 0111; invalid 0000 0000 1111 1000 */
#define ADC_INVALID_CH_MASK     (0xFFFF00F8)

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif


#ifdef BSP_MCU_RX130

/* Temp sensor and internal v ref are in bit locations 8 and 9 in each mask for rx130 */
#if BSP_PACKAGE_PINS == 100

/* valid: 1111 1111 1111 1111 0000 0011 1111 1111; invalid 0000 0000 0000 0000 1111 1100 0000 0000 */
#define ADC_INVALID_CH_MASK     (0x0000FC00)

#elif BSP_PACKAGE_PINS == 80

/* valid: 0000 0111 0011 1111 0000 0011 1111 1111; invalid 1111 1000 1100 0000 1111 1100 0000 0000 */
#define ADC_INVALID_CH_MASK     (0xF8C0FC00)

#elif BSP_PACKAGE_PINS == 64

/* valid: 0000 0000 0011 1111 0000 0011 1111 1111; invalid 1111 1111 1100 0000 1111 1100 0000 0000 */
#define ADC_INVALID_CH_MASK     (0xFFC0FC00)

#elif BSP_PACKAGE_PINS == 48

/* valid: 0000 0000 0001 1110 0000 0011 1110 0111; invalid 1111 1111 1110 0001 1111 1100 0001 1000 */
#define ADC_INVALID_CH_MASK     (0xFFE1FC18)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif


#ifdef BSP_MCU_RX230

/* Temp sensor and internal v ref are in bit locations 8 and 9 in each mask for rx230 */
#if BSP_PACKAGE_PINS == 100

/* valid: 1111 1111 1111 1111 0000 0011 1111 1111; invalid 0000 0000 0000 0000 1111 1100 0000 0000 */
#define ADC_INVALID_CH_MASK     (0x0000FC00)

#elif BSP_PACKAGE_PINS == 64

/* valid: 0000 0000 0011 1111 0000 0011 0101 1111; invalid 1111 1111 1100 0000 1111 1100 1010 0000 */
#define ADC_INVALID_CH_MASK     (0xFFC0FCA0)

#elif BSP_PACKAGE_PINS == 48

/* valid: 0000 0000 0001 1110 0000 0011 0100 0111; invalid 1111 1111 1110 0001 1111 1100 1011 1000 */
#define ADC_INVALID_CH_MASK     (0xFFE1FCB8)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif


#ifdef BSP_MCU_RX231

/* Temp sensor and internal v ref are in bit locations 8 and 9 in each mask for rx231 */
#if BSP_PACKAGE_PINS == 100

/* valid: 1111 1111 1111 1111 0000 0011 1111 1111; invalid 0000 0000 0000 0000 1111 1100 0000 0000 */
#define ADC_INVALID_CH_MASK     (0x0000FC00)

#elif BSP_PACKAGE_PINS == 64

/* valid: 0000 0000 0011 1111 0000 0011 0101 1111; invalid 1111 1111 1100 0000 1111 1100 1010 0000 */
#define ADC_INVALID_CH_MASK     (0xFFC0FCA0)

#elif BSP_PACKAGE_PINS == 48

/* valid: 0000 0000 0001 1110 0000 0011 0100 0111; invalid 1111 1111 1110 0001 1111 1100 1011 1000 */
#define ADC_INVALID_CH_MASK     (0xFFE1FCB8)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif

#if (defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M))

#if BSP_PACKAGE_PINS == 177
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 176
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 145
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 144
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 100
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */

/* valid: 0110 0000 0011 1111 1111 1111; invalid 1001 1111 1100 0000 0000 0000 */
#define ADC_INVALID_CH_MASK1    (0xFF9FC000)    /* chans 0-13, sensors valid */

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif

#if (defined(BSP_MCU_RX65_ALL))

#if BSP_PACKAGE_PINS == 177
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 176
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 145
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 144
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFF800000)    /* all channels valid (0-20, sensors) */

#elif BSP_PACKAGE_PINS == 100
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */

/* valid: 0110 0000 0011 1111 1111 1111; invalid 1001 1111 1100 0000 0000 0000 */
#define ADC_INVALID_CH_MASK1    (0xFF9FC000)    /* chans 0-13, sensors valid */

#elif BSP_PACKAGE_PINS == 64
#define ADC_INVALID_CH_MASK0    (0xFFFFFFF0)    /* channels 0-3 valid */
#define ADC_INVALID_CH_MASK1    (0xFF9FC33F)    /* chans 6, 7 10-13, sensors valid */

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif /* BSP_PACKAGE_PINS == 177 */

#endif /* defined(BSP_MCU_RX65_ALL) */

#if (defined(BSP_MCU_RX66T))

#if BSP_PACKAGE_PINS == 144
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK2    (0xFFF0F000)    /* all channels valid (0-11, 16, 17 sensors) */

#elif BSP_PACKAGE_PINS == 112
#define ADC_INVALID_CH_MASK0    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F030)    /* channels 0-3, 6-11, 16, 17 sensors valid */

#elif BSP_PACKAGE_PINS == 100

#if ((BSP_CFG_MCU_PART_FUNCTION == 0xA) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0xC) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0xE) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0x10))
#define ADC_INVALID_CH_MASK0    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F030)    /* channels 0-3, 6-11, 16, 17 sensors valid */
#else
#define ADC_INVALID_CH_MASK0    (0xFFFFFFF0)    /* channels 0-3 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFFF0)    /* channels 0-3 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F000)    /* all channels valid (0-11, 16, 17 sensors) */
#endif

#elif BSP_PACKAGE_PINS == 80
#define ADC_INVALID_CH_MASK0    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F2F0)    /* channels 0-3, 8, 10, 11, 16, 17, sensors valid */

#elif BSP_PACKAGE_PINS == 64
#define ADC_INVALID_CH_MASK0    (0xFFFFFF78)    /* channels 0-2, 7 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF78)    /* channels 0-2, 7 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F3F8)    /* channels 0-2, 10, 11, 16, 17, sensors valid */

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif /* BSP_PACKAGE_PINS == 144 */

#endif /* defined(BSP_MCU_RX66T) */

#if (defined(BSP_MCU_RX72T))

#if BSP_PACKAGE_PINS == 144
#define ADC_INVALID_CH_MASK0    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF00)    /* all channels valid (0-7) */
#define ADC_INVALID_CH_MASK2    (0xFFF0F000)    /* all channels valid (0-11, 16, 17 sensors) */

#elif BSP_PACKAGE_PINS == 100

#if ((BSP_CFG_MCU_PART_FUNCTION == 0xA) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0xC) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0xE) || \
     (BSP_CFG_MCU_PART_FUNCTION == 0x10))
#define ADC_INVALID_CH_MASK0    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFF70)    /* channels 0-3, 7 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F030)    /* channels 0-3, 6-11, 16, 17 sensors valid */
#else
#define ADC_INVALID_CH_MASK0    (0xFFFFFFF0)    /* channels 0-3 valid */
#define ADC_INVALID_CH_MASK1    (0xFFFFFFF0)    /* channels 0-3 valid */
#define ADC_INVALID_CH_MASK2    (0xFFF0F000)    /* all channels valid (0-11, 16, 17 sensors) */
#endif

#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

#endif

/******************************************************************************
Typedef definitions
*******************************************************************************/
typedef R_BSP_VOLATILE_EVENACCESS uint16_t * const  dregs_t;

typedef struct st_adc_ctrl          // ADC Control Block
{
    adc_mode_t      mode;           // operational mode
    bool            opened;
    void          (*callback)(void *p_args);

#if (defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX65_ALL) || defined(BSP_MCU_RX66T) \
  || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX72T))
    uint32_t        cmpi_mask;      // for GRPBL1
#endif    
#if (defined(BSP_MCU_RX65_ALL) || defined(BSP_MCU_RX66T) || defined(BSP_MCU_RX72T))
    uint32_t        cmpi_maskb;     // for GRPBL1 WINDOWB
#endif
} adc_ctrl_t;

/* ADCSR register ADCS field (non-63x) */
typedef enum e_adc_adcs
{
    ADC_ADCS_SINGLE_SCAN =0,
    ADC_ADCS_GROUP_SCAN  =1,
    ADC_ADCS_CONT_SCAN   =2,
    ADC_ADCS_MAX
} adc_adcs_t;

/******************************************************************************
Exported global variables
*******************************************************************************/

/******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
extern adc_err_t adc_open(uint8_t const          unit,
                          adc_mode_t const       mode,
                          adc_cfg_t * const      p_cfg,
                          void         (* const  p_callback)(void *p_args));
extern adc_err_t adc_close(uint8_t const  unit);
extern adc_err_t adc_read_all(adc_data_t * const  p_all_data);
extern adc_err_t adc_control(uint8_t const       unit,
                             adc_cmd_t const     cmd,
                             void * const        p_args);

#endif /* S12AD_PRIVATE_H */
