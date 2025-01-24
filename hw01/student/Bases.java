/**
 * CS 2110 Spring 2024 HW1
 * Part 2 - Coding with bases
 *
 * @author Shanzeh Amirali
 *
 * Global rules for this file:
 * 
 * - You cannot use multiplication, division, and modulus operators
 * - You cannot use nested loops
 * - You cannot declare file-level variables
 * - You cannot use switch statements
 * - You cannot use the unsigned right shift operator (>>>)
 * - You cannot use helper methods, call any other methods, or use recursion.
 * 
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 loops per method. This includes
 *   for loops, while loops and do-while loops.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from String literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 */
public class Bases
{
    /**
     * Convert a String containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("110"); // => 6
     */
    public static int binaryStringToInt(String binary)
    {
        int num = 0;
        int pow = 0;
        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary.charAt(i) == '1') {
                num += (1 << pow);
            }
            pow++;
        }
        return num;
    }

    /**
     * Convert a String containing ASCII characters (in decimal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("46"); // => 46
     */
    public static int decimalStringToInt(String decimal)
    {
        int num = 0;
        int base = 1;
        for (int i = 0; i < decimal.length(); i++) {
            int c = decimal.charAt(decimal.length() - i - 1);
            num += (c - 48); //how to multiply by the base
            base = (base << 1) + (base <<3);
        }
        return num;
    }

    /**
     * Convert a String containing ASCII characters (in binary) to an a String containing ASCII characters (in octal).
     * The input String will only contain the numbers 0 and 1.
     * You may assume that the length of the binary String is divisible by 3.
     *
     * Example: binaryStringToOctalString("110100"); // => "64"
     */
    public static String binaryStringToOctalString(String binary)
    {
        String str = "";
        int octIndex = 0;
        for (int i = 0; i < binary.length(); i += 3) {
            int one = Integer.valueOf(binary.charAt(i)) << 2;
            int two = Integer.valueOf(binary.charAt(i + 1)) << 1;
            int three = Integer.valueOf(binary.charAt(i + 2));
            int addNum = one + two + three;
            str = str + addNum;
        }
        return str;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hex).
     *
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters
     * necessary to represent the number that was passed in.
     *
     * Example: intToHexString(30); // => "1E"
     */
    public static String intToHexString(int hex)
    {
        String sb = "";
        while (hex > 0) {
            sb = (hex & 15) + sb;
            hex = hex >> 4;
        }
        return sb;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * hex into a String containing ASCII characters that represent that same
     * value in binary. The returned binary String should not have any leading
     * zeros, even if there are in the input hex String. If the hex String
     * evaluates to zero, then return the equivalent of zero in binary.
     *
     * The output String should only 0's and 1's.
     *
     * Example: hexStringToBinaryString("0F32A65C"); => "1111001100101010011001011100"
     */
    public static String hexStringToBinaryString(String hex)
    {
//        int pow = 0;
//        int num = 0;
//        String str = "0";
//        for (int i = hex.length() - 1; i >= 0; i--) {
//            if ((hex.charAt(i) >= 'A') && (hex.charAt(i) <= 'F')) {
//                num += ((hex.charAt(i) - 55) << pow);
//            } else {
//                num += ((hex.charAt(i) - 48) << pow);
//            }
//            pow = pow + 4;
//        }
//        while (num > 0) {
//            if ((num & 1) == 1) {
//                str = '1' + str;
//            } else {
//                str = '0' + str;
//            }
//            num = num >> 1;
//        }
//        return str;
        String str = "";
        for (int i = 0; i < hex.length(); i++) {
            char a = hex.charAt(i);

            int dec;
            if (a >= 'A' && a <= 'F') {
                dec = a - 'A' + 10;
            } else {
                dec = a - '0';
            }
        }
    }
}
