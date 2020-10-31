from cs50 import get_string
# main function
def main():
    # get user input
    inputText = get_string("Text: ")
    # calculate length
    length = len(inputText) - 1
    # initialize the count variables
    letterCount = wordCount = sentenceCount = 0
    # loop over each letter in the text
    for i in range(len(inputText)):
        # check if the loop is at the end of the input and increments word and sentence count
        if i == length and (endOfSentence(inputText[i-1]) == False):
            wordCount += 1
            sentenceCount += 1
        # counting each letter
        elif inputText[i].isalpha():
            letterCount += 1
        # counting each word
        elif endOfWord(inputText[i]):
            wordCount += 1
        # counting each sentence
        elif endOfSentence(inputText[i]):
            sentenceCount += 1
    # calculate the grade level and output it
    calculate(letterCount, wordCount, sentenceCount)

# separate function to determine if the argument (letter) is one of the three end sentence characters
def endOfSentence (letter):
    if ord(letter) == 33 or ord(letter) == 46 or ord(letter) == 63:
        return True
    return False

# separate function to determine if the argument (letter) is a space
def endOfWord (letter):
    if letter.isspace():
        return True
    return False

# separate function to calculate the grade level and output the result
def calculate (letter, word, sentence):
    # Coleman-Liau formula
    index = 0.0588 * ((100 / word) * letter) - 0.296 * ((100 / word) * sentence) - 15.8
    # round the Coleman-Liau formula result
    result = round(index)
    # if below 0
    if index <= 0:
        print("Before Grade 1")
        return 1
    # if above 16
    elif index >= 16:
        print("Grade 16+")
        return 1
    # else print the grade level stored in result
    print(f"Grade {result}")
    return 1
# main function call
main()
