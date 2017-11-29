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

    for (i = 0; i <= mp_tcb_size; i++) {
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
    P_TCB p_tcb;
	U32 stack_usage, stack_size;

	// TID does not exist (except for idle TCB)
	if (task_id > os_maxtaskrun && task_id != os_idle_TCB.task_id) {
		return OS_R_NOK;
	}
	
	// Values
    if (task_id != os_idle_TCB.task_id)
        p_tcb = os_active_TCB[task_id - 1];
    else
        p_tcb = &os_idle_TCB;
	stack_usage = 0;
	stack_size = (U16)os_stackinfo;
    
    // Stack usage
	// running / not running
	if (p_tcb->state == RUNNING) {
		// rt_get_PSP: MRS R0,PSP. 
		// MRS: Move the contents of a PSR to a general-purpose register.
		// PSP: Program Status Pointer
		stack_usage = stack_size - ((U32)rt_get_PSP() - (U32)p_tcb->stack);
		// unused = PSP - stack(task stack block pointer)
		// used = stack_size - unused
	} else {
		stack_usage = stack_size - ((U32)p_tcb->tsk_stack - (U32)p_tcb->stack);
		// unused = tsk_stack(current stack pointer) - stack(task stack block pointer)
		// used = stack_size - unused
	}
	stack_usage = (stack_usage * 100) / stack_size; // used percentage
    
    p_task_info->task_id = (U8)task_id;
	p_task_info->state = (U8)p_tcb->state;
    p_task_info->prio = (U8)p_tcb->prio;
    p_task_info->stack_usage = (U8)stack_usage;
    p_task_info->ptask = p_tcb->ptask;
	
    
  if (p_task_info->state != INACTIVE
		&& p_task_info->state != READY
		&& p_task_info->state != RUNNING
		&& p_task_info->state != WAIT_DLY
		&& p_task_info->state != WAIT_SEM
		&& p_task_info->state != WAIT_MUT) {
		return OS_R_NOK;
	}
	return OS_R_OK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
