FROM debian:buster

RUN apt update -y
# RUN apt upgrade -y

RUN    apt-get install mariadb-server -y
RUN rm -rf /var/lib/apt/lists/*

COPY ./conf/mariadb.conf /etc/mysql/mariadb.conf.d

# COPY conf/mariadb.conf	/etc/mysql/mariadb.conf.d/50-server.cnf
# RUN chmod 0444 /etc/mysql/mariadb.conf.d/50-server.cnf

COPY tools/my_sql.sh	/etc/mysql/my_sql.sh
RUN chmod 777 /etc/mysql/my_sql.sh

EXPOSE 3306

ENTRYPOINT [ "/etc/mysql/my_sql.sh" ]
