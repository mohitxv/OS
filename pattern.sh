
# Iterate through each file in the current directory
for file in *; do
  # Check if the file is a regular file (not a directory)
  if [ -f "$file" ]; then
    # Use grep to search for the pattern in the file
    if grep -q "$pattern" "$file"; then
      echo "$file: Pattern found"
    else
      echo "$file: Pattern not found"
    fi
  fi
done
