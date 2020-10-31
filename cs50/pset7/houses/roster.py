import cs50
import sys
# Connect to the database
db = cs50.SQL("sqlite:///students.db")
# Parse Input
if len(sys.argv) != 2:
    sys.exit("missing command-line argument")
# Assign the return value of the SQL query to a variable
houseStudents = db.execute("SELECT first,middle,last,birth FROM students WHERE house=? ORDER BY last ASC, first ASC", sys.argv[1])
# Loop over each row in the returned data
for i in houseStudents:
    # Convert the dict into a list of only the values
    i = list(dict.values(i))
    # Check if middle name doesn't exist
    if i[1] == None:
        # Output 'first' 'last', born 'birth'
        output = i[0] + " " + i[2] + ", " + "born " + str(i[3])
    else:
        # Output 'first' 'middle' 'last', born 'birth'
        output = i[0] + " " + str(i[1]) + " " + i[2] + ", " + "born " + str(i[3])
    # Print the result
    print(output)
