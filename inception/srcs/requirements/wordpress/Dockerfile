FROM debian:buster

RUN apt-get update -y
RUN apt-get install  php7.3-fpm php7.3-mysql mariadb-client curl -y
RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/php/7.3/fpm
COPY conf/www.conf /etc/php/7.3/fpm/pool.d

RUN mkdir /run/php
RUN rm -rf /var/www/wordpress/wp-config.php

RUN	curl https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar --output /usr/bin/wp --silent \
&&	chmod +x ./usr/bin/wp

COPY tools/auto-config.sh /tmp/auto-config.sh
RUN chmod +x /tmp/auto-config.sh

# WORKDIR /var/www/wordpress

EXPOSE 9000

ENTRYPOINT [ "/tmp/auto-config.sh" ]