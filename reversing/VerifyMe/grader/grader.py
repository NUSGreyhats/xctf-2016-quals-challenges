def grade(arg, key):
    if "XCTF{sometimespatchingismucheasierthanreversing}".lower() == key.lower():
        return True, "Hope you did it by patching. +20 Points to you!"
    else:
        return False, "..."
