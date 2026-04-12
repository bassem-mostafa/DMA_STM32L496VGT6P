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

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef STM32L496xx

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../DMA_Internal.h"
    #include "DMA_STM32L496VGT6P.h"

    #include "stm32l4xx.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum DMA_STM32L496VGT6P_Event
{
    DMA_STM32L496VGT6P_Event_None = 0,
    DMA_STM32L496VGT6P_Event_InterruptChannel_1 = UTIL_BIT( 0 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_2 = UTIL_BIT( 1 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_3 = UTIL_BIT( 2 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_4 = UTIL_BIT( 3 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_5 = UTIL_BIT( 4 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_6 = UTIL_BIT( 5 ),
    DMA_STM32L496VGT6P_Event_InterruptChannel_7 = UTIL_BIT( 6 ),
} DMA_STM32L496VGT6P_Event_t;

typedef struct DMA_STM32L496VGT6P_InstanceContext
{
    DMA_TypeDef * DMAx;       // TODO Make use of DMAx:DMA_TypeDef
    DMA_InitTypeDef InitType; // TODO Make use if InitType:DMA_InitTypeDef
    DMA_STM32L496VGT6P_Event_t Event;
} DMA_STM32L496VGT6P_InstanceContext_t;

typedef struct DMA_STM32L496VGT6P_Context
{
    TIM_Timestamp_t Timestamp;
    DMA_STM32L496VGT6P_InstanceContext_t Context[ DMA_STM32L496VGT6P_Count ];
} DMA_STM32L496VGT6P_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

void DMA1_Channel1_IRQHandler( void );
void DMA1_Channel2_IRQHandler( void );
void DMA1_Channel3_IRQHandler( void );
void DMA1_Channel4_IRQHandler( void );
void DMA1_Channel5_IRQHandler( void );
void DMA1_Channel6_IRQHandler( void );
void DMA1_Channel7_IRQHandler( void );

void DMA2_Channel1_IRQHandler( void );
void DMA2_Channel2_IRQHandler( void );
void DMA2_Channel3_IRQHandler( void );
void DMA2_Channel4_IRQHandler( void );
void DMA2_Channel5_IRQHandler( void );
void DMA2_Channel6_IRQHandler( void );
void DMA2_Channel7_IRQHandler( void );

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_Initialize( void );
static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_Cycle( void );
static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_DeInitialize( void );

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_Initialize( DMA_STM32L496VGT6P_Instance_t * Instance );
static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_Cycle( DMA_STM32L496VGT6P_Instance_t * Instance );
static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_DeInitialize( DMA_STM32L496VGT6P_Instance_t * Instance );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static DMA_STM32L496VGT6P_Context_t DMA_STM32L496VGT6P_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

void DMA1_Channel1_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_1;
}

void DMA1_Channel2_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_2;
}

void DMA1_Channel3_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_3;
}

void DMA1_Channel4_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_4;

    extern DMA_HandleTypeDef hdma_spi2_rx;
    HAL_DMA_IRQHandler( &hdma_spi2_rx );
}

void DMA1_Channel5_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_5;

    extern DMA_HandleTypeDef hdma_spi2_tx;
    HAL_DMA_IRQHandler( &hdma_spi2_tx );
}

void DMA1_Channel6_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_6;

    extern DMA_HandleTypeDef hdma_usart2_rx;
    HAL_DMA_IRQHandler( &hdma_usart2_rx );
}

void DMA1_Channel7_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_1 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_7;

    extern DMA_HandleTypeDef hdma_usart2_tx;
    HAL_DMA_IRQHandler( &hdma_usart2_tx );
}

void DMA2_Channel1_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_1;

    extern DMA_HandleTypeDef hdma_spi3_rx;
    HAL_DMA_IRQHandler( &hdma_spi3_rx );
}

void DMA2_Channel2_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_2;

    extern DMA_HandleTypeDef hdma_spi3_tx;
    HAL_DMA_IRQHandler( &hdma_spi3_tx );
}

void DMA2_Channel3_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_3;
}

void DMA2_Channel4_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_4;

    extern DMA_HandleTypeDef hdma_spi1_tx;
    HAL_DMA_IRQHandler( &hdma_spi1_tx );
}

void DMA2_Channel5_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_5;
}

void DMA2_Channel6_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_6;

    extern DMA_HandleTypeDef hdma_usart1_tx;
    HAL_DMA_IRQHandler( &hdma_usart1_tx );
}

void DMA2_Channel7_IRQHandler( void )
{
    DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ DMA_STM32L496VGT6P_2 ];

    Context->Event |= DMA_STM32L496VGT6P_Event_InterruptChannel_7;

    extern DMA_HandleTypeDef hdma_usart1_rx;
    HAL_DMA_IRQHandler( &hdma_usart1_rx );
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_Initialize( void )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( void )", __FUNCTION__ );

        // FIXME Remove the usage of `MX_DMA_Init()`
    #if 1
        extern void MX_DMA_Init( void );
        MX_DMA_Init( );
    #endif
    }
    while ( 0 );

    return Status;
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_Cycle( void )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( void )", __FUNCTION__ );
    }
    while ( 0 );

    return Status;
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Context_DeInitialize( void )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( void )", __FUNCTION__ );
    }
    while ( 0 );

    return Status;
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_Initialize( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance == NULL )
        {
            Status = DMA_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ Instance->DMAx ];

        Instance->Context = Context;
    }
    while ( 0 );

    return Status;
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_Cycle( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        DMA_STM32L496VGT6P_InstanceContext_t * Context = &DMA_STM32L496VGT6P_Context.Context[ Instance->DMAx ];

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_1 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_1 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_1;
            DMA_Trace( "Interrupt CH1: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_2 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_2 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_2;
            DMA_Trace( "Interrupt CH2: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_3 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_3 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_3;
            DMA_Trace( "Interrupt CH3: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_4 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_4 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_4;
            DMA_Trace( "Interrupt CH4: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_5 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_5 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_5;
            DMA_Trace( "Interrupt CH5: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_6 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_6 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_6;
            DMA_Trace( "Interrupt CH6: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }

        if ( ( Context->Event & DMA_STM32L496VGT6P_Event_InterruptChannel_7 ) == DMA_STM32L496VGT6P_Event_InterruptChannel_7 )
        {
            Context->Event &= ~DMA_STM32L496VGT6P_Event_InterruptChannel_7;
            DMA_Trace( "Interrupt CH7: Instance=%p, DMA=%d", Instance, Instance->DMAx );

            // TODO Invoke Callback
        }
    }
    while ( 0 );

    return Status;
}

static DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Instance_DeInitialize( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Initialize( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Success;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = DMA_STM32L496VGT6P_Context_Initialize( ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = DMA_STM32L496VGT6P_Instance_Initialize( Instance ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_Cycle( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Error;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = DMA_STM32L496VGT6P_Context_Cycle( ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = DMA_STM32L496VGT6P_Instance_Cycle( Instance ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

DMA_STM32L496VGT6P_Status_t DMA_STM32L496VGT6P_DeInitialize( DMA_STM32L496VGT6P_Instance_t * Instance )
{
    DMA_STM32L496VGT6P_Status_t Status = DMA_STM32L496VGT6P_Status_Error;

    do
    {
        DMA_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = DMA_STM32L496VGT6P_Instance_DeInitialize( Instance ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        if ( ( Status = DMA_STM32L496VGT6P_Context_DeInitialize( ) ) != DMA_STM32L496VGT6P_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char DMA_STM32L496VGT6P_VERSION[] = "0.0.0.v20260412-1852";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* STM32L496xx */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
