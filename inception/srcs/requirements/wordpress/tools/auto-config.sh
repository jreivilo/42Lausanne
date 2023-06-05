#sleep of 10

sleep 10

wp config create	--allow-root \
						--dbname=$SQL_DATABASE \
						--dbuser=$SQL_USER \
						--dbpass=$SQL_PASSWORD \
						--dbhost=mariadb:3306 --path='/var/www/wordpress'

wp core install		--allow-root \
						--url=localhost \
						--title=ft_services \
						--admin_user=$WP_USER \
						--admin_password=$WP_PASSWORD \

wp user create		--allow-root \
						$WP_USER2 \
						$WP_USER2_EMAIL \
						--role=author \
						--user_pass=$WP_PASSWORD2
