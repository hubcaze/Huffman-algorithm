# Huffman Algorithm

This is a little implementation of the Huffman code, I did it for fun so the code is not very optimized and it doesn't work for image files yet.

# Run

You can try running the code with a text file

```echo "this is the test" >> test.txt```
Then compile all the files using the command "make" and run the new binary file created:
       ```make```
       ```./exec c test.txt```
A file called compressed.bin is created, to decompress this file, use:
       ```./exec d compressed.bin```

[To learn more about the Huffman code](https://fr.wikipedia.org/wiki/Codage_de_Huffman)
