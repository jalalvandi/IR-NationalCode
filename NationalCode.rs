use regex::Regex;

/**
 * Validates an Iranian National Code based on the official algorithm.
 * 
 * # Arguments
 * * `national_code` - The national code as a string
 * 
 * # Returns
 * * `bool` - True if valid, false otherwise
 */
fn validate_iranian_national_code(national_code: &str) -> bool {
    // Remove non-numeric characters
    let re = Regex::new(r"[^0-9]").unwrap();
    let cleaned_code = re.replace_all(national_code, "").to_string();
    
    // Check length (must be 8 to 10 digits)
    let code_length = cleaned_code.len();
    if code_length < 8 || code_length > 10 {
        return false;
    }

    // Standardize to 10 digits by padding with leading zeros
    let standardized_code = format!("{:0>10}", cleaned_code);
    
    // Check if all digits are the same
    if standardized_code.chars().all(|c| c == standardized_code.chars().next().unwrap()) {
        return false;
    }

    // Extract check digit (last digit)
    let check_digit = standardized_code.chars().last().unwrap().to_digit(10).unwrap() as i32;
    let digits: Vec<i32> = standardized_code[..9].chars().map(|c| c.to_digit(10).unwrap() as i32).collect();

    // Calculate weighted sum (weights: 10 down to 2)
    let sum: i32 = digits.iter().enumerate().map(|(i, &digit)| digit * (10 - i as i32)).sum();

    // Compute remainder and check digit
    let remainder = sum % 11;
    let calculated_check_digit = if remainder < 2 { remainder } else { 11 - remainder };

    // Return true if check digits match
    calculated_check_digit == check_digit
}

// Test
fn main() {
    println!("{}", validate_iranian_national_code("6587452158")); // false
}