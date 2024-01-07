#!/bin/bash

echo "Start mysql"
# mysql_install_db --user=root --datadir=/var/lib/mysql
service mysql start

# Wait for the MariaDB service to start
sleep 5
# mysql -u $SQL_USER -p$SQL_PASSWORD -e "DROP DATABASE $SQL_DATABASE;"
# Perform the initial setup of the MariaDB server

# mysql -u "$SQL_USER" -p"$SQL_PASSWORD" -e "USE $SQL_DATABASE; SHOW TABLES;" | grep -v Tables_in | grep -v "+" | grep -v "^$" | xargs -L1 -I% mysql -u "$SQL_USER" -p"$SQL_PASSWORD" -e "USE $SQL_DATABASE; SET FOREIGN_KEY_CHECKS=0; DROP TABLE %; SET FOREIGN_KEY_CHECKS=1;"
# Delete all other objects (procedures, functions, triggers, etc.)
# mysql -u "$SQL_USER" -p"$SQL_PASSWORD" -e "USE $SQL_DATABASE; SELECT CONCAT('DROP ', OBJECT_TYPE, ' ', OBJECT_NAME, ';') FROM INFORMATION_SCHEMA.OBJECTS WHERE OBJECT_SCHEMA='$SQL_DATABASE';" | grep -v CONCAT | mysql -u "$SQL_USER" -p"$SQL_PASSWORD"
# rm -rf /var/lib/mysql/$SQL_DATABASE
mysql -u $SQL_USER -p$SQL_PASSWORD -e "SHOW DATABASES;" | grep -Ev "(Database|mysql|performance_schema|information_schema)" | awk '{print "DROP DATABASE IF EXISTS " $1 ";"}' | mysql -u $SQL_USER -p$SQL_PASSWORD

if [ ! -d "/var/lib/mysql/$SQL_DATABASE" ]; then
	echo "Create DB and USER"
	mysql -e "CREATE DATABASE IF NOT EXISTS $SQL_DATABASE;"
	mysql -e "GRANT ALL PRIVILEGES ON $SQL_DATABASE.* TO $SQL_USER@'%' IDENTIFIED BY '$SQL_PASSWORD';"
	mysql -e "FLUSH PRIVILEGES;"

	# Print a message indicating the setup is complete
	echo "MariaDB setup completed!"
	echo "Stop mysql"
	service mysql stop
fi

mysqld_safe
# echo "RM old db"
# rm -rf /var/lib/mysql/$SQL_DATABASE
# if [ ! -d "/var/lib/mysql/$SQL_DATABASE" ]; then
# 	mysql_install_db --user=root --datadir=/var/lib/mysql
# 	sleep 3
# 	echo "Start mysql"
#     service mysql start
#     echo "$SQL_DATABASE database does not exist"
# 	echo "$SQL_DATABASE creation ..."
#     mysql -u root -e "CREATE DATABASE $SQL_DATABASE;"
# 	echo 
#     mysql -u root -e "CREATE USER '$SQL_USER'@'%' IDENTIFIED BY '$SQL_PASSWORD';"
#     mysql -u root -e "GRANT ALL PRIVILEGES ON *.* TO '$SQL_USER'@'%';"
# 	mysql -u root -e "FLUSH PRIVILEGES;"
#     mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '$SQL_ROOT_PASSWORD';"

# 	mysql -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"
# 	mysql -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}' WITH GRANT OPTION;"
# 	mysql -u root -e "FLUSH PRIVILEGES;"
# 	mysqladmin -u root -p $SQL_ROOT_PASSWORD shutdown
# 	service mysql stop
# fi

# cclean