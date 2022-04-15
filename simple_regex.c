#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//Descripttion of states
/*
1. State 1 - alphanumeric
2. State 2 - open bracket
3. State 2a - alpha numeric
4. State 2b - close bracket
5. State 3 - Special character
6. State 3.1a - *, repeat last character until no match
7. State 4 - Done
8. State 5 - Error
9. State 6 - alpha special
*/

//this is a preliminary implementation of a finite_automata for use in more complicated regex
struct finite_automata_state {
    int state;
    struct finite_automata_state* next_state;
    char* storage;
    int storage_size;
    void (*state_transition)(char* input);
};

int state_transition(int state, char input){
    switch(state){
        case 1:
            if (input == '*'){
                return 6;
            } else if (is_special_character(input)){
                return 9;
            } else if (input == '[') {
                return 2;
            } else if (input >= 30 || input <= 80) {
                return 1;
            } else {
                return 5;
            }
        case 2:
            if (input == '*'){
                return 3;
            } else if (is_special_character(input)){
                return 5;
            } else if (input == '[') {
                return 5;
            } else if (input >= 30 || input <= 80) {
                return 3;
            } else {
                return 5;
            }
        case 3:
            if (input == '*'){
                return 5;
            } else if (is_special_character(input)){
                return 5;
            } else if (input == ']') {
                return 4;
            } else if (input >= 30 || input <= 80) {
                return 3;
            } else {
                return 5;
            }
        case 4:
            if (input == '*'){
                return 6;
            } else if (is_special_character(input)){
                return 9;
            } else if (input == '[') {
                return 5;
            } else if (input >= 30 || input <= 80) {
                return 5;
            } else {
                return 5;
            }
        case 5:
        case 6:
        case 7:
        case 8:
    }
}

int is_special_character(char a) {
    switch(a){
        case '\\':
            return 1;
        case '+':
            return 2;
        case '*':
            return 3;
        case '^':
            return 4;
    }
    return 0;
}

int match(char* text, int text_size, char* pattern, int pattern_size) {
    //Go letter by letter and see if it matches
    int iterator = 0;
    int repetition_mode = 0;
    for (int i = 0; i < pattern_size; i++){
        printf("%d %d\n", i, iterator);
        if (pattern[i] == '*' && i > 0) {
            if (pattern[i-1] != '\\') {
                repetition_mode = 1;
            }
        }
        if (pattern[i] == '+' && i > 0) {
            if (pattern[i-1] != '\\') {
                if (pattern[i-1] != text[iterator] && pattern[i-1] != '.'){
                    return 0;
                }
                repetition_mode = 1;
            }
        }
        if (repetition_mode != 1) {
            if (pattern[i] != text[iterator] && pattern[i] != '.'){
                return 0;
            }
            iterator++;
        } else {
            while (pattern[i-1] == text[iterator]){
                printf("%c", pattern[i-1]);
                printf("%c", pattern[i]);
                iterator++;
            }
            repetition_mode = 0;
        }
        
    }
    return 1;    
}

int main(){

    printf("Hello world! (regex edition)\n");
    char *test1 = (char*) malloc(12*sizeof(char));
    strcpy(test1, "testingonly");
    char *test2 = (char*) malloc(12*sizeof(char));
    strcpy(test2, "testi*sonly");
    printf("%d\n",match(test1, 12, test2, 12));
    free(test1);
    free(test2);
}

