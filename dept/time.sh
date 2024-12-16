#!/bin/bash

# Get the current hour in 24-hour format
h=$(date +%H)

# Determine the greeting based on the time of day
if [ $h -lt 12 ]; then
    echo "G M."
elif [ $h -lt 18 ]; then
    echo "G A."
elif [ $h -lt 22 ]; then
    echo "G E."
else
    echo "G N."
fi

