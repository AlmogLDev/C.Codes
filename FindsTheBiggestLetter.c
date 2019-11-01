

#include <stdio.h>

int main() {
    
    char Letter=0;
    int BigestLetter = 0;
    
    printf("Please enter letters:\n");
    scanf("%c", &Letter);
    
    if (Letter<='Z' && Letter>='A' && Letter-'A'>BigestLetter) {
        BigestLetter = Letter - 'A';
    }
    if (Letter<='z' && Letter>='a' && Letter-'a'>BigestLetter) {
        BigestLetter = Letter - 'a';
    }
    
    while (Letter != '#') {
        scanf("%c", &Letter);
        if (Letter<='Z' && Letter>='A' && Letter-'A'>BigestLetter) {
            BigestLetter = Letter - 'A';
        }
        if (Letter<='z' && Letter>='a' && Letter-'a'>BigestLetter) {
            BigestLetter = Letter - 'a';
        }
    }
    
    printf("%c\n", BigestLetter + 'a');

    return 0;
}
