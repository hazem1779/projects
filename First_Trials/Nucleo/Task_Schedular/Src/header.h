#ifndef HEADER_H_
#define HEADER_H_


void task1_handler (void);
void task2_handler (void);
void task3_handler (void);
void task4_handler (void);
void switch_sp_to_psp(void);
void init_systick_timer(uint32_t tick_hz);
void init_tasks_stack(void);


void enable_processor_faults(void);


__attribute__((naked)) void switch_sp_to_psp(void);
__attribute__((naked)) void init_schedular_stack(uint32_t sched_TopOfStack);


#define SCB_SHCSR  *((uint32_t *)0xE000ED24)
#define USGFAULTENA (1U << 18)
#define BUSFAULTENA (1U << 17)
#define MEMFAULTENA (1U << 16)

#define SRAM_START (0x20000000U)
#define SRAM_SIZE  ((128U) * (1024U))
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))

#define SIZE_TASK_STACK  (1024U)
#define SIZE_SCHED_STACK (1024U)

#define T1_STACK_START    (SRAM_END)
#define T2_STACK_START    ((SRAM_END) - (1U * SIZE_TASK_STACK))
#define T3_STACK_START    ((SRAM_END) - (2U * SIZE_TASK_STACK))
#define T4_STACK_START 	  ((SRAM_END) - (3U * SIZE_TASK_STACK))
#define SCHED_STACK_START ((SRAM_END) - (4U * SIZE_TASK_STACK))

#define SYSTEM_CLK 16000000U
#define TICK_HZ    1000U

#define SYST_CSR  *((uint32_t *)(0xE000E010))
#define SYST_RVR  *((uint32_t *)(0xE000E014))

#define MAX_TASKS  4
#define DUMMY_XPSR (0x01000000)
#define TASK_READY_STATE 0x00
#define TASK_BLOCKED_STATE 0xFF

#endif //__HEADER_H


