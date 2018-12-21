//
// Created by Omer on 12/15/2018.
//

#include "Account.h"

Account::~Account(){
    pthread_mutex_destroy(&lock_);
    std::list<int>::iterator itr = AccountIDs.find(accountNum_);
    AccountIDs.erase(itr);
}

bool Account::TakeMoney (int value){
    if (balance_-value<0)
        return false;
    else balance_-=value;
    return true;
}

bool Account::LockAccount(){
    while (readers_!=0){
        sleep(0.01); //TODO: is there a more correct way to do this? (like semaphore)
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
}

bool Account::DoesAccountExist(int id) const {
    int res = pthread_mutex_lock(&ListLock_);
    if (res!=0){
        perror("Lock Failed:");
        return false; //TODO: what to do if lock failed (not waiting, simply failed)- exit program? of course this is in all lock funcs
    }

    if ((int)AccountIDs.find!=AccountIDs.end()){ //account already exists!
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
