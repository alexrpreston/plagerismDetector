# Plagerism Detector

This project uses a token based algorithm for the trivial implementation and a Sequence based algorithm for the robust implementation. The project can be run with any name or number of text files in the `database` folder so long as they are .txt file. The comparison file in the target directory needs to be named `target.txt`.

# Trivial

The trivial version uses the Jaccard index which just tokenizes all the words and then divides the Intersection by the Union. You can read more [here](https://en.wikipedia.org/wiki/Jaccard_index).

## Robust

The robust version uses the Ratcliff-Obershelp similarity. This algorithm recursivly finds the matching Longest Common Substring (LCS) and then divides the total LSC by the total characters. You can read more [here](https://en.wikipedia.org/wiki/Gestalt_Pattern_Matching).

