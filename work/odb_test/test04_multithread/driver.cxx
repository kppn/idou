#include <unistd.h>
#include <memory>
#include <iostream>
#include "pthread.h"

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include "person-odb.hxx"

using namespace std;
using namespace odb::core;




const int N_THREAD     = 3;
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

  cout << "hoge" << endl;
  int hoge; cin >> hoge;

  return NULL;
}



int
main (int argc, char* argv[])
{
  pthread_t threads[N_THREAD];

  auto_ptr<odb::mysql::connection_factory> pool_factory(
    new odb::mysql::connection_pool_factory(N_CONNECTION)
  );
  db = new odb::mysql::database(argc, argv, false, "", 0, pool_factory);

  for (pthread_t& th : threads) {
    cout << "create thread" << endl;
  	
    pthread_create( &th, NULL, &f, (void *)NULL);
  }

  for (pthread_t th : threads) {
    pthread_join( th, NULL);
  }
}

