FROM debian:buster

EXPOSE 3306

#temp, i need to remove it later with the docker compose
ENV SQL_DATABASE=inception
ENV SQL_USER=inception
ENV SQL_PASSWORD=inception
ENV SQL_ROOT_PASSWORD=inception




RUN apt update -y
RUN apt upgrade -y

RUN    apt-get install mariadb-server -y


COPY conf/mariadb.conf	/etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/my_sql.sh		/etc/mysql/my_sql.sh

RUN chmod 0444 /etc/mysql/mariadb.conf.d/50-server.cnf
RUN chmod 777 /etc/mysql/my_sql.sh
# RUN /etc/mysql/my_sql.shbin