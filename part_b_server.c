/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "part_b.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

char **
blackbox_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static char * result;

    pid_t childpid;
    int p2c[2], c2p[2], error[2];
    char w_buf[1000], r_buf[10000], e_buf[10000];
    char buffer[10000];
    pipe(p2c);
    pipe(c2p);
    pipe(error);
    
    childpid = fork();
    if (childpid == -1)  {
        perror("Failed to fork");
    }
    if (childpid == 0) {                            /* child code */ 
        dup2(p2c[0], STDIN_FILENO);
        dup2(c2p[1], STDOUT_FILENO);
        dup2(error[1], STDERR_FILENO);
        close(c2p[0]);
        close(c2p[1]);
        close(p2c[0]);
        close(p2c[1]);
        close(error[0]);
        close(error[1]);
        execl(argp->pathOfBlackbox, argp->pathOfBlackbox, NULL);
    }
    if (childpid != 0) {                  /* parent code */
        close(c2p[1]);    // Parent will not write to c2p
        close(error[1]);
        sprintf(w_buf, "%d\n%d", argp->a, argp->b);
        write(p2c[1], w_buf, strlen(w_buf));
        close(p2c[1]);
        int out = read(c2p[0], r_buf, sizeof(r_buf));
        int err = read(error[0], e_buf, sizeof(e_buf));
        
        if(err > 0){
        	e_buf[err] = 0;
        	sprintf(buffer,"%s\n%s", "FAIL:", e_buf);
        } else {
        	r_buf[out] = 0;
        	sprintf(buffer, "%s\n%s", "SUCCESS:", r_buf);
        }
        
        close(c2p[0]);
        close(error[0]);
    }

    result = buffer;
    return &result;
}