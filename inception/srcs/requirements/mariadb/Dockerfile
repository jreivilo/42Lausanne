FROM debian:buster

EXPOSE 3306

RUN apt update -y
RUN apt upgrade -y

RUN    apt-get install mariadb-server -y


COPY conf/mariadb.conf	/etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/my_sql.sh		/etc/mysql/my_sql.sh

# RUN /etc/mysql/my_sql.sh