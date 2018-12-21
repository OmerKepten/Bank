//
// Created by Omer on 12/15/2018.
//

#include "ATM.h"


ATM::ATM() { //TODO: complete (+d'tor)

}
bool ATM::CreateAccount(int accountId, int psw, int init_balance) {
    if (Account::DoesAccountExist(accountId)) {
        cout<<"Error "<<id_<<": Your transaction failed - account with the same id exists"<<endl;
        reuturn false;
    }
    Account a = new Account(accountId,psw,init_balance);
    Bank::AddAccountToMap(&a); //map is locked- dont worry
    cout<<id_<<": New account id is "<<accountId<<" with password "<<psw<<" and initial balance "<<init_balance<<endl;
    return true;
}

bool ATM::ActUponCommand(char cmd, int args[]) {

    //TODO: based on AddToLog func, decide if can unlock accounts before adding to log (shorter lock time=better). if so, change order in relevant sections!
//TODO: CHECK while writing to log that we're not using anything that needs reading from account!

   if (args==NULL || args[0]==NULL|| cmd==NULL)return false; //TODO: any more input checks required? (generally in program) what about args2,3 for some of the commands? is it promised commands are ok??

    std::string AccountID = args[0];

    //check target account exists:
    Account account_a= Bank::returnAccount(AccountID);
    if ((account_a==NULL) && (cmd!="O")){

        cout << "Error " << id_ << ": Your transaction failed - account id " << AccountID << " does not exist" << endl;
        return false; //TODO: decide what to do when fails... (for all commands below as well!)
    }

    //Command: Open new account
    if(cmd=="O"){
        if (account_a!=NULL){ //account already exists!
            AddToLog(); //TODO: complete with correct error, lock log!
            return false; //TODO: decide what to do when fails...
        }
        if (CreateAccount(AccountID,args[1],args[2])){
            AddToLog(); //TODO: complete with correct error, lock log!
        };
        //TODO: what happens if createAccount fails?

        return true;
    }

    //Command: Set account as VIP (writer)
    else if (cmd=="L"){
        account_a.ActivateReader();
        int psw = account_a.getPsw();
        account_a.InactivateReader();
        if(args[1]!=psw){ //wrong psw!
            cout << "Error " << id_ << ": Your transaction failed - password for account id " << AccountID << " is incorrect" << endl; //TODO: are we sure should be printed, and not logged (may be a mistake in directions...)
            return false;
        }

        account_a.ActivateWriter();
        account_a.SetVIP(true);
        account_a.InactivateWriter();
        return true;
    }

    //Command: Add money to account (writer)
    else if (cmd=="D"){
        account_a.ActivateReader();
        int psw=account_a.getPsw();
        account_a.InactivateReader();

        if(args[1]!=psw){ //wrong psw!
            AddToLog(); //TODO: complete with correct error (wrong psw), lock log!
            return false;
        }

        account_a.ActivateWriter();
        account_a.AddMoney(args[2]);
        account_a.InactivateWriter();

        AddToLog(); //TODO:add success msg to log...
        return true;
    }

    //Command: Take money from account (writer)
    else if (cmd=="W"){
        account_a.ActivateReader();
        int psw = account_a.getPsw();
        account_a.InactivateReader();

        if(args[1]!=psw()){ //wrong psw!
            AddToLog(); //TODO: complete with correct error (wrong psw), lock log!
            return false;
        }

        account_a.ActivateWriter();
        bool res = account_a.TakeMoney(args[2]);
        account_a.InactivateWriter;

        if (res==false){ //there was not enough money in balance
            AddToLog();  //TODO: complete with correct error, lock log!
        }
        else AddToLog(); //money was taken successfully //TODO: complete with correct error, lock log!

        return res;
    }

    //command: reads balance from account
    else if (cmd=="B"){
        account_a.ActivateReader();
        int psw = account_a.getPsw();
        account_a.InactivateReader();

        if(args[1]!=psw()){ //wrong psw!
            AddToLog(); //TODO: complete with correct error (wrong psw), lock log!
            return false;
        }

        account_a.ActivateReader();
        int bal = account_a.getBalance();
        account_a.InactivateReader();

        AddToLog(); //complete got balance log msg;
        return true;
    }


    //command: transfer from one account to the other
    else if (cmd=="T"){
        Account account_b = Bank::returnAccount(args[2]);
        if (account_b==NULL){
            cout << "Error " << id_ << ": Your transaction failed - account id " << AccountID << " does not exist" << endl; //TODO:are we sure we're supposed to print, not log? may be a mistake in directions
            return false; //TODO: decide what to do when fails... (for all commands below as well!)
        }

        //handle account_a:
        account_a.ActivateReader();
        int psw = account_a.getPsw();
        account_a.InactivateReader();

        if(args[1]!=psw){ //wrong psw!
            AddToLog(); //TODO: complete with correct error (wrong psw), lock log! //note account_a
            return false;
        }

        account_a.ActivateWriter();
        bool res = account_a.TakeMoney(args[3]);
        account_a.InactivateWriter();

        if (res==false){ //there was not enough money in balance
            AddToLog();  //TODO: complete with correct error, lock log!
            return false;
        }

        account_b.ActivateWriter();
        account_b.AddMoney(args[3]);
        account_b.InactivateWriter();
        AddToLog(); //add to log, transaction successful
        return true;
    }

    else return false; //TODO: need to do something is cmd does not exist?
}