//
// Created by Omer on 12/15/2018.
//
#ifndef WET02_BANK_H
#define WET02_BANK_H

#include <map>
#include "Account.h"
#include "ATM.h"


class Bank {
public:
    Bank(); //TODO: probably need more than default c'tor(?)
    static void* activateATM(void* p_params); // TODO: insert any additional inputs necessary, new thread leads to here - initiate ATM
    static void* takeCommission(void* bank);
    void AddAccountToMap(int id, Account& account); //TODO:make sure list is not locked (and lock it while adding account)... (new account/printing/commisions... is occurring)
    bool LockList(pthread_mutex_t);
    bool UnlockList(pthread_mutex_t);
    Account& returnAccount(int id); //TODO: this returns the account refrenced by ID. remember to maintain readers-writers (need to add readers counter) (this is a reader) while searching! return NULL if not found (important!)

private:
  std::map<int, Account&> AccountsMap; //This saves all the accounts
  pthread_mutex_t write_MapLock_;
  pthread_mutex_t read_MapLock_;
  pthread_mutex_t logLock_;
};

typedef struct parameters{
    int ATM_id_;
    string argv;
} params, *p_params;


//TODO: while taking commision - lock each account at a time? while printing bank, lock all at once? or one at a time?
//TODO: add bank log (page 3 step 1 in directions)
#endif //WET02_BANK_H
