#To specify the base image which can be pulled from a container registry( Docker hub, GCR, Quay, ECR, etc)
# Debian is a Linux distribution thats composed entirely of free and open-source software.
FROM debian:buster 

EXPOSE 443

# update the package index -y is to say yes to all the prompts that come up
RUN apt update -y
RUN apt install nginx -y
RUN apt install vim -y    
RUN apt install curl -y
RUN apt -y install openssl

# store certificate and key in the container 
RUN mkdir -p /etc/nginx/ssl
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Lausanne/O=42/OU=42/CN=jolivier.42.fr/UID=jolivier"
#-x509 : This option outputs a self signed certificate instead of a certificate request. This is typically used to generate a test certificate or a self signed root CA.
#nodes : if this option is specified then if a private key is created it will not be encrypted.
#out : This specifies the output filename to write to or standard output by default.
#keyout : This gives the filename to write the newly created private key to.
#subj : This option sets the subject name to use. The arg must be formatted as /type0=value0/type1=value1/type2=..., characters may be escaped by \ (backslash), no spaces are skipped.
#La commande req crée et traite principalement des demandes de certificats au format PKCS#10. Elle peut en outre créer des certificats auto-signés.

RUN mkdir -p /var/run/nginx
#copy the configuration file from the current directory and paste it inside the container
COPY conf/nginx.conf /etc/nginx/nginx.conf

