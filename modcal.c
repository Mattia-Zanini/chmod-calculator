#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int strToNum(char *permissions);
int chmodStringToNumber(char *value);
int chmodNumberToString(char *value);
char *decimalToBinary(int num);
char *numToStr(char *binary);

int main(int argc, char *argv[])
{
    // EXAMPLE: rwxr-xr-x
    //             OWNER GROUP EVERYONE
    // READ    2^2   1     1      1
    // WRITE   2^1   1     0      0
    // EXECUTE 2^0   1     1      1
    // chmod = 755

    // check if there is the first argument otherwhise the program won't start
    if (argc < 2)
    {
        printf("Missing argument\n");
        exit(1);
    }

    // check if the argument isn't too long
    // string form: rwxr-xr-x length = 9 chars
    // numeric form: 755 length = 3 chars
    if (strlen(argv[1]) > 9)
    {
        printf("Argument too long\n");
        exit(1);
    }

    char onlyLetters = TRUE;
    char onlyNumbers = TRUE;

    // Understand if the user typed the chmod setting in string form
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == FALSE && argv[1][i] != '-')
        {
            onlyLetters = FALSE;
            break;
        }
    }

    if (onlyLetters == FALSE && strlen(argv[1]) < 4)
    {
        // Understand if the user typed the chmod setting in numeric form
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isnumber(argv[1][i]) == FALSE)
            {
                onlyNumbers = FALSE;
                break;
            }
        }
    }
    else if (onlyLetters == FALSE && strlen(argv[1]) > 3)
    {
        printf("Argument too long for the numeric form\n");
        exit(1);
    }

    if (onlyLetters == FALSE && onlyNumbers == FALSE)
    {
        printf("Argument invalid\n");
        exit(1);
    }
    if (onlyLetters == TRUE && strlen(argv[1]) < 9)
    {
        printf("Argument invalid in string form\n");
        exit(1);
    }

    if (onlyLetters == TRUE)
        chmodStringToNumber(argv[1]);
    else
        chmodNumberToString(argv[1]);

    return 0;
}

int strToNum(char *permissions)
{
    int total = 0;
    for (int i = 0; i < strlen(permissions); i++)
    {
        int power = 0;
        if (permissions[i] == '-')
            continue;
        else if (permissions[i] == 'r')
            power = 2;
        else if (permissions[i] == 'w')
            power = 1;
        else if (permissions[i] == 'x')
            power = 0;

        total += pow(2, power);
    }
    return total;
}

char *numToStr(char *binary)
{
    char *result = malloc(4);

    char trattino = '-';
    char r = 'r';
    char w = 'w';
    char x = 'x';

    for (int i = 0; i < strlen(binary); i++)
    {
        int num = binary[i] - '0';
        if (num == 0)
            strncat(result, &trattino, 1);
        else
        {
            if (i == 0)
                strncat(result, &r, 1);
            if (i == 1)
                strncat(result, &w, 1);
            if (i == 2)
                strncat(result, &x, 1);
        }
    }
    return result;
}

int chmodStringToNumber(char *value)
{
    char owner[4];
    char group[4];
    char everyone[4];
    sprintf(owner, "%c%c%c", value[0], value[1], value[2]);
    sprintf(group, "%c%c%c", value[3], value[4], value[5]);
    sprintf(everyone, "%c%c%c", value[6], value[7], value[8]);

    int numOwner = strToNum(owner);
    int numGroup = strToNum(group);
    int numEveryone = strToNum(everyone);

    char *result = malloc(4);
    sprintf(result, "%d%d%d", numOwner, numGroup, numEveryone);

    printf("%s\n", result);
    free(result);

    return 0;
}
int chmodNumberToString(char *value)
{
    // printf("forma numerica: %s\n", value);
    char owner = value[0];
    char group = value[1];
    char everyone = value[2];

    /*
    printf("Owner: %c\n", owner);
    printf("Group: %c\n", group);
    printf("Everyone: %c\n", everyone);
    printf("Valore di owner: %s\n", decimalToBinary(owner - '0'));
    printf("Valore di group: %s\n", decimalToBinary(group - '0'));
    printf("Valore di everyone: %s\n", decimalToBinary(everyone - '0'));
    */

    char *stringOwner = decimalToBinary(owner - '0');
    char *stringGroup = decimalToBinary(group - '0');
    char *stringEveryone = decimalToBinary(everyone - '0');

    // 755 = 111 101 101
    /*
    printf("Owner in string: %s\n", numToStr(stringOwner));
    printf("Group in string: %s\n", numToStr(stringGroup));
    printf("Everyone in string: %s\n", numToStr(stringEveryone));
    */

    char *result = malloc(9);
    sprintf(result, "%s%s%s",
            numToStr(stringOwner), numToStr(stringGroup), numToStr(stringEveryone));

    printf("%s\n", result);
    free(result);

    return 0;
}

char *decimalToBinary(int num)
{
    // Stores binary representation of number.
    int binaryNum[3]; // Assuming 3 bit integer.
    int i = 0;

    for (; num > 0;)
    {
        binaryNum[i++] = num % 2;
        num /= 2;
    }

    char *binary = malloc(4);
    // Printing array in reverse order.
    for (int j = i - 1; j >= 0; j--)
    {
        // printf("%d\n", binaryNum[j]);
        char bit = binaryNum[j] + '0';
        // printf("Bit singolo: %c\n", bit);
        strncat(binary, &bit, 1);
    }

    // printf("Provola: %s\n", binary);

    return binary;
}