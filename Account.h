//
// Created by Omer on 12/15/2018.
//

#ifndef WET02_ACCOUNT_H
#define WET02_ACCOUNT_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>




class Account {
public:
    Account();
    Account(int AccountNum, int AccountPsw, int balance);
    int const getNum() {return accountNum_;} const;
    int const getPsw() {return accountPsw_;} const;
    int const getBalance(){return balance_;} const;
    void SetVIP(bool VIPStatus){VIP=VIPStatus;};
    bool AddMoney(int value){balance_+=value; return true;};
    bool TakeMoney (int value);
    bool static DoesAccountExist(int id); //TODO: here the lock is placed inside the static func (instead of in ATM area like other funcs) - make sure the list is truly locked from any ATM
                                            // TODO: note: in retrospect we can probably just use map in banks...is there a reason not to?

    void ActivateReader();
    void InactivateReader();
    void ActivateWriter();
    void InactivateWriter();
    //bool LockAccount();
    //bool UnlockAccount();
    ~Account();

private:
    int accountNum_;
    int accountPsw_;
    int balance_;
    bool VIP;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *read_lock;
    int ReadersNum;
};



#endif //WET02_ACCOUNT_H
