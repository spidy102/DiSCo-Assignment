#include<unistd.h>
void plot(char * fname){
    int pid;
    if((pid = fork())==0){
        if(execlp("python", "python","visualise.py",fname,(char*)NULL)==-1){
        	execlp("python3", "python3","visualise.py",fname,(char*)NULL);
        };
    }
    exit(0);
}
int main(){
    plot("mycsv.csv");
    return 0;
}
