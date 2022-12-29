import os
import numpy as np
import matplotlib.pyplot as plt

# Cut filename extension and split camel case words
def convertFilenameToTitle (filename):

    # Cut file extension
    withoutExtension = filename.split (".")[0]

    # Split words
    finalName = withoutExtension[0].upper ()
    for i in range (1, len (withoutExtension)):
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
    for filename in logFiles:

        # Read data
        with open ("./logs/" + filename, "r") as f:
            lines = f.readlines ()
            data = [float (line) for line in lines]
        
        # Visualize using matplotlib
        plt.plot (np.arange (len (data)), data)
        plt.title (convertFilenameToTitle (filename))
        plt.show ()

if __name__ == '__main__':
    main ()
