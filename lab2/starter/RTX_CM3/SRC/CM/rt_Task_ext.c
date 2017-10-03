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
  p_tcb = &os_idle_TCB;
  p_tcb = os_active_TCB[task_id-1];
	/* Add your own code here. Change the following lines accordingly */
	
  p_task_info->task_id     = p_tcb->task_id;
	p_task_info->state       = p_tcb->state;
	p_task_info->prio        = p_tcb->prio;
  
  /* code snippet below copied from https://learn.uwaterloo.ca/d2l/le/content/336412/viewContent/1882575/View */
  /* start of code snippet */
  if (p_tcb->state != 2) {
    U32 sizeInAddr = (U16)os_stackinfo;
    p_task_info->stack_usage = (U8)(((U32)(p_tcb->stack) + sizeInAddr - (U32)(p_tcb->tsk_stack))*100/sizeInAddr);
  }
  else {
    U32 sizeInAddr = (U16)os_stackinfo;
    p_task_info->stack_usage = (U8)(((U32)(p_tcb->stack) + sizeInAddr - (U32)(rt_get_PSP()))*100/sizeInAddr);  
  }
  
  /* end of code snippet*/
	
  p_task_info->ptask       = p_tcb->ptask;
  
  if (p_tcb->state <= 10)
    return OS_R_OK;
  else
    return OS_R_NOK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
