/*----------------------------------------------------------------------------
 *      ECE254 Lab Task Management
 *----------------------------------------------------------------------------
 *      Name:    RT_TASK_ext.C
 *      Purpose: Interface functions for extended task management  
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/

#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/
P_TCB p_tcb;

/*----------------------------------------------------------------------------
 *      Local Functions
 *---------------------------------------------------------------------------*/

int os_tsk_count_get (void);

/*--------------------------- rt_tsk_count_get ------------------------------*/
/* added in ECE254 lab keil_rtx */
int rt_tsk_count_get (void) {
	int k = 0;
	int i;

	for (i = 0; i <=10; i++) {
	if (os_active_TCB[i-1] != NULL) {
		k++;
	}
	}
	if (os_idle_TCB.task_id != 255) {
		k++;
	}
	
	return k;
}

/*--------------------------- rt_tsk_get ------------------------------------*/
/* added in ECE254 lab keil_proc */
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
  p_tcb =&os_idle_TCB;
  p_tcb=os_active_TCB[task_id-1];
	/* Add your own code here. Change the following lines accordingly */
	p_task_info->task_id     = p_tcb->task_id;
	p_task_info->state       = INACTIVE;
	p_task_info->prio        = 99;
	p_task_info->stack_usage = 15;
	p_task_info->ptask       = NULL;
	return OS_R_OK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
