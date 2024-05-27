#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void displayResults(int lines, int words, int characters);

int main() {
    char filename[100];
    FILE *file;
    int characters = 0, words = 0, lines = 0;
    int ch;
    int in_word = 0;

    printf("Enter the filename to open: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if ((char)ch == '\n') {
            lines++;
        }

        if (isspace((char)ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(file);

    displayResults(lines, words, characters);

    return 0;
}

void displayResults(int lines, int words, int characters) {
    printf("\nTextual Data Structure Analysis:\n");
    printf("+----------------+-------+\n");
    printf("|     Element    | Count |\n");
    printf("+----------------+-------+\n");
    printf("| Lines          | %5d |\n", lines);
    printf("| Words          | %5d |\n", words);
    printf("| Characters     | %5d |\n", characters);
    printf("+----------------+-------+\n");
}