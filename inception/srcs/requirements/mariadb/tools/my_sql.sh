#!/bin/bash

if [ ! -d "/var/lib/mysql/$SQL_DATABASE" ]; then
	mysql_install_db --user=root --datadir=/var/lib/mysql
    service mysql start
    echo "$SQL_DATABASE database does not exist"
    mysql -u root -e "CREATE DATABASE $SQL_DATABASE;"
    mysql -u root -e "CREATE USER '$SQL_USER'@'%' IDENTIFIED BY '$SQL_PASSWORD';"
    mysql -u root -e "GRANT ALL PRIVILEGES ON *.* TO '$SQL_USER'@'%';"
	mysql -u root -e "FLUSH PRIVILEGES;"
    mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '$SQL_ROOT_PASSWORD';"
	mysql -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"

	mysql -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}' WITH GRANT OPTION;"
	mysql -u root -e "FLUSH PRIVILEGES;"
	mysqladmin -u root -p $SQL_ROOT_PASSWORD shutdown
fi

mysqld_safe