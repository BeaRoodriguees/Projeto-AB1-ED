#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define DEBUG if(0)

int isUpper(char c){
    if (c >= 65 && c <= 90) return 1;
    else return 0;
}

int isLower(char c){
    if (c >= 97 && c <= 122) return 1;
    else return 0;
}

int isSpace(char c){
    if (c == ' ' || c == '\t') return 1;
    else return 0;
}


/*
 * Check if the name is valid.
 *
 * @param name strig with the name
 * @return 0 - invalid | 1 - valid
 *
 */
int checkName(char name[]){
    int length = strlen(name) - 1; 
    
    if (length < 2) //Short Name
        return 0;

    if (!isUpper(name[0])){
        DEBUG printf(" %c ", name[0]);
        return 0;
    }

    for (int i = 1; i < length; i++){
        if (isSpace(name[i])){            
            if(!isUpper(name[i+1])){
                DEBUG printf("\n%c\n", name[i+1]);
                return 0;
            }
            i++;
        }
        else if (!isLower(name[i])){
            DEBUG printf("\n%c\n", name[i]);
            return 0;
        }        
    }

    return 1;
}