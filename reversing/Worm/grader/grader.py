def grade(arg, key):
    if "XCTF{db8496580ff636bc51ade827d1999d32d5dabb1c}".lower() == key.lower():
        return True, "You just uncovered worm2k16! +40 points to you!"
    else:
        return False, "..."
