#!/bin/bash

TEMPLATE_FILE="DocumentationTemplates.md"
OUTPUT_DIR="."
NUM_FILE="num.txt"

count=0

awk -v output_dir="$OUTPUT_DIR" '
/^============\*\*\*[0-9]+\*\*\*============$/ {
    count++
    filename = output_dir "/" count ".md"
    file_content = ""
    next
}
/^============&&&[0-9]+&&&============$/ {
    # Remove leading/trailing empty lines
    sub(/^[ \t\r\n]+/, "", file_content)
    sub(/[ \t\r\n]+$/, "", file_content)
    # Print without extra newline at the end
    printf "%s", file_content > filename
    next
}
{
    file_content = file_content $0 "\n"
}
END {
    print count
}' "$TEMPLATE_FILE" > /tmp/doc_count.txt

count=$(cat /tmp/doc_count.txt)
echo -n "$count" > "$NUM_FILE"
rm /tmp/doc_count.txt

echo "Generated $count documentation files."
