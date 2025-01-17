import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # TODO: Read database file into a variable
    sequences = []
    dna_file = {}
    with open(sys.argv[1]) as csv_file:
        for index, row in enumerate(csv_file):
            if index == 0:
                sequences = [sequence for sequence in row.strip().split(",")][1:]
            else:
                name = row.strip().split(",")
                dna_file[name[0]] = name[1:]

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as txt_file:
        seq_file = txt_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    result = [longest_match(seq_file, subsequence) for subsequence in sequences]

    # TODO: Check database for matching profiles
    for s in dna_file:
        count = 0
        for j in range(len(dna_file[s])):
            if result[j] == int(dna_file[s][j]):
                count += 1
        if count == len(sequences):
            print(s)
            exit(0)

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
