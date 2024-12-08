import requests
import bs4 as bs
import os

# Constants for easy configuration
BASE_URL = "http://192.168.129.219//.hidden/"  # The starting URL for scraping
OUTPUT_DIR = "readme_scrapping"               # Directory to store results
OUTPUT_FILE = "results.txt"                   # File to save the scraped data
EXCLUDE_PHRASES = ["Demande", "Toujours", "Tu", "Non"]  # Phrases to exclude
TARGET_FILENAME = "README"                    # Target file to search for

def scrapping_recursive(url):
    """
    Recursively scrapes the given URL, searching for the target file (e.g., README).
    Extracts and saves data if it does not contain excluded phrases.
    """
    try:
        print(f"Processing URL: {url}")
        # Make a GET request to the URL
        response = requests.get(url)
        # Parse the HTML content with BeautifulSoup
        soup = bs.BeautifulSoup(response.text, 'html.parser')
        
        if soup is not None:
            # Find all anchor tags
            links = soup.find_all("a")

            # Ensure the output directory exists
            os.makedirs(OUTPUT_DIR, exist_ok=True)

            # Open the output file in append mode
            with open(os.path.join(OUTPUT_DIR, OUTPUT_FILE), "a+", encoding="utf-8") as f:
                for link in links:
                    # Get the href attribute of each link
                    final_link = link.get('href')

                    # Check if the link is the target file
                    if final_link == TARGET_FILENAME:
                        # Fetch the target file content
                        target_response = requests.get(url + final_link)
                        
                        # Filter the content by excluded phrases
                        if not any(phrase in target_response.text for phrase in EXCLUDE_PHRASES):
                            # Write the content to the file
                            f.write(target_response.text)

                    # If the link is not a parent directory, recurse
                    elif final_link != "../":
                        scrapping_recursive(url + final_link)
    
    except Exception as e:
        # Log errors for debugging purposes
        print(f"Error processing URL {url}: {e}")

# Start the scraping process
scrapping_recursive(BASE_URL)
