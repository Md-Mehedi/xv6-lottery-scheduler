#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  // uint xticks;

  // acquire(&tickslock);
  // xticks = ticks;
  // release(&tickslock);
  return uptime();
}



/**************** Code for Loterry Schedule *****************/
int sys_settickets(void){
  int number;
  argint(0, &number);
  if(argint(0, &number) < 0)
    return -1;
  if(number < 1)
    return -1;
  
  struct proc* p = myproc();
  p->tickets = number;
  cprintf("%d tickets set for pid %d\n", number, p->pid);
  return 0;
}

int sys_getpinfo(void){
  struct pstat * stat = 0;
  if(argptr(0, (void*)&stat, sizeof(*stat)) < 0)
    return -1;
  if(stat == 0)
    return -1;

  getpinfo(stat);
  return 0;
  
  // cprintf("passing arg : %d %d %d %d\n", stat->inuse[1], stat->pid[0], stat->tickets[0], stat->ticks[0]);
  return 0;
}