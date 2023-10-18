# Impledge-Technlogy-Assignement
The provided C++ program is designed to find the longest and second longest compound words within a list of words. The program utilizes a Trie data structure for efficient word storage and searching.

Here's a step-by-step explanation of the code's approach:

Trie Data Structure:

The core data structure used in this code is the Trie. A Trie is a tree-like structure where each node represents a character in a word. The path from the root to a node forms a word, and each node has links to its child nodes, corresponding to the next character in the word. Trie is efficient for searching for words and their substrings.
Word Insertion:

The code initializes an empty Trie with a root node containing a space character. It then reads words from the input file and inserts them into the Trie. The insertion process involves traversing the Trie while adding nodes for each character in the word. The last node of a word is marked as a valid word endpoint.
Finding Suffixes:

After inserting a word into the Trie, the code finds all the possible suffixes of that word. Suffixes are portions of the word that come after the current character. The getSuffixesStartIndices function is used to find the starting indices of all such suffixes in the original word.
Compound Word Detection:

The code maintains a queue of word pairs (pair of the original word and its suffix) to be processed. It iteratively dequeues pairs and examines the suffix for compound word possibilities.
If a valid compound word is found, it is compared with the longest and second longest compound words found so far. If it is longer than the current longest, it becomes the new longest, and the previous longest becomes the second longest.
The compound words are also stored in an unordered set to avoid counting them multiple times.
Performance Measurement:

The code uses the <chrono> library to measure the time taken for the entire process, from reading the input file to finding compound words. This elapsed time is displayed as part of the program's output.
