/**
 * @brief: ECE254 Keil ARM RL-RTX Task Management Lab starter file that calls os_tsk_get()
 * @file: main_task_exp.c
 * @date: 2015/09/13
 */
/* NOTE: This release is for students to use */

#include <LPC17xx.h>
#include "uart_polling.h" 
#include <RTL.h>
#include "../../RTX_CM3/INC/RTL_ext.h" /* extended interface header file */
#include <stdio.h>
#include <string.h>

#define NUM_FNAMES 7

struct func_info {
  void (*p)();      /* function pointer */
  char name[16];    /* name of the function */
};

extern void os_idle_demon(void);
__task void task1(void);
__task void task2(void);
__task void task3(void);
__task void task4(void);
__task void task5(void);
__task void init (void);
 
char *state2str(unsigned char state, char *str);
char *fp2name(void (*p)(), char *str);

OS_MUT g_mut_uart;
OS_TID g_tid = 255;

void *testptr;
int task_resume_flag = 0;

_declare_box(testpool, 12, 30);

int  g_counter = 0;  // a global counter
char g_str[16];
char g_tsk_name[16];

struct func_info g_task_map[NUM_FNAMES] = \
{
  /* os_idle_demon function ptr to be initialized in main */
  {NULL,  "os_idle_demon"}, \
  {task1, "task1"},   \
  {task2, "task2"},   \
  {task3, "task3"},   \
  {task4, "task4"},   \
  {task5, "task5"},   \
  {init,  "init" }
};

/* no local variables defined, use one global var */
__task void task1(void)
{
	int count;
	count = os_tsk_count_get();
	printf("***Number of tasks: %d \n", count);
	
	for (;;) {
		g_counter++;
	}
}

__task void task2(void)
{
	while (1) {
        printf ("running task2...\n");
        task_resume_flag = 0;
        testptr = os_mem_alloc(testpool);
        os_mut_wait(g_mut_uart, 0xFFFF);
        if (!task_resume_flag) 
            printf("task2 allocated block %d of 30 in pool \n", ((U32)testptr - (U32)testpool) / 12);
        else 
            printf ("resuming task2...\n");
        os_mut_release(g_mut_uart);
	}
}

__task void task3(void) {
	while (1) {
        printf ("running task3...\n");
        task_resume_flag = 0;
        testptr = os_mem_alloc(testpool);
        os_mut_wait(g_mut_uart, 0xFFFF);
        if (!task_resume_flag) 
            printf("task3 allocated block %d of 30 in pool \n", ((U32)testptr - (U32)testpool) / 12);
        else 
            printf ("resuming task3...\n");
        os_mut_release(g_mut_uart);
    }
}

__task void task4(void) {
	while (1) {
        printf ("running task4...\n");
        task_resume_flag = 0;
        testptr = os_mem_alloc(testpool);
        os_mut_wait(g_mut_uart, 0xFFFF);
        if (!task_resume_flag) 
            printf("task4 allocated block %d of 30 in pool \n", ((U32)testptr - (U32)testpool) / 12);
        else 
            printf ("resuming task4...\n");
        os_mut_release(g_mut_uart);
    }
}

__task void task5(void) {
    int val;
	while (1) {
        val = os_mem_free(testpool, testptr);
        if (val == OS_R_OK) {
            os_mut_wait(g_mut_uart, 0xFFFF);
            printf ("task5 successfully freed memory \n");
            os_mut_release(g_mut_uart);
            task_resume_flag = 1;
        }
        else {
            os_mut_wait(g_mut_uart, 0xFFFF);
            printf ("task5 failed to free memory \n");
            os_mut_release(g_mut_uart);
        }
	}
}

/*--------------------------- init ------------------------------------*/
/* initialize system resources and create other tasks                  */
/*---------------------------------------------------------------------*/
__task void init(void)
{
	os_mut_init(&g_mut_uart);
 
	_init_box(testpool, sizeof(testpool), 12);
    
    //makes memory pool full
    testptr = os_mem_alloc(testpool);
    printf("Filling memory pool \n");
    
	while (((U32)testptr - (U32)testpool) / 12 < 29) {
        testptr = os_mem_alloc(testpool);
	}
    
    printf("Remaining blocks in pool %d \n", 30 - (((U32)testptr - (U32)testpool) / 12));
    
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: TID = %d\n", os_tsk_self());
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task1, 1);  /* task 1 at priority 1 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task1 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
  
	g_tid = os_tsk_create(task2, 3);  /* task 2 at priority 1 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task2 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task3, 4);  /* task 3 at priority 5 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task3 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task4, 4);  /* task 4 at priority 2 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task4 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task5, 2);  /* task 5 at priority 3 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task5 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);

	os_tsk_delete_self();     /* task MUST delete itself before exiting */
}

/**
 * @brief: convert state numerical value to string represenation      
 * @param: state numerical value (macro) of the task state
 * @param: str   buffer to save the string representation, 
 *               buffer to be allocated by the caller
 * @return:the string starting address
 */
char *state2str(unsigned char state, char *str)
{
	switch (state) {
	case INACTIVE:
		strcpy(str, "INACTIVE");
		break;
	case READY:
		strcpy(str, "READY   ");
		break;
	case RUNNING:
		strcpy(str, "RUNNING ");
		break;
	case WAIT_DLY:
		strcpy(str, "WAIT_DLY");
		break;
	case WAIT_ITV:
		strcpy(str, "WAIT_ITV");
		break;
	case WAIT_OR:
		strcpy(str, "WAIT_OR");
		break;
	case WAIT_AND:
		strcpy(str, "WAIT_AND");
		break;
	case WAIT_SEM:
		strcpy(str, "WAIT_SEM");
		break;
	case WAIT_MBX:
		strcpy(str, "WAIT_MBX");
		break;
	case WAIT_MUT:
		strcpy(str, "WAIT_MUT");
		break;
	case WAIT_MEM:
		strcpy(str, "WAIT_MEM");
		break;
	default:
		strcpy(str, "UNKNOWN");    
	}
	return str;
}

/** 
 * @brief: get function name by function pointer
 * @param: p the entry point of a function (i.e. function pointer)
 * @param: str the buffer to return the function name
 * @return: the function name string starting address
 */
char *fp2name(void (*p)(), char *str)
{
	int i;
	unsigned char is_found = 0;
  
	for ( i = 0; i < NUM_FNAMES; i++) {
		if (g_task_map[i].p == p) {
			str = strcpy(str, g_task_map[i].name);  
			is_found = 1;
			break;
		}
	}
	if (is_found == 0) {
		strcpy(str, "ghost");
	}
	return str;
}

int main(void)
{
	SystemInit();         /* initialize the LPC17xx MCU */
	uart0_init();         /* initilize the first UART */
   
	/* fill the fname map with os_idle_demon entry point */
	g_task_map[0].p = os_idle_demon;
  
	printf("Calling os_sys_init()...\n");
	
	os_sys_init(init);    /* initilize the OS and start the first task */
}
