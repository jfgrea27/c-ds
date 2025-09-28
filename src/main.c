#include <stdlib.h>
#include <unistd.h>

int count_action(int action, FILE *file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        switch (action) {
            case WORD_COUNT
            :
                if (isspace(c)) {
                    count++;
                }
                break;
            case LINE_COUNT:
                if (c == '\n') {
                    count++;
                }
                break;
            default:
                return -1;
        }
    }
    // count the last word/line
    count++;

    return count;
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        void *ptr = malloc(sizeof(int));
    }

    sleep(); // Give leaks time to check


    return 0;
}