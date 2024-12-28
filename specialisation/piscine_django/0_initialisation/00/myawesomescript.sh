#!/bin/sh

# On vérifie qu'un argument (l'URL bit.ly) est fourni
if [ $# -ne 1 ]; then
    echo "Usage: $0 <bit.ly URL>"
    exit 1
fi

# Récupération de l'URL finale, $1 est le premier argument passé au script
curl -sIL "$1" \
  | grep -i '^Location:' \
  | tail -n1 \
  | cut -d ' ' -f2 \
  | tr -d '\r'
