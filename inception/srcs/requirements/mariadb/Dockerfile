FROM debian:buster

RUN apt update -y
# RUN apt upgrade -y

RUN    apt-get install mariadb-server -y
RUN rm -rf /var/lib/apt/lists/*

COPY ./conf/mariadb.conf /etc/mysql/mariadb.conf.d

# COPY conf/mariadb.conf	/etc/mysql/mariadb.conf.d/50-server.cnf
# RUN chmod 0444 /etc/mysql/mariadb.conf.d/50-server.cnf

COPY tools/my_sql.sh		/etc/mysql/my_sql.sh
RUN chmod 777 /etc/mysql/my_sql.sh

COPY ./tools/setup_db.sql /

RUN service mysql start ; \
    mysql < setup_db.sql ; \
    rm -rf setup_db.sql

EXPOSE 3306

# CMD ["bash", "/etc/mysql/my_sql.sh"]

CMD ["mysqld_safe"]