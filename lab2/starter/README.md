- All test tasks are located in main_task_exp
- To run tasks, run the Starter SIM build
- Output from logged actions of each task is outputted to UART1 port
- Task Spec
	- task init creates a scenario where the memory pool of size n has memory allocated memory blocks n-1 in the pool
	  and then runs task2, task3, task4, and task 5 in sequential order
	- tasks task2, task3, and 4 all call the os_mem_alloc function, but task2 is assigned a lower priority than task3 
	  and task4, and task3 and task4 are assigned the same priority
	- task task 5 calls the os_mem_free function and has a lower priority than task2
	- task1 is unused by the function