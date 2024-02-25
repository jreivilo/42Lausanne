# Use PHP with Apache as the base image
FROM php:7.4-fpm

RUN apt-get update && apt-get install -y nginx

# Install extensions and any other necessary packages
RUN docker-php-ext-install pdo pdo_mysql

# Copy the application code to the container
COPY . /var/www/html

#copy configuration files nginx
COPY nginx.conf /etc/nginx/conf.d/default.conf

# Expose port 80 to access the web server
EXPOSE 80

CMD service nginx start && php-fpm
