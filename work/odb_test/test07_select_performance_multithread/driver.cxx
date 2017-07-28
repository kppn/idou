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



#define TRY 30000
const int N_THREAD     = 1;
const int N_CONNECTION = 1;

database * db;


void *f(void *p)
{
  shared_ptr<Person> person;
  typedef odb::query<Person> query;
  typedef odb::result<Person> result;

  for (auto i = 0; i < (TRY/N_THREAD); i++)
  {
    transaction t(db->begin());

    person = db->query_one<Person>(query::name == "takashi");

    t.commit ();
  }

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

