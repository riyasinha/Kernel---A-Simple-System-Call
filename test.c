#include <stdio.h>

#include <linux/kernel.h>

#include <sys/syscall.h>

#include <unistd.h>


int main()

{
	
long int trycall = syscall(318,1,"text.txt");
	
	if(trycall==0)
		
		printf("Correctly Executed");

	else

		printf("Error in Execution");


	return 0;

}
