FROM debian:buster 

RUN apt-get update -y
RUN apt-get install nginx -y
RUN apt-get install openssl -y
RUN rm -rf /var/lib/apt/lists/*

#copy the configuration file from the current directory and paste it inside the container
COPY conf/default /etc/nginx/sites-available/default
# COPY conf/nginx.conf /etc/nginx/nginx.conf
# RUN chmod 777 /etc/nginx/nginx.conf

COPY tools/cmd.sh /tmp/cmd.sh
RUN chmod 777 /tmp/cmd.sh

RUN openssl req -newkey rsa:4096 -x509 -days 365 -sha256 -nodes -keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.crt -subj "/CN=jolivier.42.fr" 
#-x509 : This option outputs a self signed certificate instead of a certificate request. This is typically used to generate a test certificate or a self signed root CA.
#nodes : if this option is specified then if a private key is created it will not be encrypted.
#out : This specifies the output filename to write to or standard output by default.
#keyout : This gives the filename to write the newly created private key to.
#subj : This option sets the subject name to use. The arg must be formatted as /type0=value0/type1=value1/type2=..., characters may be escaped by \ (backslash), no spaces are skipped.
#La commande req crée et traite principalement des demandes de certificats au format PKCS#10. Elle peut en outre créer des certificats auto-signés.

EXPOSE 443

ENTRYPOINT [ "/tmp/cmd.sh" ]
