import csv
import sys

# parse input
if len(sys.argv) != 3:
    sys.exit("missing command-line argument")

def main():
    # initialize my lists and an empty string
    strProfile, nameList, strSearch = [], [], []

    # Open txt file and store it in sequence variable
    sequenceFile = open(sys.argv[2], "r")
    sequence = sequenceFile.read()
    sequenceFile.close()

    # Open CSV file
    with open(sys.argv[1], "r") as database:
        reader = csv.reader(database)
        # grab the headings from the first line of the csv and store them
        csvHeadings = next(reader)
        strTypes = csvHeadings
        # read each line into the csv
        for line in reader:
            # store the names in a list / which will later be used to identify the str profile match
            nameList.append(line[0])
            # initialize a temporary string variable to add each str type and their respective sequence counts for each person
            tempString = ''
            # loop through each str type and add ^ information
            for v in range(1, len(strTypes), 1):
                tempString += (strTypes[v] + line[v])
            # for each person - add their strcount - in a sequence 'str##str##str##' to be used later to identify a match
            strProfile.append(tempString)
    database.close()

    # removing the 'name' column in the first row (headers)
    del strTypes[0]

    # assigning the highest str sequence for each STR type to a variable which will be compared with each persons profile
    strCountString = calculateHighestStrSequence(strTypes, sequence)
    # compare the sequence's count with each person - and display that persons name if a match is found. if not return no match
    displayMatch(strProfile, strCountString, nameList)

# function for getting the highest consecutive STR sequence inside of the sequence.txt file
def calculateHighestStrSequence (strTypes, sequence):
    # initialize a list to store the sequence inside of for each STR
    sequenceProfile = []
    # loop through each STR type
    for x in range(len(strTypes)):
        # initialize variables for while loop + storing current and overall highest counts
        index, highestSequence, currentHighest = 0, 0, 0
        # calculate the length of the current STR
        strLength = len(strTypes[x])
        # loop through the entire text file
        while index < len(sequence) - strLength:
            # if a match is found
            if sequence[index : index + strLength] == strTypes[x]:
                # increment the count and index
                currentHighest += 1
                index += strLength
                continue
            else:
                # if no match found - check if the current highest sequence count is higher than the overall
                if currentHighest >= highestSequence:
                    # assign the overall count
                    highestSequence = currentHighest
                # and reset the current counter
                currentHighest = 0
                # increment the index
                index += 1
        # add each str's sequence count to a list - then create a string from that list for comparison
        sequenceProfile.append(strTypes[x] + str(highestSequence))
        strCountString = ''.join(sequenceProfile)
    # return the string
    return strCountString
# function to print out the person who's profile matches the sample
def displayMatch(profile, string, nameList):
        # for each persons str profile
        for p in range(len(profile)):
            # if a match is found
            if profile[p] == string:
                # print their name using the current index which matches up with our name list
                print(nameList[p])
                break
            # else if no match
            elif p >= len(profile) - 1:
                print("No match.")

main()