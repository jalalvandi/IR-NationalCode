using System;
using System.Linq;
using System.Text.RegularExpressions;

/**
 * Validates an Iranian National Code based on the official algorithm.
 */
public class NationalCodeValidator
{
    /**
     * Checks if the given national code is valid.
     * 
     * @param nationalCode The national code as a string
     * @return bool Returns true if valid, false otherwise
     */
    public static bool ValidateIranianNationalCode(string nationalCode)
    {
        // Remove non-numeric characters
        string cleanedCode = Regex.Replace(nationalCode ?? "", "[^0-9]", "");
        
        // Check length (must be 8 to 10 digits)
        int codeLength = cleanedCode.Length;
        if (codeLength < 8 || codeLength > 10)
        {
            return false;
        }

        // Standardize to 10 digits by padding with leading zeros
        string standardizedCode = cleanedCode.PadLeft(10, '0');
        
        // Check if all digits are the same
        if (standardizedCode.All(c => c == standardizedCode[0]))
        {
            return false;
        }

        // Extract check digit (last digit)
        int checkDigit = standardizedCode[^1] - '0';
        string digits = standardizedCode.Substring(0, 9);

        // Calculate weighted sum (weights: 10 down to 2)
        int sum = 0;
        for (int i = 0; i < 9; i++)
        {
            sum += (digits[i] - '0') * (10 - i);
        }

        // Compute remainder and check digit
        int remainder = sum % 11;
        int calculatedCheckDigit = remainder < 2 ? remainder : 11 - remainder;

        // Return true if check digits match
        return calculatedCheckDigit == checkDigit;
    }

    // Test
    public static void Main()
    {
        Console.WriteLine(ValidateIranianNationalCode("6587452158")); // False
    }
}