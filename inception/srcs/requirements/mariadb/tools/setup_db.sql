-- FLUSH PRIVILIGES  maybe not needed (see https://stackoverflow.com/questions/36463966/mysql-when-is-flush-privileges-in-mysql-really-needed)
CREATE DATABASE wordpress;
CREATE USER 'db_user'@'%' IDENTIFIED BY '12db_user_password3';
GRANT ALL PRIVILEGES ON wordpress.* TO 'db_user'@'%';
FLUSH PRIVILEGES;

-- ALTER USER        give root a password. (root is the admin)
ALTER USER 'root'@'localhost' IDENTIFIED BY 'db_user_password';
