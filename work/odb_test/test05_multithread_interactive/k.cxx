#include <unistd.h>
#include <memory>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include "pthread.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include "person-odb.hxx"

using namespace std;
using namespace odb::core;


int
main (int argc, char* argv[])
{
  while (1) {
    string s;
    cin >> s;

    cout << "input is " << s << endl;
  }
}

