/**
 * Validates an Iranian National Code based on the official algorithm.
 * 
 * @param {string} nationalCode - The national code to validate
 * @returns {boolean} - True if valid, false otherwise
 */
function validateIranianNationalCode(nationalCode = '') {
    // Remove non-numeric characters
    const cleanedCode = (nationalCode || '').replace(/[^0-9]/g, '');
    
    // Check length (must be 8 to 10 digits)
    const codeLength = cleanedCode.length;
    if (codeLength < 8 || codeLength > 10) {
        return false;
    }

    // Standardize to 10 digits by padding with leading zeros
    const standardizedCode = cleanedCode.padStart(10, '0');
    
    // Check if all digits are the same
    if (standardizedCode.split('').every(digit => digit === standardizedCode[0])) {
        return false;
    }

    // Extract check digit (last digit)
    const checkDigit = parseInt(standardizedCode.slice(-1));
    const digits = standardizedCode.slice(0, -1).split('').map(Number);

    // Calculate weighted sum (weights: 10 down to 2)
    const sum = digits.reduce((acc, digit, i) => acc + digit * (10 - i), 0);

    // Compute remainder and check digit
    const remainder = sum % 11;
    const calculatedCheckDigit = remainder < 2 ? remainder : 11 - remainder;

    // Return true if check digits match
    return calculatedCheckDigit === checkDigit;
}

// Test
console.log(validateIranianNationalCode('6587452158')); // false