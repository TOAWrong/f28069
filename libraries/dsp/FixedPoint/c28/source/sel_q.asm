;;#############################################################################
;;! \file source/sel_q.asm
;;!
;;! \brief  Selects the Q format for the twiddle factors
;;!
;;! \date   Feb 25, 2002
;;! 
;;
;;  Group:            C2000
;;  Target Family:    C28x
;;
;;#############################################################################
;;$TI Release: C28x Fixed Point DSP Library v1.20.00.00 $
;;$Release Date: Mon May 22 15:47:12 CDT 2017 $
;;$Copyright: Copyright (C) 2014-2017 Texas Instruments Incorporated -
;;            http://www.ti.com/ ALL RIGHTS RESERVED $
;;#############################################################################
;;
;;*****************************************************************************
;; defines
;;*****************************************************************************
Q30             .set    30
Q31             .set    31

; Select Twiddle factor Q format
TF_QFMAT        .set    Q30    
        
;;#############################################################################
;;  End of File
;;#############################################################################
