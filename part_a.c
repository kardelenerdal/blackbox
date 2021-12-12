#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

#define READ_END  0 // fd[0]
#define WRITE_END 1 // fd[1]

int main(int argc, char** argv) {

  pid_t childpid;
  int first_pipe[2]; // Stores two ends of first pipe, parentToChildPipe
  int second_pipe[2]; // Stores two ends of second pipe, childToParentPipe
  int third_pipe[2]; // child sends error, parent recieves error
  char w_buf[100], r_buf[10000], e_buf[10000];
  int output = open(argv[2], O_APPEND|O_WRONLY|O_CREAT, 0744);
  
  if(output<0){
    printf("%s\n", "cannot open file");
  }
   
  if (pipe(first_pipe) == -1) {
    fprintf(stderr,"First Pipe failed");
    return 1;
  }
  
  if (pipe(second_pipe) == -1) {
      fprintf(stderr,"Second Pipe failed");
      return 1;
  }

  if(pipe(third_pipe) == -1){
    fprintf(stderr, "%s\n", "Third Pipe failed");
  }

  childpid = fork();
  if (childpid == -1)  {
    perror("Failed to fork");
    return 1; 
  }

  // CHILD 
  if (childpid == 0) {                           
   
    dup2(first_pipe[0], STDIN_FILENO);
    dup2(second_pipe[1], STDOUT_FILENO);
    dup2(third_pipe[1], STDERR_FILENO);

    close(first_pipe[WRITE_END]);  /* close the write and of the first pipe since child only reads from that pipe */
    close(second_pipe[READ_END]);  /* close the read and of the second pipe since child only writes to that pipe */
    close(first_pipe[READ_END]);   /* close the write and of the first pipe since child only reads from that pipe */
    close(second_pipe[WRITE_END]); /* close the read and of the second pipe since child only writes to that pipe */
    close(third_pipe[READ_END]);
    close(third_pipe[WRITE_END]);

    execl(argv[1], argv[1], NULL);
    return 1; 
  }
  // PARENT
  if (childpid > 0) {                
    close(first_pipe[READ_END]); 
    close(second_pipe[WRITE_END]); 
    close(third_pipe[WRITE_END]);
    int num1, num2;
    scanf("%d", &num1);
    scanf("%d", &num2);
    sprintf(w_buf, "%d\n%d", num1, num2);
    write(first_pipe[1], w_buf, strlen(w_buf));
    close(first_pipe[1]);
    read(second_pipe[0], r_buf, sizeof(r_buf));
    int err = read(third_pipe[0], e_buf, sizeof(e_buf));
    close(third_pipe[0]);
    close(second_pipe[0]);
    char buffer[10000];
    int status;

    if(err > 0){
      sprintf(buffer,"%s\n%s", "FAIL:", e_buf);
      status = write(output, &buffer, strlen(buffer));
    } else {
      sprintf(buffer, "%s\n%s", "SUCCESS:", r_buf);
      status = write(output, &buffer, strlen(buffer));
    }
    if(status < 0){
      printf("%s\n", "cannot write");
    }
   return 0; 
  }
}
