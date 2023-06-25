#!/bin/bash

sleep 8

cd /var/www/wordpress

echo "Installing wordpress..."
rm -rf /var/www/wordpress/*

wp core download --allow-root

wp core config	\
				--dbname=$SQL_DATABASE \
				--dbuser=$SQL_USER \
				--dbpass=$SQL_PASSWORD \
				--dbhost=mariadb:3306 \
				--allow-root

# install the wp instance and set the admin user and general infos like title and url
wp core install \
				--admin_user=$WP_ADMIN_USER \
				--admin_password=$WP_ADMIN_PASSWORD \
				--admin_email=$WP_ADMIN_EMAIL \
				--title=$WP_TITLE \
				--url=$WP_URL \
				--allow-root

# create the first non-admin user
wp user create \
				$WP_USER \
				$WP_USER_MAIL \
				--role=author \
				--user_pass=$WP_USER_PASSWORD \
				--allow-root

php-fpm7.3 -F





# #https://developer.wordpress.org/cli/commands/core/install/

# echo "Waiting for mariadb to be ready..."
# sleep 8
# ls
# echo "Starting auto-config.sh"
# wp --info

# rm -rf /var/www/html/*

# echo "Installing wordpress..."
# wp core download --allow-root

# echo "Creating wp-config.php..."
# wp config create --allow-root --dbname=$SQL_DATABASE --dbuser=$SQL_USER --dbpass=$SQL_PASSWORD --dbhost=mariadb:3306
# ls
# pwd

# # echo "Creating ADMIN user..."
# # wp core install --allow-root \
# # 	--allow-root \
# # 	--url=https://localhost:443 \
# # 	--title=ft_services \
# # 	--admin_user=$WP_USER \
# # 	--admin_password=$WP_PASSWORD \
# # 	--admin_email=$WP_USER_EMAIL \
# # 	--skip-email

# # echo "Creating author user..."
# # wp user create --allow-root \
# # 	$WP_USER2 \
# # 	$WP_USER2_EMAIL \
# # 	--role=author \
# # 	--user_pass=$WP_PASSWORD2

# chown -R www-data:www-data /var/www/html
# service php7.3-fpm start;
# service php7.3-fpm stop


# php-fpm7.3 -F