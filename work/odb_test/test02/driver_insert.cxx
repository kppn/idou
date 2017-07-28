#include <memory>
#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include "person-odb.hxx"

using namespace std;
using namespace odb::core;

int
main (int argc, char* argv[])
{
  shared_ptr<database> db(new odb::mysql::database (argc, argv));

  {
    Person takashi("takashi", 20);

    transaction t(db->begin());

    db->persist(takashi);

    t.commit ();

    int a;
    cin >> a;
  }
}
