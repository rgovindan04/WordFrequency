**Overview**
This project implements a Dictionary Abstract Data Type (ADT) using Red-Black Trees for efficient data storage and retrieval. The following components are included in the project:

Dictionary.h and Dictionary.cpp: These files define and implement the Dictionary ADT using a Red-Black Tree as the underlying data structure. This ensures balanced performance for common dictionary operations such as insertion, deletion, and lookup.

DictionaryTest.cpp: Contains comprehensive unit tests for the Dictionary ADT to verify its correctness and robustness. These tests validate the ADT's functionality under various scenarios and edge cases.

Order.cpp: A client program originally developed in a previous assignment (pa7) that interacts with the Dictionary ADT.

WordFrequency.cpp: The top-level client application for this assignment. It processes a given text file by:
- Reading each line from the file.
- Parsing individual words from each line.
- Converting each word to lowercase to ensure uniformity.
- Inserting each word as a key into the Dictionary. The corresponding value represents the word's frequency count.

**Features**
- Red-Black Tree Implementation: The Dictionary ADT is implemented using a Red-Black Tree to ensure efficient operations with guaranteed logarithmic time complexity for insertion, deletion, and search.
- Unit Testing: The DictionaryTest executable provides a thorough validation of the ADT, ensuring reliability and correctness.
Word Frequency Analysis: The WordFrequency client processes text files to compute the frequency of each unique word, leveraging the capabilities of the Dictionary ADT.
- Customizable Client Programs: The Order client demonstrates a reusable and customizable example of integrating the Dictionary ADT.

**Usage Details**
- The WordFrequency program processes text files line by line and parses words based on delimiters.
- Each word is converted to lowercase to ensure case-insensitive frequency counting.
- Words are inserted into the Dictionary ADT as keys, with their corresponding frequencies maintained as values.

