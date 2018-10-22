#ifndef vlado_pid_manager
#define vlado_pid_manager

#define MIN_PID 300
#define MAX_PID 600

#define PID_ALLOCATION_SUCESS 1
#define PID_ALLOCATION_FAIL -1

//#define PROBLEM_EXISTS_MAP_ALLOCATION

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

void print_map_allocation(void);


#endif


