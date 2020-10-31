import csv
import cs50
import sys
# If no database file already - create one
open("students.db", "w").close()
# connect to the database and create a new table with appropriate column names
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# Parse input
if len(sys.argv) != 2:
    sys.exit("missing command-line argument")
# Open the users input csv file
with open(sys.argv[1], "r") as csv_file:
    # Create a reader to read rows
    reader = csv.DictReader(csv_file)
    for row in reader:
        # Assign each columns values to a variable
        name = row["name"]
        house = row["house"]
        birth = row["birth"]
        # Split the name into first / middle / last
        name = name.split(" ")
        for i in range(len(name)):
            # Assign the results of splitting the full name into each sub name category
            if len(name) == 3:
                first = name[0]
                middle = name[1]
                last = name[2]
            # If no middle name just get first and last - and assign middle to be 'None'
            elif len(name) == 2:
                first = name[0]
                middle = None
                last = name[1]
        # Insert each row into the students table
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            first, middle, last, house, birth)