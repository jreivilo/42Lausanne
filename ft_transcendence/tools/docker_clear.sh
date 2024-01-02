#!/bin/bash

docker stop $(docker ps -qa)
docker rm $(docker ps -qa)
docker rmi $(docker images -q)
docker network rm $(docker network ls -q)