def grade(arg, key):
    if "XCTF{welov3r3trostuff}".lower() == key.lower():
        return True, "You Got The Flag!"
    else:
        return False, "..."
