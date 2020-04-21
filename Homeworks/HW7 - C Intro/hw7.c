/**
 * @file hw7.c
 * @author Saumya Jain
 * @brief Command-line argument & expression parsing logic
 * @date 2020-03-10
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stdio.h>
#include "hw7.h"
#include "errcodes.h"

#define FALSE 0
#define TRUE 1

// One-time defined global array of expressions
struct expression arr[MAX_NUMBER_OF_EXPRESSIONS];

/**
 * @brief Convert a string containing ASCII characters (in decimal) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in str
 */
int decimalStringToInt(const char *str)
{
    size_t power = my_strlen(str);
    int multiplier = 1;
    for(int i = 0; i < (int) power - 1; i++) {
        multiplier = multiplier * 10;
    }

    int answer = 0;
    int number = 0;

    while(*str != 0) {
        number = *str - '0';
        answer = answer + number * multiplier;
        multiplier = multiplier / 10;
        str++;
    }

    return answer;
}

/**
 * @brief Convert a string containing ASCII characters (in hex) to an int.
 * 
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in hexadecimal str
 */
int hexStringToInt(const char *str)
{
    size_t len = my_strlen(str);
    int multiplier = 1;
    for(int i = 0; i < (int)len - 1; i++) {
        multiplier = multiplier
         * 16;
    }

    int answer = 0;
    int number;

    while(*str != 0) {
        if (*str >= 'A' && *str <= 'F') {
            number = *str - '7';
        } else {
            number = *str - '0';
        }
        answer = answer + number * multiplier;
        multiplier = multiplier / 16;
        str++;
    }

    return answer;
}

/**
 * @brief Parser algorithm for determining the result of a basic math expression.
 * 
 * @param expression A null terminated expression retrieved as a command line arg
 * @param index Indicating the corresponding struct in the global struct array (for this expression) to be populated
 */
