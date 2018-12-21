//
// Created by Omer on 12/15/2018.
//

#ifndef WET02_ATM_H
#define WET02_ATM_H

#include <pthread>

#include "Account.h


class ATM {
public:
    ATM(int id);
    bool ATMLock();
    bool ATMUnlock();
    bool ActUponCommand(char cmd, int args[]); //TODO: this function gets command name and arguments, and calls the other functions. Remember to sleep(1) during cmd, and sleep(0.1) between cmds (0.1 taken care of in bank)
    bool CreateAccount(int accountId,int psw,int init_balance);
    static AddToLog(); //TODO: need to build this: first decide how to maintain log. add params, go over all log-writing scenarios. remember to lock log if needed! (if so, may have to add logLock)
    ~ATM();

private:
    int id_;
    pthread_mutex_t lock_;
};


#endif //WET02_ATM_H
