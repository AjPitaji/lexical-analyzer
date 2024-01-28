#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#define MAX_LENGTH 1000

int isKeyword(char *token) {
    char keywords[9][10] = {"int", "char", "float", "double", "if", "else", "while", "for", "return"};
    for (int i = 0; i < 9; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char *token) {
    char operators[12][5] = {"+", "-", "*", "/", "%", "==", "!=", "<=", ">=", "<", ">","="};
    for (int i = 0; i < 11; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void writeToFile(char *filename, char *content) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", content);
    fclose(file);
}

void analyzeTokens(char *program) {
    char *token = strtok(program, " \t\n()+-*/%=<>;{}[],\"");
    while (token != NULL) {
        if (isKeyword(token)) {
            writeToFile("keywords.txt", token);
        } else if (isdigit(token[0])) {
            writeToFile("constants.txt", token);
        } else if (token[0] == '\'' || token[0] == '\"') {
            writeToFile("literals.txt", token);
        } else if (isalpha(token[0]) || token[0] == '_') {
            writeToFile("identifiers.txt", token);
        } else if (strchr("+-*/%=<>;{}[],()\"'", token[0]) != NULL) {
    writeToFile("special_symbols.txt", token);
} else if (isOperator(token)) {
    writeToFile("operators.txt", token);
} else {
            writeToFile("unknown_tokens.txt", token);
        }
        token = strtok(NULL, " \t\n()+-*/%=<>;{}[],\"");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char program[MAX_LENGTH];
    size_t bytesRead = fread(program, 1, MAX_LENGTH, file);
    program[bytesRead] = '\0'; // Null-terminate the string

    fclose(file);

    // Clear existing content in output files
    FILE *outputFiles[] = {
        fopen("keywords.txt", "w"),
        fopen("constants.txt", "w"),
        fopen("literals.txt", "w"),
        fopen("identifiers.txt", "w"),
        fopen("special_symbols.txt", "w"),
        fopen("operators.txt", "w"),
        fopen("unknown_tokens.txt", "w")
    };

    for (int i = 0; i < 7; i++) {
        if (!outputFiles[i]) {
            perror("Error opening output file");
            return 1;
        }
        fclose(outputFiles[i]);
    }

    analyzeTokens(program);

    printf("Token analysis completed. Check the output files for categorized tokens.\n");

    return 0;
}
