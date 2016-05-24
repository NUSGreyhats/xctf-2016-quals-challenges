def grade(arg, key):
    if "nusgreyhats" in key.lower().replace(" ", ""):
        return True, "Very easy."
    else:
        return False, "Wrong."
