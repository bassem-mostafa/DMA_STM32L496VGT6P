// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

/**
 *  @file
 *
 *  @brief Platform DMA STM32L496VGT6P Driver
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_DMA_Driver
 *
 *  @{
 */

/**
 *  @defgroup Platform_DMA_STM32L496VGT6P STM32L496VGT6P
 *
 *  @{
 */

#ifndef DMA_STM32L496VGT6P_H_
    #define DMA_STM32L496VGT6P_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief DMA STM32L496VGT6P Operation Status
     *
     *  @enum DMA_STM32L496VGT6P_Status_t
     */
    typedef enum DMA_STM32L496VGT6P_Status
    {
        DMA_STM32L496VGT6P_Status_Success = 0,     ///< Success
        DMA_STM32L496VGT6P_Status_ArgumentInvalid, ///< Argument Invalid
        DMA_STM32L496VGT6P_Status_NotSupported,    ///< Not Supported
        DMA_STM32L496VGT6P_Status_Error,           ///< General Error
        DMA_STM32L496VGT6P_Status_Busy,            ///< Busy
        DMA_STM32L496VGT6P_Status_Timeout,         ///< Timeout
    } DMA_STM32L496VGT6P_Status_t;

    /**
     *  @brief DMA STM32L496VGT6P
     *
     *  @enum DMA_STM32L496VGT6P_t
     */
    typedef enum DMA_STM32L496VGT6P
    {
        DMA_STM32L496VGT6P_1 = 0, ///< DMA 1
        DMA_STM32L496VGT6P_2,     ///< DMA 2
        DMA_STM32L496VGT6P_Count  ///< Count
    } DMA_STM32L496VGT6P_t;

    /**
     *  @brief DMA STM32L496VGT6P Instance (Forward Declaration)
     */
    typedef struct DMA_STM32L496VGT6P_Instance DMA_STM32L496VGT6P_Instance_t;

    /**
     *  @brief DMA STM32L496VGT6P Callback On Interrupt
     */
    typedef DMA_STM32L496VGT6P_Status_t ( *DMA_STM32L496VGT6P_CallbackOnInterrupt_t )( DMA_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief DMA STM32L496VGT6P Instance Context
     *
     *  @struct DMA_STM32L496VGT6P_Instance_Context_t
     */
    typedef struct DMA_STM32L496VGT6P_Instance_Context DMA_STM32L496VGT6P_Instance_Context_t;

    /**
     *  @brief DMA STM32L496VGT6P Instance
     *
     *  @struct DMA_STM32L496VGT6P_Instance_t
     */
    typedef struct DMA_STM32L496VGT6P_Instance
    {
        DMA_STM32L496VGT6P_t DMAx;

        // Managed Internally
        DMA_STM32L496VGT6P_Instance_Context_t * Context;
    } DMA_STM32L496VGT6P_Instance_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    /**
     *  @brief Initializes specified DMA STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return DMA_STM32L496VGT6P_Status_t
     */
    DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Initialize( DMA_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief Cycles specified DMA STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return DMA_STM32L496VGT6P_Status_t
     */
    DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Cycle( DMA_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief De-initializes specified DMA STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return DMA_STM32L496VGT6P_Status_t
     */
    DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_DeInitialize( DMA_STM32L496VGT6P_Instance_t * Instance );

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char DMA_STM32L496VGT6P_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* DMA_STM32L496VGT6P_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
