FILE=./srcs/docker-compose.yml
GREE=\x1b[32m
BLU=\x1b[34m
RED=\x1b[31m
CLO=\033[0m

up:
	@echo "// ************** //"
	@echo "     STARTING       "
	@echo "// ************** //"
	@mkdir -p /home/jolivier/data &> /dev/null
	@mkdir -p /home/jolivier/data/wordpress &> /dev/null
	@mkdir -p /home/jolivier/data/mariadb &> /dev/null
	@docker-compose -f $(FILE) up -d

build:
	@echo "// ************** //"
	@echo "      BUILDING      "
	@echo "// ************** //"
	@docker-compose -f $(FILE) build

start:
	@docker-compose -f $(FILE) start

stop:
	@docker-compose -f $(FILE) stop

down:
	@docker-compose -f $(FILE) down

clean:
	@docker-compose -f $(FILE) down -v

msg:
	@echo "// ************** //"
	@echo "     SHUTDOWN       "
	@echo "     CLEANING       "
	@echo "// ************** //"

fclean: msg down clean 
	@docker rmi nginx:jolivier
	@docker rmi mariadb:jolivier
	@docker rmi wordpress:jolivier

prune:
	@docker system prune -af
	rm -rf /home/mbenbajj/data/* &> /dev/null

re : fclean build up

.PHONY : up build start stop down clean fclean re
