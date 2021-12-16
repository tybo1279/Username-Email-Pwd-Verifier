/******************************************************************************
 * @file: Verifier.c
 * @creator: Tyler Krill
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"
/******************************************************************************
 * Helper functions
 *****************************************************************************/

int isChar(int n) {
    if((n <= 90 && n >= 65) || (n <= 122 && n >= 97)) {
      return 1;
    }
    else {
      return 0;
    }
}
int isDigit(int n) {
    if((n <= 57 && n >= 48)) {
      return 1;
    }
    else {
      return 0;
    }
}
int strLength(char s[]) {
    int n = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
       ++n;
    }
    return n;
}
int strCmp(char s1[], char s2[]) {
    if (strLength(s1) != strLength(s2)) {
       return 1;
    }
    int count = 0;
    for (int i = 0; s1[i] != '\0'; ++i) {
       if (s1[i] == s2[i]) {
          count = count + 1;
       }
    }
    if (count == strLength(s1)) {
      return 0;
    }
    else {
      return 1;
    }
    return 1;
}

/*
 * Username verification function
 */
int Verify_Username(char user[], size_t len) {

    if (!(isChar(user[0]))) {
       printf("Username must begin with a letter\n");
       return 0;
    }
    int length = strLength(user);
    if (!(length <= 32)) {
       printf("Maximum of 32 characters\n");
       return 0;
    }
    for (int i = 0; i < length; ++i) {
       if (!(isChar(user[i])) && !(isDigit(user[i])) && user[i] != '_' ) {
          printf("Invalid character in username\n");
          return 0;
       }
   }

    printf("Username formatting correct\n");
    return 1;
}
/*
 * Email verification function
 */
int Verify_Email(char email[], size_t len) {

    int mark = -1;

    if (!(isChar(email[0]))) {
       printf("Email name must begin with a letter\n");
       return 0;
    }
    for (int i = 0; i < strLength(email); ++i) {
       if (email[i] == '@') {
          mark = i;
          if (i == 0) {
             printf("Email name missing\n");
             return 0;
          }
          break;
       }
       if (!isChar(email[i]) && !isDigit(email[i]) && email[i] != '.') {
          printf("Invalid character in email name\n");
          return 0;
       }
    }
    if (mark == -1) {
       printf("Missing @\n");
       return 0;
    }
    if (mark > 32) {
       printf("Email name must have fewer than 32 characters\n");
       return 0;
    }

    for (int j = mark + 1; j < strLength(email); ++j) {
       if (!isChar(email[j]) && !isDigit(email[j]) && email[j] != '.') {
          printf("Invalid character in domain\n");
          return 0;
       }
       if (email[j] == '.') {
          if (j == mark + 1) {
            printf("Domain missing\n");
            return 0;
          }
          if (!isChar(email[j+1])) {
            printf("Domain or subdomain must begin with a letter\n");
            return 0;
          }
       }
       else if (!isChar(email[j]) && email[j-1] == '@') {
          printf("Domain or subdomain must begin with a letter\n");
          return 0;
       }
    }
    char str[] = {email[strLength(email)-3], email[strLength(email)-2], email[strLength(email)-1]};
    if (strCmp(str, "edu")!=0 && strCmp(str, "com")!=0 && strCmp(str, "net")!=0) {
        printf("Top level domain must be .edu, .com, or .net\n");
        return 0;
    }
    int dom_len = (strLength(email) - (mark + 1) - 4);
    if (!(dom_len <= 64)) {
       printf("Maximum of 64 characters in domain\n");
       return 0;
    }

    printf("Email formatting is correct\n");
    return 1;
}
/*
 * Password verification function
 */
int Verify_Password(char pwd[], size_t len) {

    if ((strLength(pwd)) < 8) {
        printf("Password must have at least 8 characters\n");
        return 0;
    }
    if ((strLength(pwd)) > 16) {
        printf("Password must have at most 16 characters\n");
        return 0;
    }
    int confirm_Lower = 0;
    int confirm_Upper = 0;
    for (int i = 0; i < strLength(pwd); ++i) {
	if (pwd[i] == ' ') {
          printf("Password cannot contain spaces\n");
          return 0;
	}
        if ((int)pwd[i] <= 122 && (int)pwd[i] >= 97) {
          confirm_Lower = 1;
        }
        if ((int)pwd[i] <= 90 && (int)pwd[i] >= 65) {
          confirm_Upper = 1;
        }
    }
    if (confirm_Upper == 0) {
       printf("Password must contain at least one upper case letter\n");
       return 0;
    }
    if (confirm_Lower == 0) {
       printf("Password must contain at least one lower case letter\n");
       return 0;
    }

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    if (strCmp(pwd1, pwd2) != 0) {
       printf("Passwords do not match\n");
       return 0;
    }

    printf("Passwords match\n");
    return 1;
}

/*
 * Prompts user with an input and reads response from stdin
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    for (int i = 0; i < strLength(data); ++i) {
        if (data[i] == '\n') {
           data[i] = '\0';
        }
    }
    return;
}
