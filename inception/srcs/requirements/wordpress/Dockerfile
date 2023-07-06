
FROM debian:buster

FROM debian:buster

# Set environment variables
# ENV SQL_DATABASE=wordpress
# ENV SQL_USER=db_user
# ENV SQL_PASSWORD=db_user_password
# ENV SQL_ROOT_PASSWORD=db_root_password
# ENV WP_URL=localhost
# ENV WP_TITLE=inception_j
# ENV WP_ADMIN_USER=admin
# ENV WP_ADMIN_PASSWORD=admin_password
# ENV WP_ADMIN_EMAIL=admin@localhost.fr
# ENV WP_USER=jolivier
# ENV WP_USER_MAIL=admin@localhost.ch
# ENV WP_USER_PASSWORD=user_password


RUN apt-get update -y
RUN apt-get install  php7.3-fpm php7.3-mysql mariadb-client curl -y
RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/php/7.3/fpm
COPY conf/www.conf /etc/php/7.3/fpm/pool.d

RUN mkdir /run/php

RUN	curl https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar --output /usr/bin/wp --silent \
&&	chmod +x ./usr/bin/wp

COPY tools/auto-config.sh /tmp/auto-config.sh
RUN chmod +x /tmp/auto-config.sh

RUN mkdir -p /var/www/wordpress
RUN chown -R www-data:www-data /var/www/wordpress
# RUN chmod -R 775 /var/www/wordpress/wp-content/plugins

# WORKDIR /var/www/wordpress

EXPOSE 9000

ENTRYPOINT [ "/tmp/auto-config.sh" ]
