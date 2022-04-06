#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//this is a preliminary implementation of a finite_automata for use in more complicated regex
struct finite_automata_state {
    struct finite_automata_state* next_state;
    char* storage;
    int storage_Size;
    void (*state_transition)(char* input);
};

int match(char* text, int text_size, char* pattern, int pattern_size) {
    //Go letter by letter and see if it matches
    int iterator = 0;
    for (int i = 0; i < pattern_size; i++){
        if (pattern[i] != text[iterator] && pattern[i] != '.'){
            return 0;
        } 
        iterator++;
    }
    return 1;    
}

int main(){

    printf("Hello world! (regex edition)\n");
    char *test1 = (char*) malloc(12*sizeof(char));
    strcpy(test1, "testingonly");
    char *test2 = (char*) malloc(12*sizeof(char));
    strcpy(test2, "testin.only");
    printf("%d\n",match(test1, 12, test2, 12));
    free(test1);
    free(test2);
}

