//
// Created by Omer on 12/15/2018.
//

#include "Bank.h"

Bank::Bank(){
    if(pthread_mutex_init(MapLock_W)!=0) {
        perror("Mutex init failed:");
        exit(-1);
    }
    if(pthread_mutex_init(LogLock_W)!=0) {
        pthread_mutex_destroy(MapLock_W);
        perror("Mutex init failed:");
        exit(-1);
    }
    if(pthread_mutex_init(LogLock_R)!=0) {
        pthread_mutex_destroy(MapLock_W);
        pthread_mutex_destroy(LogLock_W);
        perror("Mutex init failed:");
        exit(-1);
    }
    if(pthread_mutex_init(MapLock_R)!=0) {
        pthread_mutex_destroy(MapLock_W);
        pthread_mutex_destroy(LogLock_W);
        pthread_mutex_destroy(LogLock_R);
        perror("Mutex init failed:");
        exit(-1);
    }
    Readers_Log=0;
    Readers_Map=0;
}

Bank::~Bank(){
    pthread_mutex_destroy(MapLock_W);
    pthread_mutex_destroy(LogLock_W);
    pthread_mutex_destroy(MapLock_R);
    pthread_mutex_destroy(LogLock_R);
}

void Bank::ActivateReader_Log() {
    if(pthread_mutex_lock(LogLock_R)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    Readers_Log++;
    if (Readers_Log==1){
        if(pthread_mutex_lock(LogLock_W)!=0){
            perror("Lock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(LogLock_R)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}
void Bank::ActivateReader_Map() {
    if(pthread_mutex_lock(MapLock_R)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    Readers_Map++;
    if (Readers_Map==1){
        if(pthread_mutex_lock(MapLock_W)!=0){
            perror("Lock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(MapLock_R)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}
void Bank::InactivateReader_Map() {
    int res=pthread_mutex_lock(MapLock_R);
    if (res!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    Readers_Map--;
    if (Readers_Map==0){
        if(pthread_mutex_unlock(MapLock_W)!=0){
            perror("Unlock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(MapLock_R)!0){
        perror("Unlock Failed:");
        exit(-1);
    }
}
void Bank::InactivateReader_Log() {
    int res=pthread_mutex_lock(LogLock_R);
    if (res!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    Readers_Log--;
    if (Readers_Log==0){
        if(pthread_mutex_unlock(LogLock_W)!=0){
            perror("Unlock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(LogLock_R)!0){
        perror("Unlock Failed:");
        exit(-1);
    }
}
void Bank::ActivateWriter_Log() {
    if(pthread_mutex_lock(LogLock_W)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}
void Bank::ActivateWriter_Map() {
    if(pthread_mutex_lock(MapLock_W)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}
void Bank::InactivateWriter_Log() {
    if(pthread_mutex_unlock(LogLock_W)!=0){
        perror("Unlock Failed:");
        exit(-1);
    }
}
void Bank::InactivateWriter_Map() {
    if(pthread_mutex_unlock(MapLock_W)!=0){
        perror("Unlock Failed:");
        exit(-1);
    }
}

void Bank::activateATM(char* argv[]) {  //TODO: create new ATM. read file. ActUponCommand (sleep(0.1) between lines)
}
