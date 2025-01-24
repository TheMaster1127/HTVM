import sys
import io
import unicodedata

# Set the default encoding to UTF-8
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

def replace_non_ascii(text, delimiter="|"):
    result = []
    i = 0
    while i < len(text):
        char = text[i]
        # Check if the character is ASCII (ordinal value <= 127)
        if ord(char) <= 127:
            result.append(char)  # Keep ASCII characters as-is
        else:
            # Replace non-ASCII characters with their Unicode code point value (UXXXX)
            code_point = f"U-{ord(char):04X}"  # Format as UXXXX
            result.append(code_point)
            # Add a delimiter only if the next character is non-ASCII
            if i + 1 < len(text) and ord(text[i + 1]) > 127:
                result.append(delimiter)
        i += 1
    return "".join(result)

# Example usage
input_text = """Hello, Привет! 😊
This is a test.
Line 2: こんにちは"""
output = replace_non_ascii(input_text)

print("Original Text:")
print(input_text)
print("\nProcessed Text:")
print(output)
