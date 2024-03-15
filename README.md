# Huffman Compression - Data Structures Course Homework #8

This repository contains the implementation of a compression and decompression tool developed as part of the Data Structures course at National Sun Yat-sen University (NSYSU), Assignment #8. The core algorithm used in this project is the Huffman algorithm, a method for lossless data compression.

## Project Overview

The goal of this project is to demonstrate the practical application of the Huffman algorithm in file compression and decompression. By achieving a reduction in the required amount of storage or transmission, data compression becomes a vital tool in handling and transferring data efficiently.

### Features

- **Compression**: Reduces the file size by applying the Huffman coding algorithm, storing the encoding table in the header of the compressed file.
- **Decompression**: Retrieves the original data from the compressed file using the encoding table stored in its header.
- **Efficiency Calculation**: Computes the compression ratio and includes it in the header of the compressed file along with the sizes of the original and compressed files.
- **CLI Interface**: Offers command-line options to specify input and output files for both compression and decompression operations.

### Usage

To compress a file:

`huffman -c -i <inputfile> -o <outputfile>`

To decompress a file:

`huffman -u -i <inputfile> -o <outputfile>`


### Huffman Encoding Specification

The implementation follows these rules to ensure the consistency and efficiency of the Huffman codes generated:

1. **Tree Construction**: In the Huffman tree, the left subtree is labeled with 0, and the right subtree with 1.
2. **Node Merging**: When merging two nodes, the node of less lexical order is set as the left son. The lexical order is determined by the least symbols in the two nodes.
3. **Handling Ties**: If multiple nodes have the same frequency, merge the two nodes with the least and the second least symbols in lexical order.

### Contributions and Feedback

Feel free to fork this repository, submit pull requests, or send us feedback on how to improve the software.

### Acknowledgments

- This project is part of the coursework for the Data Structures course at NSYSU.
- Thanks to the course instructors and teaching assistants for their guidance and support.


