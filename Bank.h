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
    void activateATM(char* argv[]); // TODO: insert any additional inputs necessary, new thread leads to here - initiate ATM
    void AddAccountToMap(int id, Account& account); //TODO:make sure list is not locked (and lock it while adding account)... (new account/printing/commisions... is occurring)
    void ActivateReader_Map();
    void InactivateReader_Map();
    void ActivateWriter_Map();
    void InactivateWriter_Map();
    void ActivateReader_Log();
    void InactivateReader_Log();
    void ActivateWriter_Log();
    void InactivateWriter_Log();
    bool UnlockList(pthread_mutex_t);
    Account& returnAccount(int id); //TODO: this returns the account refrenced by ID. remember to maintain readers-writers (need to add readers counter) (this is a reader) while searching! return NULL if not found (important!)

private:
  std::map<int, Account&> AccountsMap; //This saves all the accounts
  pthread_mutex_t *MapLock_W;
  pthread_mutex_t *MapLock_R;
  pthread_mutex_t *LogLock_W;
    pthread_mutex_t *LogLock_R;
  int Readers_Map;
  int Readers_Log;
};

//TODO: while taking commision - lock each account at a time? while printing bank, lock all at once? or one at a time?
//TODO: add bank log (page 3 step 1 in directions)
#endif //WET02_BANK_H
