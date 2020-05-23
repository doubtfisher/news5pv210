/**
 * @file    IxQMgrInit.c
 *
 * @author Intel Corporation
 * @date    30-Oct-2001
 *
 * @brief:  Provided initialization of the QMgr component and its subcomponents.
 *
 * 
 * @par
 * IXP400 SW Release version 2.0
 * 
 * -- Copyright Notice --
 * 
 * @par
 * Copyright 2001-2005, Intel Corporation.
 * All rights reserved.
 * 
 * @par
 * SPDX-License-Identifier:	BSD-3-Clause
 * @par
 * -- End of Copyright Notice --
*/

/*
 * System defined include files.
 */

/*
 * User defined include files.
 */
#include "IxOsal.h"
#include "IxQMgr.h"
#include "IxQMgrQCfg_p.h"
#include "IxQMgrDispatcher_p.h"
#include "IxQMgrLog_p.h"
#include "IxQMgrQAccess_p.h"
#include "IxQMgrDefines_p.h"
#include "IxQMgrAqmIf_p.h"

/*
 * Set to true if initialized
 * N.B. global so integration/unit tests can reinitialize
 */
BOOL qMgrIsInitialized = false;

/*
 * Function definitions.
 */
IX_STATUS
ixQMgrInit (void)
{
    if (qMgrIsInitialized)
    {
	IX_QMGR_LOG0("ixQMgrInit: IxQMgr already initialised\n");
	return IX_FAIL;
    }

    /* Initialise the QCfg component */
    ixQMgrQCfgInit ();

    /* Initialise the Dispatcher component */
    ixQMgrDispatcherInit ();

    /* Initialise the Access component */
    ixQMgrQAccessInit ();

    /* Initialization complete */
    qMgrIsInitialized = true;

    return IX_SUCCESS;
}

IX_STATUS
ixQMgrUnload (void)
{
    if (!qMgrIsInitialized)
    {
	return IX_FAIL;
    }

    /* Uninitialise the QCfg component */
    ixQMgrQCfgUninit ();

    /* Uninitialization complete */
    qMgrIsInitialized = false;

    return IX_SUCCESS;
}

void
ixQMgrShow (void)
{
    IxQMgrQCfgStats *qCfgStats = NULL;
    IxQMgrDispatcherStats *dispatcherStats = NULL;
    int i;
    UINT32 lowIntRegRead, upIntRegRead;

    qCfgStats = ixQMgrQCfgStatsGet ();
    dispatcherStats = ixQMgrDispatcherStatsGet ();
    ixQMgrAqmIfQInterruptRegRead (IX_QMGR_QUELOW_GROUP, &lowIntRegRead);
    ixQMgrAqmIfQInterruptRegRead (IX_QMGR_QUEUPP_GROUP, &upIntRegRead);
    printf("Generic Stats........\n");
    printf("=====================\n");
    printf("Loop Run Count..........%u\n",dispatcherStats->loopRunCnt);
    printf("Watermark set count.....%d\n", qCfgStats->wmSetCnt);
    printf("===========================================\n");
    printf("On the fly Interrupt Register Stats........\n");
    printf("===========================================\n");
    printf("Lower Interrupt Register............0x%08x\n",lowIntRegRead);
    printf("Upper Interrupt Register............0x%08x\n",upIntRegRead);
    printf("==============================================\n");
    printf("Queue Specific Stats........\n");
    printf("============================\n");

    for (i=0; i<IX_QMGR_MAX_NUM_QUEUES; i++)
    {
	if (ixQMgrQIsConfigured(i))
	{
	    ixQMgrQShow(i);
	}
    }

    printf("============================\n");
}

IX_STATUS
ixQMgrQShow (IxQMgrQId qId)
{
    IxQMgrQCfgStats *qCfgStats = NULL;
    IxQMgrDispatcherStats *dispatcherStats = NULL; 

    if (!ixQMgrQIsConfigured(qId))
    {
	return IX_QMGR_Q_NOT_CONFIGURED;
    }
    
    dispatcherStats = ixQMgrDispatcherStatsGet ();
    qCfgStats = ixQMgrQCfgQStatsGet (qId);

    printf("QId %d\n", qId);
    printf("======\n");
    printf("  IxQMgrQCfg Stats\n");
    printf("    Name..................... \"%s\"\n", qCfgStats->qStats[qId].qName);
    printf("    Size in words............ %u\n", qCfgStats->qStats[qId].qSizeInWords);
    printf("    Entry size in words...... %u\n", qCfgStats->qStats[qId].qEntrySizeInWords);
    printf("    Nearly empty watermark... %u\n", qCfgStats->qStats[qId].ne);
    printf("    Nearly full watermark.... %u\n", qCfgStats->qStats[qId].nf);
    printf("    Number of full entries... %u\n", qCfgStats->qStats[qId].numEntries);
    printf("    Sram base address........ 0x%X\n", qCfgStats->qStats[qId].baseAddress);
    printf("    Read pointer............. 0x%X\n", qCfgStats->qStats[qId].readPtr);
    printf("    Write pointer............ 0x%X\n", qCfgStats->qStats[qId].writePtr);

#ifndef NDEBUG
    if (dispatcherStats->queueStats[qId].notificationEnabled)
    {
        char *localEvent = "none ????";
        switch (dispatcherStats->queueStats[qId].srcSel)
        {
            case IX_QMGR_Q_SOURCE_ID_E:
                localEvent = "Empty";
                break;
            case IX_QMGR_Q_SOURCE_ID_NE:
                localEvent = "Nearly Empty";
                break;
            case IX_QMGR_Q_SOURCE_ID_NF:
                localEvent = "Nearly Full";
                break;
            case IX_QMGR_Q_SOURCE_ID_F:
                localEvent = "Full";
                break;
            case IX_QMGR_Q_SOURCE_ID_NOT_E:
                localEvent = "Not Empty";
                break;
            case IX_QMGR_Q_SOURCE_ID_NOT_NE:
                localEvent = "Not Nearly Empty";
                break;
            case IX_QMGR_Q_SOURCE_ID_NOT_NF:
                localEvent = "Not Nearly Full";
                break;
            case IX_QMGR_Q_SOURCE_ID_NOT_F:
                localEvent = "Not Full";
                break;
            default :
                break;
        }
        printf("    Notifications localEvent...... %s\n", localEvent);
    }
    else
    {
        printf("    Notifications............ not enabled\n");
    }
    printf("  IxQMgrDispatcher Stats\n");
    printf("    Callback count................%d\n",
	  dispatcherStats->queueStats[qId].callbackCnt);
    printf("    Priority change count.........%d\n",
	  dispatcherStats->queueStats[qId].priorityChangeCnt);
    printf("    Interrupt no callback count...%d\n",
	  dispatcherStats->queueStats[qId].intNoCallbackCnt);
    printf("    Interrupt lost callback count...%d\n",
	  dispatcherStats->queueStats[qId].intLostCallbackCnt);
#endif

    return IX_SUCCESS;
}




