//
// Created by Omer on 12/15/2018.
//

#include "Account.h"

Account::Account(int AccountNum, int AccountPsw, int balance) {
    if (AccountNum==NULL||AccountPsw==NULL||balance==NULL){
        return;
    }
    accountNum_=AccountNum;
    accountPsw_=AccountPsw;
    balance_=balance;
    VIP=false;
    if(pthread_mutex_init(read_lock,NULL)!=0 {
        perror("Lock init failed:");
        exit(-1);
    }
    if(pthread_mutex_init(write_lock,NULL)!=0 {
        perror("Lock init failed:");
        pthread_mutex_destroy(read_lock);
        exit(-1);
    }
    ReadersNum=0;
}
Account::~Account(){
    pthread_mutex_destroy(write_lock);
    pthread_mutex_destroy(read_lock);
    //TODO: delete from Bank map! (or is it done in ATM? Is there even a need?)
}
bool Account::TakeMoney (int value){
    if (balance_-value<0)
        return false;
    else balance_-=value;
    return true;
}
/*bool Account::LockAccount(){
    while (readers_!=0){
        sleep(0.01); //
    }
    int res = pthread_mutex_lock(&lock_);
    if (res==0){
        return true;
    }
    perror("Lock Failed:");
    return false;
}
bool Account::UnlockAccount(){
    int res = pthread_mutex_unlock(&lock_);
    if (res==0){
        return true;
    }
    perror("Unlock Failed:");
    return false;
}*/

void ActivateReader(){
    if(pthread_mutex_lock(read_lock)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    ReadersNum++;
    if (ReadersNum==1){
        if(pthread_mutex_lock(write_lock)!=0){
            perror("Lock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(read_lock)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}

void InactivateReader(){
    int res=pthread_mutex_lock(read_lock);
    if (res!=0){
        perror("Lock Failed:");
        exit(-1);
    }
    ReadersNum--;
    if (ReaderNum==0){
        if(pthread_mutex_unlock(write_lock)!=0){
            perror("Unlock Failed:");
            exit(-1);
        }
    }
    if(pthread_mutex_unlock(read_lock)!0){
        perror("Unlock Failed:");
        exit(-1);
    }
}

void ActivateWriter(){
    if(pthread_mutex_lock(write_lock)!=0){
        perror("Lock Failed:");
        exit(-1);
    }
}

void InactivateWriter(){
    if(pthread_mutex_unlock(write_lock)!=0){
        perror("Unlock Failed:");
        exit(-1);
    }
}

bool Account::DoesAccountExist(int id) const {
    int res = pthread_mutex_lock(&ListLock_);
    if (res!=0){
        perror("Lock Failed:");
        return false; //TODO: what to do if lock failed (not waiting, simply failed)- exit program? of course this is in all lock funcs
    }

    if (AccountIDs.find(int)!=AccountIDs.end()){ //account already exists!
        res=pthread_mutex_unlock(&ListLock_);
        if (res!=0){
            perror("Lock Failed:");
           //TODO: what to do if lock failed (not waiting, simply failed)- exit program? of course this is in all lock funcs
        }
        return true;
    }
    res=pthread_mutex_unlock(&ListLock_);
    if (res!=0){
        perror("Lock Failed:");
        //TODO: what to do if lock failed (not waiting, simply failed)- exit program? of course this is in all lock funcs
    }
    return false;
}
