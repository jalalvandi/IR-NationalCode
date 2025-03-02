# IR-NationalCode

This project includes the implementation of the Iranian National Code validation algorithm in various programming languages. Each file contains a function that takes a national code as input and checks its validity.

## Algorithm Description

The Iranian National Code validation algorithm is as follows:
1. Remove non-numeric characters from the input.
2. Check the length of the code (it should be between 8 to 10 digits).
3. Standardize the code to 10 digits by adding leading zeros.
4. Checking for repeating digits (e.g., 1111111111 is invalid).
5. Extract the control digit (the last digit).
6. Calculate the weighted sum of the digits (weights from 10 to 2).
7. Calculate the remainder and the control digit.
8. Compare the calculated control digit with the extracted control digit.

## Usage

Examples for each file are written inside the respective file.

## Authors

- [Sina Jalalvandi]

## License

This project is licensed under the MIT License. See the LICENSE file for more details.