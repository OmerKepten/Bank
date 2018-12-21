#include <iostream>
#include <pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Bank.h"

int main(int argc, char* argv[]) {

    //It is promised arguments are correct- no need to check
    int NumOfATMs = atoi(argv[1]);
    int ThreadIdx=1;

    //TODO: add Bank initialization (includes opening the Bank's own account)
    pthread_create((pthread_t)ThreadIdx,NULL,&Bank::TakeCommissions,NULL); //This is the thread responsible for bank commissions
    ThreadIdx++;

    for (int i=ThreadIdx;i<=NumOfATMs+ThreadIdx;i++){ //ATM initialization
        pthread_create((pthread_t)i,NULL,&Bank::activateATM,argv[i+2]);
    }

    //TODO: do some things, any other threads etc

    //at the end, collect all threads:
    for (int i=1;i<=ThreadIdx;i++){
        int res;
        pthread_join((pthread_t)i,res);
        if (res!=0){
            perror("");
            //TODO: add error handling
        }
    }
    pthread_join()
}

