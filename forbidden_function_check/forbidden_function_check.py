import glob
import os
import re

SRC_DIR = "../src/"
ALLOWED_FILE = "./allowed_func.txt"

TYPE_LIST = ['int', 'char', 'float', 'double', 'bool', 'void', 
             'short', 'long', 'signed', 'struct', 'const']

def valid_func_name(name):
    """Check if the provided name is a valid C function/identifier name."""
    return bool(re.match(r"^[a-zA-Z_][a-zA-Z0-9_]*$", name))

def is_function_declaration(line):
    """
    Heuristically checks if a given line is a function declaration.
    Returns the function name if found, or None otherwise.
    """
    line = line.strip()
    if len(line) < 2 or line[0] in ('#', '/') or '(' not in line or ')' not in line:
        return None
    # We expect the line to end with either ')' or '{'
    if not (line.endswith(')') or line.endswith('{')):
        return None

    # Remove pointer or address symbols for cleaner parsing.
    line_clean = re.sub(r'[\*&]', ' ', line)
    
    # Use regex to match a pattern like: return_type function_name(parameters)
    match = re.match(r'.*\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\).*', line_clean)
    if match:
        return match.group(1)
    return None

def get_allowed_functions():
    """
    Collects function names from both the source files and the allowed functions file.
    Returns a set of allowed function names.
    """
    functions = set()

    # Extract functions declared in the source files.
    for filepath in glob.iglob(os.path.join(SRC_DIR, '**', '*.c'), recursive=True):
        with open(filepath, "r") as file:
            for line in file:
                func_name = is_function_declaration(line)
                if func_name:
                    functions.add(func_name)
    
    # Read the externally allowed functions.
    with open(ALLOWED_FILE, "r") as file:
        allowed_funcs = [f.strip() for f in file.read().split(",") if f.strip()]
        functions.update(allowed_funcs)
    
    return functions

def compare_functions(allowed_functions):
    """
    Scans source files for function calls and prints out any calls that are
    not present in the allowed_functions set.
    """
    # Regex to capture function calls: function_name( ... )
    function_call_pattern = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\(')
    forbidden_count = 0
    
    for filepath in glob.iglob(os.path.join(SRC_DIR, '**', '*.c'), recursive=True):
        with open(filepath, "r") as file:
            for line in file:
                # Find all function calls in the line.
                matches = function_call_pattern.findall(line)
                for func in matches:
                    # Skip valid type casts and if the function is allowed.
                    if func not in allowed_functions and valid_func_name(func):
                        forbidden_count += 1
                        print(f"{filepath}: {line.strip()} --> forbidden call: {func}")
    
    print(f"Total forbidden function calls found: {forbidden_count}")

if __name__ == '__main__':
    allowed_funcs = get_allowed_functions()
    compare_functions(allowed_funcs)
