DATABASE=test02
MYSQL_ROOT=mysql --user=root -proot123
MYSQL_TESTUSER=mysql --user=testuser -ptest123 $(DATABASE)

all:
	odb --std c++11 -d mysql --generate-query --generate-schema --default-pointer std::shared_ptr  person.hxx
	g++ -std=c++11 -c person-odb.cxx
	g++ -std=c++11 -c driver_insert.cxx
	g++ -std=c++11 -c driver_select.cxx
	g++ -std=c++11 -c driver_update.cxx
	g++ -std=c++11 -c driver_delete.cxx
	g++ -std=c++11 -o driver_insert driver_insert.o person-odb.o -lodb-mysql -lodb
	g++ -std=c++11 -o driver_select driver_select.o person-odb.o -lodb-mysql -lodb
	g++ -std=c++11 -o driver_update driver_update.o person-odb.o -lodb-mysql -lodb
	g++ -std=c++11 -o driver_delete driver_delete.o person-odb.o -lodb-mysql -lodb

clean:
	rm -f *odb*
	rm -f driver_insert
	rm -f driver_select
	rm -f driver_update
	rm -f driver_delete
	rm -f *.sql
	rm -f *.o

migrate:
	$(MYSQL_TESTUSER) < person.sql

exec_insert:
	./driver_insert --user testuser --database test02 --password test123

exec_select:
	./driver_select --user testuser --database test02 --password test123

exec_update:
	./driver_update --user testuser --database test02 --password test123

exec_delete:
	./driver_delete --user testuser --database test02 --password test123

query:
	echo -n 'select * from people'   | $(MYSQL_TESTUSER)

delete:
	echo -n 'delete from people;'    | $(MYSQL_TESTUSER)

create_database:
	echo -n 'CREATE DATABASE' $(DATABASE)                                           | $(MYSQL_ROOT)

setdb:
	echo -n 'CREATE USER 'testuser'@'%' IDENTIFIED BY 'test123';'                   | $(MYSQL_ROOT)
	echo -n 'GRANT all PRIVILEGES on *.* to 'testuser'@'%' IDENTIFIED BY 'test123'; | $(MYSQL_ROOT)

