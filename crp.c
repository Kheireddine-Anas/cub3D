#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char secret_message[256] = "Hello Members the code of new Date are JK:DD:jn :1114: be there";
    const char *password = "ma9la1111";
    printf("ly!\n");
    printf(">>:<<");
    char input_password[256];
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0;
    if (strcmp(input_password, password) == 0) {
        printf(": %s\n", secret_message);
    } else {
        printf("Incorrect password.\n");
    }
    return 0;
}
