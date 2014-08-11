//
//  main.cpp
//  assignment OS
//
//  Created by Ryu@NorCal on 7/14/14.
//  Copyright (c) 2014 Ryu@NorCal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "project.h"
#define USER_HOST "user@host : "
using namespace std;
int main(int argc, const char * argv[])
{
  char command[100];
  
  bool exit = false;
  // insert code here...
  cout << "Boot up OS C... v 1.0.0\n";
  /***************************************************************************
   Start up
   **************************************************************************/
  OS *session = new OS();
 // if (!session->is_factory_reset()) {
    // ofstream file;
    // *session = *new OS(file);
 // }
  
  /***************************************************************************
   command line input
   **************************************************************************/
  while (!exit) {
    cout << USER_HOST;
    cin.getline(command,100);
    if(command == "quit" || command == "exit"){ exit = true;  }
    if(!session->command_switcher(command) && exit == false){  cout<< "command not found ...\n"; }
  }
  
  cout << "Bye! \n";
  return 0;
}