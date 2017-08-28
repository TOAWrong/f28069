/******************************************************************************
* FILE PURPOSE: This file contains the PN9 table
*******************************************************************************
*
* FILE NAME: phy_pn9Table.c
*
* DESCRIPTION:  PN9 Sequence Lookup Table
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 07/31/2012 JKunduru    Written
*
*
*
*******************************************************************************/
#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_pn9STable, "sunPhyTable");
#pragma DATA_SECTION(PHY_pn9Table, "sunPhyTable");

/* PN9 sequence in signed (1/-1) format */
const SINT16 PHY_pn9STable[PHY_PN9_LUT_SIZE] =
  {
     1,      1,      1,     -1,      1,      1,      1,     -1,   
    -1,      1,      1,     -1,      1,      1,      1,     -1,   
    -1,     -1,      1,     -1,      1,     -1,      1,     -1,   
    -1,      1,     -1,     -1,      1,      1,      1,     -1,   
    -1,     -1,      1,      1,      1,     -1,      1,      1,   
    -1,      1,     -1,      1,     -1,      1,      1,      1,   
    -1,     -1,      1,     -1,     -1,      1,      1,     -1,   
    -1,     -1,     -1,     -1,      1,      1,     -1,     -1,   
    -1,     -1,      1,      1,      1,     -1,      1,     -1,   
    -1,      1,     -1,     -1,     -1,      1,      1,     -1,   
     1,     -1,      1,      1,     -1,      1,      1,      1,   
     1,      1,     -1,      1,      1,     -1,     -1,      1,   
     1,     -1,     -1,     -1,      1,     -1,      1,      1,   
     1,     -1,     -1,     -1,     -1,     -1,      1,     -1,   
    -1,     -1,     -1,      1,      1,      1,      1,      1,   
    -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,   
    -1,      1,      1,      1,      1,     -1,     -1,     -1,   
    -1,      1,     -1,     -1,     -1,      1,      1,      1,   
     1,     -1,      1,     -1,     -1,      1,      1,     -1,   
    -1,      1,     -1,     -1,      1,     -1,     -1,     -1,   
    -1,      1,     -1,      1,      1,      1,      1,     -1,   
    -1,     -1,      1,      1,     -1,     -1,      1,      1,   
     1,      1,     -1,      1,      1,     -1,      1,      1,   
     1,     -1,      1,     -1,      1,     -1,     -1,     -1,   
     1,     -1,      1,     -1,     -1,     -1,     -1,      1,   
     1,     -1,      1,      1,     -1,      1,     -1,     -1,   
    -1,      1,      1,     -1,     -1,     -1,      1,      1,   
     1,      1,      1,      1,     -1,     -1,     -1,      1,   
    -1,     -1,     -1,      1,     -1,      1,      1,     -1,   
    -1,     -1,     -1,      1,     -1,      1,     -1,      1,   
     1,     -1,      1,     -1,      1,      1,      1,      1,   
     1,      1,     -1,      1,     -1,      1,     -1,      1,   
    -1,      1,     -1,     -1,     -1,     -1,     -1,      1,   
    -1,      1,     -1,     -1,      1,     -1,      1,      1,   
     1,      1,      1,     -1,     -1,      1,     -1,     -1,   
    -1,      1,     -1,     -1,      1,     -1,     -1,      1,   
    -1,      1,     -1,     -1,      1,      1,      1,      1,   
     1,     -1,      1,     -1,     -1,     -1,      1,     -1,   
    -1,     -1,     -1,     -1,      1,      1,      1,     -1,   
    -1,     -1,     -1,      1,      1,     -1,     -1,      1,   
    -1,      1,      1,     -1,     -1,      1,     -1,      1,   
    -1,     -1,     -1,      1,      1,      1,     -1,     -1,   
     1,     -1,      1,      1,      1,     -1,      1,     -1,   
    -1,     -1,     -1,     -1,     -1,     -1,      1,     -1,   
     1,      1,     -1,      1,     -1,     -1,      1,      1,   
     1,     -1,      1,     -1,      1,      1,     -1,     -1,   
     1,      1,      1,     -1,     -1,      1,      1,      1,   
     1,      1,      1,      1,     -1,     -1,      1,      1,   
    -1,     -1,      1,      1,     -1,      1,     -1,      1,   
    -1,     -1,      1,      1,     -1,      1,      1,     -1,   
    -1,     -1,     -1,     -1,     -1,      1,     -1,     -1,   
     1,     -1,      1,      1,     -1,      1,      1,     -1,   
     1,      1,     -1,     -1,      1,     -1,     -1,     -1,   
    -1,     -1,     -1,      1,      1,     -1,      1,     -1,   
    -1,      1,     -1,      1,     -1,      1,      1,      1,   
     1,     -1,      1,     -1,      1,      1,      1,     -1,   
     1,      1,     -1,     -1,     -1,      1,     -1,     -1,   
     1,      1,     -1,      1,     -1,     -1,     -1,     -1,   
     1,     -1,     -1,      1,      1,      1,      1,     -1,   
    -1,      1,     -1,      1,     -1,      1,     -1,      1,   
     1,     -1,     -1,     -1,      1,      1,     -1,      1,   
     1,      1,      1,     -1,     -1,      1,      1,      1,   
    -1,      1,      1,      1,      1,     -1,      1,      1,   
     1,      1,      1,      1,      1,      1,     -1,		 1
};

/* PN9 sequence in unsigned (1/0) format */
const SINT16 PHY_pn9Table[PHY_PN9_LUT_SIZE] =
{
#include "phy_pn9Table.txt"
};