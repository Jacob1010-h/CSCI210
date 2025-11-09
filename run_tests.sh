#!/bin/bash
# ===============================
# Run all filesystem tests + show diffs
# Usage: ./run_tests.sh
# ===============================

set -e  # stop on first compile error

# build
echo "Compiling..."
gcc -Wall -Wextra -o main main.c mkdirSplitpath.c otherCommands.o

# find all test input files
for testfile in test_cases/test*.in; do
    base="${testfile%.in}"            # remove .in
    myout="${base}_my.out"            # your output file
    expected="${base}.out"            # expected output file

    echo "=================================="
    echo "Running $testfile..."
    ./main < "$testfile" 2>/dev/null > "$myout"

    # compare outputs
    echo "Diffing $myout vs $expected:"
    if diff -u "$expected" "$myout"; then
        echo "✅ PASS: $testfile matches expected output."
    else
        echo "❌ FAIL: Differences found for $testfile."
    fi
    echo
done

echo "=================================="
echo "All tests completed."
echo "=================================="
