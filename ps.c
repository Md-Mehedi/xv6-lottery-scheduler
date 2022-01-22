#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

// Print the status of processes
void print(struct pstat *stat)
{
    printf(1, "pid\tinuse\ttickets\tticks\n");
    for (int i = 0; i < NPROC; i++)
    {
        if (stat->pid[i] == 0)
            continue;
        printf(1, "%d\t%d\t%d\t%d\n", stat->pid[i], stat->inuse[i], stat->tickets[i], stat->ticks[i]);
    }
}

// Swap two process data between i and j position
void swap(struct pstat *stat, int i, int j)
{
    int pid = stat->pid[i];
    int inuse = stat->inuse[i];
    int tickets = stat->tickets[i];
    int ticks = stat->ticks[i];

    stat->pid[i] = stat->pid[j];
    stat->inuse[i] = stat->inuse[j];
    stat->tickets[i] = stat->tickets[j];
    stat->ticks[i] = stat->ticks[j];

    stat->pid[j] = pid;
    stat->inuse[j] = inuse;
    stat->tickets[j] = tickets;
    stat->ticks[j] = ticks;
}

// Sort the process status according to tickets count descending
// This function uses 'Selection Sort'
void sort(struct pstat *stat)
{
    int max_pos = 0;
    for (int i = 0; i < NPROC; i++)
    {
        max_pos = i;
        for (int j = i + 1; j < NPROC; j++)
        {
            if (stat->tickets[max_pos] < stat->tickets[j] || (stat->tickets[max_pos] == stat->tickets[j] && stat->ticks[max_pos] < stat->ticks[j]))
            {
                max_pos = j;
            }
        }
        if (max_pos != i)
        {
            swap(stat, i, max_pos);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf(1, "No argument needed for ps\n");
        exit();
    }
    struct pstat stat;

    // Getting process infos by system call
    getpinfo(&stat);

    // Sorting the results
    sort(&stat);

    // Printing the infos
    print(&stat);

    exit();
}