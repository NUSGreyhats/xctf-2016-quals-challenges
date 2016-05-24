def grade(arg, key):
    if "XCTF{O_Malbolge_Wh3r3_Ar7_Th0u}".lower() == key.lower():
        return True, "You got it!"
    else:
        return False, "..."
