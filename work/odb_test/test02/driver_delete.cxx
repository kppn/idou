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
    typedef odb::query<Person> query;
    typedef odb::result<Person> result;

    transaction t(db->begin());

    result r( db->query<Person>(query::name == "takashi") );

    if (! r.empty()) {
      Person person(*r.begin());
      cout << "delete : " << person.name() << endl;
      db->erase(person);
    }

    t.commit ();
  }
}

