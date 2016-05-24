def grade(arg, key):
    if "XCTF{h3ll0k1tty}".lower() == key.lower():
        return True, "+20 Points to you!"
    else:
        return False, "..."
