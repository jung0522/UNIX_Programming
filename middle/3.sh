#!/bin/bash
# 3.sh: Generates a multiplication table (2 to 9) using a Bash script

# Outer loop: iterates through numbers 2 to 9 (multiplication tables)
for i in {2..9}; do
  # Inner loop: iterates through numbers 1 to 9 (factors)
  for j in {1..9}; do
    # Print the product of i and j, aligned to 4 characters wide
    printf "%4d" $((i * j))
  done
  # Print a new line after each row of the table
  echo
done

