from cs50 import get_string


def count_letters(text):
    letter_count = 0
    for char in text:
        if char.isalpha():
            letter_count += 1
    return float(letter_count)


def count_words(text):
    words_count = 0
    words = text.split()
    for word in words:
        words_count += 1
    return float(words_count)


def count_sentences(text):
    sentences_count = 0
    for char in text:
        if char in [".", "!", "?"]:
            sentences_count += 1
    return float(sentences_count)


def main():
    text = get_string("Text: ")

    letter_count = count_letters(text)
    words_count = count_words(text)
    sentences_count = count_sentences(text)

    L = (100 / words_count) * letter_count
    S = (100 / words_count) * sentences_count

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {int(index)}")


main()
