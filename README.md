# CornerGrocer
Program description:
This program takes an input file (input.txt) containing each item purchased throughout the day as a single line of text. 
An output file (frequency.dat) is produced, containing each item purchased and the number of times it has been purchased, separated by " - "
This program can print the contents of frequency.dat, the frequency of a single item, or a histogram of the data

Things done well:
I believe the histogram looks nice, and that the program works in an efficient manner.

Things that need improvement:
With that said, there are many areas that could be improved.
Although this program is small enough for the menu and histogram display functions to fit in the source file, readability and maintainability would be greatly improved by putting those functions in a separate file.
The file names themselves are not nearly descriptive enough.
The menu and histogram functions are limited in their use. Adding more parameters to adjust the size and colors would benefit the programs' capabilities.

Challenges:
Incorporating C++ and Python can be very finicky. 
Nearly every problem I encountered was related to the interoperation of the two languages
These problems are not easy to search for, and so I had to rely on trial and error to solve them.

Skills Learned:
I learned a lot about the interoperation of C++ and Python, which is a transferable skill to any development jobs where multiple languages will be used together.

Maintainability and adaptability:
Although the histogram function doesn't have any parameters to adjust its size, it does use local variables to control the width of its columns. 
Maintainability and adaptability are admittedly weak in this program overall. I tried to make sure everything was readable, but actually modifying the code is not as easy as it should be.
