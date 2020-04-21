/**
 * CS 2110 Spring 2020 HW1
 * Part 2 - Coding with bases
 *
 * @author Saumya Jain
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt
 * - You may declare exactly one String variable each in intToOctalString and
 *   and BinaryStringToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int number = 0;
        for (int i = 0; i < binary.length(); i++) {
            if (binary.charAt(binary.length() - 1 - i) == '1') {
                number += 1 << i;
            }
        }
        return number;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int number = 0;
        int pow = 1;
        for (int i = decimal.length()-1; i >= 0; i--) {
            number += (decimal.charAt(i) - '0') * pow;
            pow *= 10;
        }
        return number;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int number = 0;
        int shift = 0;
        for (int i = hex.length() - 1; i >= 0; i--) {
            char current = hex.charAt(i);
            if (current > '9') {
                number += (current - '0' - 7) << shift;
            } else {
                number += (current - '0') << shift;
            }
            shift += 4;
        }
        return number;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToOctalString(10); // => "12"
     *
     * You may declare one String variable in this method.
     */
    public static String intToOctalString(int octal)
    {
        String number = "";
        if (octal == 0) {
            return "0";
        }
        for (int i = octal; i > 0; i = i >> 3) {
            number = (i - ((i >> 3) << 3)) + number;
        }
        return number;
    }

    /**
     * Convert a String containing ASCII characters representing a number in binary into 
     * a String containing ASCII characters that represent that same value in hexadecimal.
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The length of all the binary strings passed in will be of size 32.
     * The hex String returned should contain 8 characters. 
     *
     * Example: binaryStringToHexString("00000010111110100001101100111000"); // => 02FA1B38
     *
     * You may declare one String variable in this method.
     */
    public static String binaryStringToHexString(String binary)
    {
        int number = 0;
        String hexString = "";
        int current = 0;
        for (int i = 0; i < binary.length(); i++) {
            number += (binary.charAt(binary.length() - 1 - i) - 48) << i;
        }
        for (int i = 0; i <= 28; i += 4) {
            current = (number & (0xF << i)) >> i;
            if (current <= 9) {
                hexString = (char)(current + 48) + hexString;
            } else {
                hexString = (char)(current + 55) + hexString;
            }
        }
        return hexString;
    }
}
