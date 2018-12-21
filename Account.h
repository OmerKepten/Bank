//
// Created by Omer on 12/15/2018.
//

#ifndef WET02_ACCOUNT_H
#define WET02_ACCOUNT_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <std::list>

class Account {
public:
    Account();
    Account(int AccountNum, int AccountPsw, int balance): accountNum_=AccountNum, accountPsw_=AccountPsw,balance_=balance, VIP=FALSE{pthread_mutex_init(&lock_,NULL); AccountIDs.push_back(accountNum_); readers_=0;};
    int const getNum() {return accountNum_;} const;
    int const getPsw() {return accountPsw_;} const;
    int const getBalance(){return balance_;} const;
    void SetVIP(bool VIPStatus){VIP=VIPStatus;};
    bool AddMoney(int value){balance_+=value; return true;};
    bool TakeMoney (int value);
    bool static DoesAccountExist(int id); //TODO: here the lock is placed inside the static func (instead of in ATM area like other funcs) - make sure the list is truly locked from any ATM
                                            // TODO: note: in retrospect we can probably just use map in banks...is there a reason not to?
    bool LockAccount();
    bool UnlockAccount();
    ~Account();

private:
    int accountNum_;
    int accountPsw_;
    int balance_;
    bool VIP;
    pthread_mutex_t lock_; //TODO: make sure actually locks the whole object!
    int readers_; //TODO: for readers-writers mechanism - instead of semaphore. is this ok? we can have multiple readers but writer cannot access until all are done, and writer locks the account as well
    static std::list<int> AccountIDs; // TODO: honestly I don't remember static members so I need to check if its ok.. note: in retrospect we can probably just use map in banks...is there a reason not to?
    static pthread_mutex_t  ListLock_; //TODO: where do I initialize (pthread_mutex_init) it (need to review static rules, sorry..)
};



#endif //WET02_ACCOUNT_H
