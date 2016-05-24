def grade(arg, key):
    if "XCTF{batman_is_awesome}" in key:
        return True, "Cool, you can piece together things."
    else:
        return False, "Wrong."
