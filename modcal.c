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
char *intToBinary3Bits(int num);
char *numToStr(char *binary);

int main(int argc, char *argv[])
{
    // EXAMPLE: rwxr-xr-x
    //             OWNER GROUP EVERYONE
    // READ    2^2   1     1      1
    // WRITE   2^1   1     0      0
    // EXECUTE 2^0   1     1      1
    // chmod = 755

    // Verifica se è stato fornito un argomento iniziale, altrimenti il programma non parte
    if (argc < 2)
    {
        printf("Error: Missing argument\n");
        exit(1);
    }

    // Verifica se l'argomento è troppo lungo
    // La forma in stringa: rwxr-xr-x ha una lunghezza di 9 caratteri
    // La forma numerica: 755 ha una lunghezza di 3 caratteri
    if (strlen(argv[1]) > 9)
    {
        printf("Error: Argument too long\n");
        exit(1);
    }

    char onlyLetters = TRUE;
    char onlyNumbers = TRUE;

    // Verifica se l'utente ha inserito i permessi di chmod in forma di stringa
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
        // Verifica se l'utente ha inserito i permessi di chmod in forma numerica
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == FALSE)
            {
                onlyNumbers = FALSE;
                break;
            }
        }
    }
    else if (onlyLetters == FALSE && strlen(argv[1]) > 3)
    {
        printf("Error: Argument too long for the numeric form\n");
        exit(1);
    }

    if (onlyLetters == FALSE && onlyNumbers == FALSE)
    {
        printf("Error: Argument invalid\n");
        exit(1);
    }
    if (onlyLetters == TRUE && strlen(argv[1]) < 9)
    {
        printf("Error: Argument invalid in string form\n");
        exit(1);
    }

    // Chiamata alle funzioni appropriate in base alla forma di input dell'utente
    if (onlyLetters == TRUE)
        chmodStringToNumber(argv[1]);
    else
        chmodNumberToString(argv[1]);

    return 0;
}

// Converte i permessi di chmod in forma di stringa in un numero intero
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

// Converte un numero di chmod in una stringa di permessi di chmod
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

// Converte i permessi di chmod in forma di stringa in un numero intero
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

// Converte un numero di chmod in una stringa di permessi di chmod
int chmodNumberToString(char *value)
{
    char owner = value[0];
    char group = value[1];
    char everyone = value[2];

    char *stringOwner = intToBinary3Bits(owner - '0');
    char *stringGroup = intToBinary3Bits(group - '0');
    char *stringEveryone = intToBinary3Bits(everyone - '0');

    char *result = malloc(10); // 9 (rwxr-xr-x) + 1 (terminatore nullo)
    sprintf(result, "%s%s%s",
            numToStr(stringOwner), numToStr(stringGroup), numToStr(stringEveryone));

    printf("%s\n", result);
    free(result);

    return 0;
}

// Converte un numero in un numero binario a 3 bit
char *intToBinary3Bits(int num)
{
    if (num < 0 || num > 7)
    {
        printf("Error: Number out of range");
        exit(1);
    }

    char *binaryString = (char *)malloc(4); // 3 bits + null terminator

    if (binaryString == NULL)
    {
        printf("Error: Memory allocation failed");
        exit(1);
    }

    for (int i = 2; i >= 0; i--)
    {
        binaryString[i] = (num & 1) + '0'; // Converte il bit meno significativo in un carattere
        num >>= 1;                         // Shift a destra per elaborare il bit successivo
    }

    binaryString[3] = '\0'; // Termina la stringa con il terminatore nullo
    return binaryString;
}
