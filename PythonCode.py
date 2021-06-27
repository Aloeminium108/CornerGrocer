# Alice Parrish
# 6/18/2021

import string

# Create file object, dictionary of item frequencies, 
# and write frequency.dat file
# Returns 0 if process is successful. Returns 1 otherwise.
def Initialize(fileName):
    # Use global itemFrequency variable instead of creating a local field
    itemFrequency = {}

    # Create file object to read input.txt
    try:
        inputFile = open(fileName, 'r')
    except IOError:
        print("ERROR: {} not found".format(fileName))
        return 1

    # Iterate through every line in the file and update itemFrequency
    for item in inputFile.readlines():
        # For each item, if it is in itemFrequency, add 1 to that item's value
        # If it is not in itemFrequency, 
        if item in itemFrequency:
            itemFrequency[item] += 1
        else:
            itemFrequency[item] = 1

    # Create frequency.dat file to write to
    try:
        outputFile = open('frequency.dat', 'w')
    except IOError:
        print("ERROR: Could not write to frequency.dat")
        return 1

    # Write each item and its frequency to the file separated by an = sign
    loopCount = 1
    for item in itemFrequency.keys():
        outputFile.write(item.strip())
        outputFile.write(' - ') # Write a delimiter between the item name and frequency
        outputFile.write(str(itemFrequency[item]))
        loopCount += 1
        # write a newline character on each line except the last
        if (loopCount <= len(itemFrequency.keys())):
            outputFile.write('\n')

    # Close files when done
    inputFile.close()
    outputFile.close()
    return 0

# Print the overall frequency of each item
def OverallFrequency():
    # Open frequency.dat to read from
    try:
        file = open('frequency.dat', 'r')
    except IOError:
        print("ERROR: frequency.dat not found")
        return

    #Print contents of frequency.dat
    for line in file.readlines():
        print(line, end='')

    # Close frequency.dat
    file.close
    
# Return the frequency of a single item.
def IndividualFrequency(itemName):
    # Open frequency.dat to read from
    try:
        file = open('frequency.dat', 'r')
    except IOError:
        print("ERROR: frequency.dat not found")
        return

    frequency = 0

    # Search frequency.dat for item name
    for line in file.readlines():
        if(line.lower().startswith(itemName.lower())):
            frequency = int(line.split(' - ')[1])
            break

    # Close frequency.dat
    file.close()
    return frequency
