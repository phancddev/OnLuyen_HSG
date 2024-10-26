import pandas as pd
import glob
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas

# GP Conversion table based on the image
gp_conversion = {
    1: 500, 2: 485, 3: 471, 4: 458, 5: 446, 6: 434, 7: 423, 8: 412, 9: 401, 10: 391, 
    11: 381, 12: 371, 13: 361, 14: 352, 15: 343, 16: 334, 17: 325, 18: 316, 19: 308, 20: 300,
    21: 292, 22: 284, 23: 276, 24: 268, 25: 261, 26: 254, 27: 247, 28: 240, 29: 233, 30: 226,
    31: 219, 32: 213, 33: 207, 34: 201, 35: 195, 36: 189, 37: 183, 38: 177, 39: 171, 40: 166,
    41: 161, 42: 156, 43: 151, 44: 146, 45: 141, 46: 136, 47: 131, 48: 126, 49: 122, 50: 118,
    51: 114, 52: 110, 53: 106, 54: 102, 55: 98, 56: 94, 57: 90, 58: 86, 59: 82, 60: 79,
    61: 76, 62: 73, 63: 70, 64: 67, 65: 64, 66: 61, 67: 58, 68: 55, 69: 52, 70: 49,
    71: 46, 72: 43, 73: 41, 74: 39, 75: 37, 76: 35, 77: 33, 78: 31, 79: 29, 80: 27,
    81: 25, 82: 23, 83: 21, 84: 19, 85: 17, 86: 15, 87: 14, 88: 13, 89: 12, 90: 11,
    91: 10, 92: 9, 93: 8, 94: 7, 95: 6, 96: 5, 97: 4, 98: 3, 99: 2, 100: 1
}

# List all CSV files matching the pattern 'week*.csv'
csv_files = glob.glob('week*.csv')

# Dictionary to hold cumulative GP points for each participant
gp_points = {}

# Read each CSV file and accumulate GP points
for file in csv_files:
    df = pd.read_csv(file)
    
    # Iterate over the rows (rankings) in the CSV file
    for index, row in df.iterrows():
        username = row['Username']
        rank = index + 1  # Rank is the row number starting from 1
        
        # Get GP points for this rank
        points = gp_conversion.get(rank, 0)
        
        # Add to cumulative GP points
        if username not in gp_points:
            gp_points[username] = {'GP_Points': 0, 'Fullname': row['Fullname'], 'School': row['School']}
        
        gp_points[username]['GP_Points'] += points

# Convert the dictionary to a DataFrame
gp_df = pd.DataFrame.from_dict(gp_points, orient='index').reset_index()
gp_df = gp_df.rename(columns={'index': 'Username'})

# Sort by GP points in descending order
gp_df = gp_df.sort_values(by='GP_Points', ascending=False)

# Create PDF
pdf_filename = "gpPointsLQDOJ2024.pdf"
c = canvas.Canvas(pdf_filename, pagesize=letter)

# Set up font and page margins
c.setFont("Helvetica", 12)
x_offset = 50
y_offset = 750
line_height = 20

# Draw header
c.drawString(x_offset, y_offset, "Username")
c.drawString(x_offset + 150, y_offset, "Fullname")
c.drawString(x_offset + 350, y_offset, "School")
c.drawString(x_offset + 500, y_offset, "Total GP Points")
y_offset -= line_height

# Draw each row
for index, row in gp_df.iterrows():
    c.drawString(x_offset, y_offset, row['Username'])
    c.drawString(x_offset + 150, y_offset, row['Fullname'])
    c.drawString(x_offset + 350, y_offset, row['School'])
    c.drawString(x_offset + 500, y_offset, str(row['GP_Points']))
    y_offset -= line_height
    
    # Start a new page if content overflows
    if y_offset < 50:
        c.showPage()
        c.setFont("Helvetica", 12)
        y_offset = 750

# Save the PDF
c.save()

print(f"PDF file '{pdf_filename}' created successfully.")