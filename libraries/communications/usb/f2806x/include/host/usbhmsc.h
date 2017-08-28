//#############################################################################
// FILE: usbhmsc.h
// TITLE: Definitions for the USB MSC host driver
//#############################################################################
// $TI Release: F2806x Support Library v2.02.00.00 $
// $Release Date: Mon May 22 15:42:15 CDT 2017 $
// $Copyright:
// Copyright (C) 2009-2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

#ifndef __USBHMSC_H__
#define __USBHMSC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup usblib_host_class
//! @{
//
//*****************************************************************************

typedef struct tUSBHMSCInstance tUSBHMSCInstance;

//*****************************************************************************
//
// These defines are the the events that will be passed in the \e ui32Event
// parameter of the callback from the driver.
//
//*****************************************************************************
#define MSC_EVENT_OPEN          1
#define MSC_EVENT_CLOSE         2

//*****************************************************************************
//
// The prototype for the USB MSC host driver callback function.
//
//*****************************************************************************
typedef void (*tUSBHMSCCallback)(tUSBHMSCInstance *psMSCInstance,
                                 uint32_t ui32Event,
                                 void *pvEventData);

//*****************************************************************************
//
// Prototypes for the USB MSC host driver APIs.
//
//*****************************************************************************
extern tUSBHMSCInstance * USBHMSCDriveOpen(uint32_t ui32Drive,
                                           tUSBHMSCCallback pfnCallback);
extern void USBHMSCDriveClose(tUSBHMSCInstance *psMSCInstance);
extern int32_t USBHMSCDriveReady(tUSBHMSCInstance *psMSCInstance);
extern int32_t USBHMSCBlockRead(tUSBHMSCInstance *psMSCInstance,
                                uint32_t ui32LBA, uint8_t *pui8Data,
                                uint32_t ui32NumBlocks);
extern int32_t USBHMSCBlockWrite(tUSBHMSCInstance *psMSCInstance,
                                 uint32_t ui32LBA, uint8_t *pui8Data,
                                 uint32_t ui32NumBlocks);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBHMSC_H__
