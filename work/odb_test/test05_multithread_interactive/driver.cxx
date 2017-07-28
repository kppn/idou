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



const int N_CONNECTION = 3;

database * db;


void *f(void *p)
{
  {
    Person takashi("takashi", 20);

    transaction t(db->begin());

    db->persist(takashi);

    t.commit ();
  }

  cout << syscall(SYS_gettid) << endl;
  sleep(100000000);

  return NULL;
}



int
main (int argc, char* argv[])
{
  auto_ptr<odb::mysql::connection_factory> pool_factory(
    new odb::mysql::connection_pool_factory(N_CONNECTION)
  );
  db = new odb::mysql::database(argc, argv, false, "", 0, pool_factory);

  list<pthread_t *> threads;

  while (1) {
    string s;
    cin >> s;

    cout << "input is " << s << endl;

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
      return ch != '\n';
    }));

    if (s == "a") {
      pthread_t * th = new pthread_t;
      pthread_create( th, NULL, &f, (void *)NULL);
      threads.push_back(th);
    } else if (s == "d") {
      if (threads.size() == 0)
        continue;
      pthread_t * th = threads.front();
      threads.pop_front();
      pthread_cancel( *th );
      pthread_join(*th, NULL);
      delete th;
    }
  }
}

