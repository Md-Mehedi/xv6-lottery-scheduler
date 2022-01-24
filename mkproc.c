#include "types.h"
#include "stat.h"
#include "user.h"
#include "random.h"
#include "param.h"

int main(int argc, char *argv[])
{
    int process_id;
    int i, process_count;
    int x, z;

    if (argc < 2)
    {
        // If not argument passed only
        // 1 process will be created
        process_count = 1;
    }
    else
    {
        process_count = atoi(argv[1]);
    }
    if (process_count > NPROC - 2)
    {
        printf(1, "Error!! No process can be created\nAt a time maximum 62 process can be created\n");
        exit();
    }
    if (process_count <= 0)
    {
        printf(1, "Argument is not correct. Type mkproc <1..62>\n");
        exit();
    }

    x = 0;
    process_id = 0;

    // Calling process only creates process by fork()
    // Every child process stucks in the loop which
    // consume the CPU time. After executing loop
    // break the outer loop.
    for (i = 0; i < process_count; i++)
    {
        int tickets = random_at_most(MAX_TICKET_VALUE);
        process_id = fork();
        if (process_id < 0)
        {
            printf(1, "Maximum process limit exceeded");
        }
        else if (process_id == 0)
        {
            settickets(tickets);
            //Useless loop for calculation to consume CPU Time
            for (z = 0; z < 4000000000; z += 1)
                x = x + 13.19 * 66.66; // Useless calculation
            printf(1, "Process %d has done it's work\n", process_id);
            break;
        }
        else{
            printf(1, "process %d created with tickets %d\n", process_id, tickets);
        }
    }
    exit();
}