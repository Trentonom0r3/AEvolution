import os
import re

# Define directories to search
directories = ['./commands', './responses']

# Pattern to match class definitions
pattern = re.compile(r'class\s+(\w+)\s*:\s*public\s+(Command|Response)\s*\{')

def find_classes_and_generate_boost_export(directory):
    # List to store found class names
    class_names = []

    # Walk through the directory
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.h'):  # Look for header files
                file_path = os.path.join(root, file)
                with open(file_path, 'r') as f:
                    content = f.read()
                    matches = pattern.findall(content)
                    class_names.extend([match[0] for match in matches])
    
    # Generate BOOST_CLASS_EXPORT output
    for class_name in class_names:
        print(f'BOOST_CLASS_EXPORT({class_name})')

# Process each directory
for directory in directories:
    find_classes_and_generate_boost_export(directory)
