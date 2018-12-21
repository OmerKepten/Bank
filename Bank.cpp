//
// Created by Omer on 12/15/2018.
//
#include <fstream>
#include "Bank.h"

#include <sstream>
#include <string>

void* Bank::activateATM(void* parameters) {  //TODO: create new ATM. read file. ActUponCommand (sleep(0.1) between lines)
    p_params pp = (p_params) parameters;
    int id = pp->ATM_id_;
    string file_name = pp->argv;
    ATM atm = new ATM(id);
    ifstream infile(file_name);
    while (getline(infile, line)) {
        char command = line[0];
        int args[4];//0 - account num, 1 - password, 2 - amount \ target account, 3 - period \ amount
        parse(args, line);
        atm.ActUponCommand(cmd, args);
        sleep(0.1);
        getline(infile, line);
    }
}

Account& Bank::returnAccount(int id){
    //activate reader map
    Account a = AccountsMap[id];
    return a;
    //inactivate reader map
}
