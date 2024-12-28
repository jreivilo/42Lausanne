import sys

# Path to the periodic_table.txt file
PERIODIC_TABLE_FILE = "periodic_table.txt"
OUTPUT_HTML_FILE = "periodic_table.html"

def parse_periodic_table(file_path):
    """Parses the periodic_table.txt file where each line contains comma-separated key:value pairs."""
    elements = []
    with open(file_path, "r") as file:
        for line in file:
            # Split the line by comma
            parts = line.strip().split(",")
            # Extract name from the first part
            name_part = parts[0].split("=") #EX Hydrogen = position:0 -> name_part = ["Hydrogen ", " position:0"]
            name = name_part[0].strip()  #EX "Hydrogen "
            properties = {"name": name}
            
            position = parts[0].split(":")[-1]
            properties["position"] = position
            
            # Parse the remaining key:value pairs
            for part in parts[1:]:
                key, value = part.split(":")
                key = key.strip()
                value = value.strip()
                properties[key] = value
            # Add parsed element to the list
            elements.append({
                "name": properties["name"],
                "position": int(properties["position"]),
                "number": int(properties["number"]),
                "symbol": properties["small"],
                "mass": properties["molar"],
            })
    return elements

def generate_html(elements):
    """Generates the HTML for the periodic table."""
    # Calculate the number of rows and columns needed
    max_position = max(e["position"] for e in elements)
    rows = 7  # Periods in the periodic table
    columns = max_position + 1  # Groups in the periodic table

    # Create a 2D array representing the table
    table = [[None for _ in range(columns)] for _ in range(rows)]
    for element in elements:
        # Map elements based on their position
        row = (element["number"] - 1) // columns
        col = element["position"]
        table[row][col] = element

    # Generate HTML
    html = [
        "<html>",
        "<head>",
        "<title>Periodic Table</title>",
        "</head>",
        "<body>",
        "<table style=\"border-collapse: collapse; text-align: center;\">"
    ]

    for row in table:
        html.append("<tr>")
        for cell in row:
            if cell:
                html.append(f"<td style=\"border: 1px solid black; padding: 10px;\">"
                            f"<h4>{cell['name']}</h4>"
                            f"<ul>"
                            f"<li>No {cell['number']}</li>"
                            f"<li>{cell['symbol']}</li>"
                            f"<li>{cell['mass']}</li>"
                            f"</ul>"
                            f"</td>")
            else:
                html.append("<td></td>")
        html.append("</tr>")

    html.extend([
        "</table>",
        "</body>",
        "</html>"
    ])

    return "\n".join(html)

def main():
    # Parse the periodic table file
    try:
        elements = parse_periodic_table(PERIODIC_TABLE_FILE)
    except FileNotFoundError:
        print(f"Error: File {PERIODIC_TABLE_FILE} not found.")
        sys.exit(1)

    # Generate the HTML
    html_content = generate_html(elements)

    # Write the HTML to the output file
    with open(OUTPUT_HTML_FILE, "w") as file:
        file.write(html_content)

    print(f"HTML file generated: {OUTPUT_HTML_FILE}")

if __name__ == "__main__":
    main()
