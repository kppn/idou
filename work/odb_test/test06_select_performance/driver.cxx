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

int
main (int argc, char* argv[])
{
  shared_ptr<database> db(new odb::mysql::database (argc, argv));

  typedef odb::query<Person> query;
  typedef odb::result<Person> result;

  shared_ptr<Person> p;

  for (auto i = 0; i < TRY; i++) {
    transaction t(db->begin());
    //for (auto j = 0; j < 100; j++) {
      p = db->query_one<Person>(query::name == "takashi");
      //result r(db->query<Person>());
    //}
    t.commit ();
  }
}

