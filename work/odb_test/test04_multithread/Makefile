DATABASE=test04
MYSQL_ROOT=mysql --user=root -proot123
MYSQL_TESTUSER=mysql --user=testuser -ptest123 $(DATABASE)

all:
	odb --std c++11 -d mysql --generate-query --generate-schema --default-pointer std::shared_ptr  person.hxx
	g++ -std=c++11 -c person-odb.cxx
	g++ -std=c++11 -c driver.cxx
	g++ -std=c++11 -o driver driver.o person-odb.o -lodb-mysql -lodb -lpthread

clean:
	rm -f *odb*
	rm -f driver
	rm -f *.sql
	rm -f *.o

migrate:
	$(MYSQL_TESTUSER) < person.sql

exec:
	./driver --user testuser --database $(DATABASE) --password test123 --host 127.0.0.1 --port 3306

query:
	echo -n 'select * from people'   | $(MYSQL_TESTUSER)

delete:
	echo -n 'delete from people;'    | $(MYSQL_TESTUSER)

create_database:
	echo -n 'CREATE DATABASE' $(DATABASE)                                           | $(MYSQL_ROOT)

setdb:
	echo -n 'CREATE USER 'testuser'@'%' IDENTIFIED BY 'test123';'                   | $(MYSQL_ROOT)
	echo -n 'GRANT all PRIVILEGES on *.* to 'testuser'@'%' IDENTIFIED BY 'test123'; | $(MYSQL_ROOT)

