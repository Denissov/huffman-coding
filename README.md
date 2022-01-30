# huffman-coding
This program decomposes text files using Huffman coding algorithm. It also performs recovery of the decomposed text file.

## priority_queue_min.cpp & main.cpp
First of these files contains a realization of Priority Queue class, which is used in Huffman coding algorythm. Second of these files is intended for one of complementary tasks: turnng symbols with given frequencies into codes through building corresponding Huffman tree. Use **makefile** for running these two. There is obe text file required - it must contain the size of two arrays, and arrays of symbols and their frequencies themselves.

## symbol_count.cpp
This file contains the realization of Huffman coding algorythm itself. It requires three text files, that have to be put in the following order: **input.txt** - file, containing the text that has to be decomposed, **code.txt** - file, which contains the result of encryption of input.txt file after Huffman coding algorythm worked, **decode.txt** - file, which contains the result of recovery of the code from decode.txt file.

**P.S.** *All the comments inside all of the files listed above are in Russian.*
