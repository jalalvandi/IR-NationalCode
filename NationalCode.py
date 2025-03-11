import re

def validate_iranian_national_code(national_code: str) -> bool:
    # Remove non-numeric characters
    cleaned_code = re.sub(r'[^0-9]', '', national_code)
    code_length = len(cleaned_code)

    # Check if length is between 8 and 10 digits
    if code_length < 8 or code_length > 10:
        return False

    # Standardize to 10 digits by padding with leading zeros
    standardized_code = cleaned_code.zfill(10)
    digits = list(map(int, standardized_code))

    # Check if all digits are the same (invalid case)
    if len(set(digits)) == 1:
        return False

    # Extract the check digit (last digit)
    check_digit = digits.pop()

    # Calculate weighted sum (weights: 10 down to 2)
    weighted_sum = sum(digits[i] * (10 - i) for i in range(9))

    # Compute remainder and check digit
    remainder = weighted_sum % 11
    calculated_check_digit = remainder if remainder < 2 else 11 - remainder

    # Return true if calculated check digit matches the provided one
    return calculated_check_digit == check_digit

# Test cases
print(validate_iranian_national_code('1111111111'))  # False (repeating digits)
print(validate_iranian_national_code('12345'))       # False (too short)
