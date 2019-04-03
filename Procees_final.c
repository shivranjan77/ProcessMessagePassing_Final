#include <string.h>
#include<stdio.h>
#include <unistd.h>   
#include<stdlib.h>
#include <sys/wait.h> 
#include <ctype.h>                         
int main(void)
{
int pid;
char st[70];
int fd1[2],fd2[2];
pipe(fd1);
pipe(fd2);
pid = fork();
if (pid == 0)
{
int count;
close(fd1[0]);
printf("Enter your Desired String  ");
fgets(st, sizeof(st), stdin);
printf("Child Original Message is %s", st);
int ct = write(fd1[1], st, strlen(st) + 1);
ct = read(fd2[0], st, sizeof(st));
printf("Child Inverted Message Recieved from Parent is %s", st);
}
else 
{
int ct,i;
close(fd1[1]);
ct = read(fd1[0], st, sizeof(st));
printf("Parent Recieved Message From Child is %s", st);
for(i = 0;i<sizeof(st);i++)
{
if(islower(st[i]))
  st[i] = toupper(st[i]);
else
  st[i] = tolower(st[i]);
}
printf("Parent Inverted Message Sent to Child is %s", st);
ct = write(fd2[1], st, strlen(st) + 1);
wait(NULL);
}
}
