int atoi(char *s) {
  int sign = 1, i, result = 0;

  // Check if the string is empty.
  if (s[0] == '\0') {
    return 0;
  }

  // Check if the first character of the string is a minus sign.
  if (s[0] == '-') {
    sign = -1;
    i = 1;
  } else {
    i = 0;
  }

  // Loop through the string, adding each digit to the result.
  for (; s[i] != '\0' && isdigit(s[i]); i++) {
    result *= 10;
    result += s[i] - '0';
  }

  // Return the result, multiplied by the sign.
  return result * sign;
}