void parseExpression(char *expression, int index)
{
    int start = 0;
    int end = 0;
    int sum = 0;
    int temp;
    int multiplier = 1;
    //0x1+000

    // TODO: Iterate through the string, parsing each sum term and adding them to a result

    //iterating through string until null
    while(expression[start] != 0) {
        while(expression[end] != '+' && expression[end] != '-' && expression[end] != 0) {
            end++;
        }

        //start from the beginning
        if (start == 0) {
            int result;

            //if the first two are 0x
            if (start < (int) my_strlen(expression) && expression[start] == '0' && expression[start + 1] == 'x' ) {
                if (start + 2 < (int) my_strlen(expression) && expression[start + 2] == 'x') {
                    my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[index].result = 0;
                    arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                    return;

                } else {
                    //calculate hex here
                    multiplier = 1;
                    temp = start + 2;

                    while(temp < end - 1) {
                        multiplier = multiplier * 16;
                        temp++;
                    }

                    temp = start + 2;
                    result = 0;
                    while(temp < end) {
                        int number;
                        if (expression[temp] >= 'A' && expression[temp] <= 'F') {
                            number = expression[temp] - '7';
                        } else if (expression[temp] >= '0' && expression[temp] <= '9') {
                            number = expression[temp] - '0';
                        } else {
                            my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                            arr[index].result = 0;
                            arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                            return;
                        }

                        result = result + number * multiplier;
                        multiplier = multiplier / 16;
                        temp++;
                    }
                }
                sum = sum + result;

            } else if (expression[start] == 'x') {
                my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[index].result = 0;
                arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                return;

            } else {
                //decimal form
                multiplier = 1;
                temp = start;
                while (temp < end - 1) {
                    multiplier = multiplier * 10;
                    temp++;
                }

                temp = start;
                result = 0;
                while(temp < end) {
                    int number;
                    number = expression[temp] - '0';
                    result = result + number * multiplier;
                    multiplier = multiplier / 10;
                    temp++;
                }
                sum = sum + result;
            }

        } else if (expression[start] == '+' || expression[start] == '-') {
        //for expressionsn that start with + OR -
            //getting past first character
            start++;
            int result;

            if (start < (int) my_strlen(expression) && expression[start] == '0' && expression[start + 1] == 'x' ) {

                //checking to see if the first two characters are 0x
                if (start + 2 < (int) my_strlen(expression) && expression[start + 2] == 'x') {
                    my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[index].result = 0;
                    arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                    return;

                } else {
                    //calculate hex
                    multiplier = 1;
                    int temp = start + 2;
                    while(temp < end - 1) {
                        multiplier = multiplier * 16;
                        temp++;
                    }
                    temp = start + 2; 
                    result = 0;

                    while(temp < end) {
                        int number;
                        if (expression[temp] >= 'A' && expression[temp] <= 'F') {
                            number = expression[temp] - '7';
                        } else if (expression[temp] >= '0' && expression[temp] <= '9') {
                            number = expression[temp] - '0';
                        } else {
                            my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                            arr[index].result = 0;
                            arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                            return;
                        }
                        result = result + number * multiplier;
                        multiplier = multiplier / 16;
                        temp++;
                    }
                }

                if (expression[start - 1] == '-') {
                    sum = sum - result;
                } else {
                    sum = sum + result;
                }

            } else if (expression[start] == 'x') {
                my_strncpy(arr[index].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[index].result = 0;
                arr[index].errorCode = ERR_MALFORMED_HEX_FOUND;
                return;

            } else {
                int result;

                //the decimal form
                multiplier = 1;
                temp = start;
                while (temp < end - 1) {
                    multiplier = multiplier * 10;
                    temp++;
                }

                temp = start;
                result = 0;
                while(temp < end) {
                    int number;
                    number = expression[temp] - '0';
                    result = result + number * multiplier;
                    multiplier = multiplier / 10;
                    temp++;
                }

                if (expression[start - 1] == '-') {
                    sum = sum - result;
                } else {
                    sum = sum + result;
                }
            } 
        }
        start = end;
        end++;
    }

    // TODO: Initialize the struct info for this expression and write it to the struct
    my_strncpy(arr[index].buffer, expression, my_strlen(expression));
    arr[index].result = sum;
    arr[index].errorCode = NO_ERROR;
}

/**
 * @brief Helper method for printing out the global array struct info
 * DO NOT MODIFY THIS METHOD AS IT IS USED FOR THE LAST STEP (PIPE).
 */
void printArrayDebug(void)
{
    // Safety check
    if (sizeof(arr) / sizeof(arr[0]) != MAX_NUMBER_OF_EXPRESSIONS)
    {
        printf("ERROR: MISMATCH ARRAY LENGTH WITH MACRO: MAX_NUMBER_OF_EXPRESSIONS.\n");
        return;
    }

    for (int i = 0; i < MAX_NUMBER_OF_EXPRESSIONS; i++)
    {
        printf("\nStruct info at index %d:\n", i);
        printf("Expression: %s\n", arr[i].buffer);
        printf("Result: %d\n", arr[i].result);
        printf("ErrorCode: %u\n", arr[i].errorCode);
        printf("---------------------\n");
    }
}

/**
 * @brief Main method, responsible for parsing command line argument and populating expression structs in the global arr
 * 
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int my_main(int argc, char const *argv[])
{
    UNUSED_FUNC(hexStringToInt);
    UNUSED_FUNC(parseExpression);
    UNUSED_FUNC(printArrayDebug);
    UNUSED_FUNC(decimalStringToInt);
    UNUSED_PARAM(argv);
    
    // Initial check: We need at least 1 math expression passed in
    // ( Yes argc can possibly be zero! But we don't worry about that too much in this hw :) )
    if (argc < 2)
    {
        printf("USAGE:   ./hw7 [-d] \"basic math expressions separated by quotation marks\"\n");
        printf("EXAMPLE: ./hw7 \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        printf("EXAMPLE FOR PRINTING OUT DEBUG INFO: ./hw7 -d \"3+0x40-7+5\" \"0xA6+5000-45\"\n");
        return 1; // Exit failure (value is implementation defined)
    }

    if (my_strncmp(argv[1], DEBUG_FLAG, (int) my_strlen(DEBUG_FLAG)) == 0 && argc > MAX_NUMBER_OF_EXPRESSIONS + 2) {
        // error of too many specified expressions, printf("PROGRAM ERROR: Too many expressions specified!");
        return 1;
    } else if (argc > MAX_NUMBER_OF_EXPRESSIONS + 1) {
        // error of too many specified expressions, printf("PROGRAM ERROR: Too many expressions specified!");
        return 1;
    }
    
    if (argc == 2) {
        
        int i = 1;
        while (i < argc) {

            //if there is a debug flag, no expressions
            if (my_strncmp(argv[i], DEBUG_FLAG, (int) my_strlen(DEBUG_FLAG)) == 0) {
                // error of no specified expression, printf("PROGRAM ERROR: No expression specified!");
                return 1;
            }
            if ((int)my_strlen(argv[i]) > MAX_EXPRESSION_LENGTH) {
                my_strncpy(arr[i - 1].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[i - 1].result = 0;
                arr[i - 1].errorCode = ERR_EXPRESSION_TOO_LONG;
            } else if ((int)my_strlen(argv[i]) < MIN_EXPRESSION_LENGTH) {
                my_strncpy(arr[i - 1].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                arr[i - 1].result = 0;
                arr[i - 1].errorCode = ERR_EXPRESSION_TOO_SMALL;
            } else {
                // expression has no issues
                parseExpression((char*)argv[i], i - 1);
            }
            i++;
        }
    } else {
        int i = 1;

        // case of first being '-d'
        if (my_strncmp(argv[i], DEBUG_FLAG, (int) my_strlen(DEBUG_FLAG)) == 0) {

            // going to the first expression
            i++;

            // iterating through the leftover terms
            while (i < argc) {

                // -d in incorrect location
                if (my_strncmp(argv[i], DEBUG_FLAG, 2)) {
                    my_strncpy(arr[i - 2].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 2].result = 0;
                    arr[i - 2].errorCode = ERR_MALFORMED_HEX_FOUND;
                }
                if ((int)my_strlen(argv[i]) > MAX_EXPRESSION_LENGTH) {
                    my_strncpy(arr[i - 2].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 2].result = 0;
                    arr[i - 2].errorCode = ERR_EXPRESSION_TOO_LONG;
                } else if ((int)my_strlen(argv[i]) < MIN_EXPRESSION_LENGTH) {
                    my_strncpy(arr[i - 2].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 2].result = 0;
                    arr[i - 2].errorCode = ERR_EXPRESSION_TOO_SMALL;
                } else {
                    // expression has no issues
                    parseExpression((char*) argv[i], i - 2);
                }
                i++;
            }
            printArrayDebug();
        } else {
            // this is the case when '-d' is not in spot 1

            // iterating through all the leftover terms
            while (i < argc) {
                if (my_strncmp(argv[i], DEBUG_FLAG, (int) my_strlen(DEBUG_FLAG))) { //-d in wrong place (always > 1 at this point)
                    my_strncpy(arr[i - 1].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 1].result = 0;
                    arr[i - 1].errorCode = ERR_MALFORMED_HEX_FOUND;
                }
                if ((int)my_strlen(argv[i]) > MAX_EXPRESSION_LENGTH) {
                    my_strncpy(arr[i - 1].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 1].result = 0;
                    arr[i - 1].errorCode = ERR_EXPRESSION_TOO_LONG;
                } else if ((int)my_strlen(argv[i]) < MIN_EXPRESSION_LENGTH) {
                    my_strncpy(arr[i - 1].buffer, ERROR_MSG, my_strlen(ERROR_MSG));
                    arr[i - 1].result = 0;
                    arr[i - 1].errorCode = ERR_EXPRESSION_TOO_SMALL;
                } else {
                    // expression has no issues
                    parseExpression((char*)argv[i], i - 1);
                }
                i++;
            }
        }
    }

    // Note 1: If debug flag is presented in any other location besides argv[1], it should be treated as a bad HEX value

    // Note 2: In order to protect our struct array from overflow and undefined behavior,
    // we need to make sure we don't pass in more command-line arguments than necessary.
    // Later on in the course you will learn how to dynamically allocate space for situations like this!

    return 0; // EXIT_SUCCESS
}
