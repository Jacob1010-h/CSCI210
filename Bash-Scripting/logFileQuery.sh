#!/bin/bash


if [ $# -ne 3 ]; then
    echo "Usage: ./logFileQuery.sh <target dir> <person> <month>"
    exit 1
fi

# Gather Variables
TARGET_DIR="$1"
PERSON="$2"
MONTH="$3"

# Check if the Month is Valid
case "$MONTH" in
    Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) ;;
    *) echo "Invalid month"; exit 1;;
esac

# Reset and create queryResults directory
OUTDIR="queryResults"
rm -rf "$OUTDIR"
mkdir -p "$OUTDIR"

find "$TARGET_DIR" -type f | while read -r file; do
    # Check if file contains a date (dd/yyyy)
    if grep -qE "[0-9]{2}/20(1[0-9]|2[0-4])" "$file"; then
        # Get first line and check month
        first_line=$(head -n 1 "$file")
        if echo "$first_line" | grep -q "$MONTH"; then
            # Extract year from first line
            year=$(echo "$first_line" | grep -oE "20(1[0-9]|2[0-4])" | head -n 1)
            if [ -n "$year" ]; then
                # Search for person in this file
                grep "$PERSON" "$file" >> "$OUTDIR/${PERSON}_${MONTH}_${year}.log"
            fi
        fi
    fi
done
