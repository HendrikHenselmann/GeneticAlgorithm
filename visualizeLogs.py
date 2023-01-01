import os
import numpy as np
import matplotlib.pyplot as plt

# Cut filename extension and file number and split camel case words
def convertFilenameToTitle (filename):

    # Cut file extension
    withoutExtension = filename.split (".")[0]

    # Skip file number
    firstCharIndex = 0
    while (withoutExtension[firstCharIndex].isnumeric()):            
        firstCharIndex += 1

    # Split words
    finalName = withoutExtension[firstCharIndex].upper ()
    for i in range (firstCharIndex+1, len (withoutExtension)):
        if withoutExtension[i].isupper ():
            finalName += " "
        finalName += withoutExtension[i]

    return finalName

def main ():

    # Get all log filenames
    logFiles = []
    for filename in os.listdir ("./logs/"):
        logFiles.append (filename)
    
    # For every file
    for filename in sorted(logFiles):

        # Read data
        with open ("./logs/" + filename, "r") as f:
            lines = f.readlines ()
            data = [float (line) for line in lines]
        
        # Visualize using matplotlib
        plt.plot (np.arange (len (data)), data)
        plt.title (convertFilenameToTitle (filename))
        plt.xlabel ("generation")
        plt.ylabel ("fitness")
        plt.show ()

if __name__ == '__main__':
    main ()
