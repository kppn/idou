DATABASE=test01
MYSQL_ROOT=mysql --user=root -proot123
MYSQL_TESTUSER=mysql --user=testuser -ptest123 $(DATABASE)

all:
	odb --std c++11 -d mysql --generate-query --generate-schema --default-pointer std::shared_ptr  person.hxx
	g++ -std=c++11 -c driver.cxx
	g++ -std=c++11 -c person-odb.cxx
	g++ -std=c++11 -o driver driver.o person-odb.o -lodb-mysql -lodb

migrate:
	$(MYSQL_TESTUSER) < person.sql

exec:
	./driver --user testuser --database $(DATABASE) --password test123

query:
	echo -n 'select * from person'   | $(MYSQL_TESTUSER)

setdb:
	echo -n 'CREATE USER 'testuser'@'%' IDENTIFIED BY 'test123';'                   | $(MYSQL_ROOT)
	echo -n 'GRANT all PRIVILEGES on *.* to 'testuser'@'%' IDENTIFIED BY 'test123'; | $(MYSQL_ROOT)
	echo -n 'CREATE DATABASE' $(DATABASE)                                           | $(MYSQL_ROOT)

