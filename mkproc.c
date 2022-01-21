#include "types.h"
#include "stat.h"
#include "user.h"
#include "random.h"
#include "param.h"

int main(int argc, char *argv[])
{
    int pid;
    int k, n;
    int x, z;

    if (argc < 2)
        n = 1; //Default
    else
        n = atoi(argv[1]);
    if (n < 0 || n > NPROC-2){
        printf(1, "maximum process limit 62");
        n = 2;
    }
    x = 0;
    pid = 0;

    for (k = 0; k < n; k++)
    {
        int tickets = random_at_most(MAX_TICKET_VALUE);
        pid = fork();
        if (pid < 0)
        {
            printf(1, "process limit exceeded");
        }
        // else if (pid > 0)
        // {
        //     // parent
        //     printf(1, "Parent %d creating child %d\n", getpid(), pid);
        //     //   wait();
        // }
        else if (pid == 0)
        {
            // printf(1, "Child %d created\n", getpid());
            settickets(tickets);
            for (z = 0; z < 4000000000; z += 1)
                // printf(1, "%d\n", random_at_most(100));
                x = x + 3.14 * 89.64; //Useless calculation to consume CPU Time
            break;
        }
    }
    // printf(1, "ok\n");
    exit();
}