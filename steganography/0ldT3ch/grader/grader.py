def grade(arg, key):
    if "XCTF{G00D_0LD_PAPER_TAPE_CRYPTO}".lower() == key.lower():
        return True, "You Got The Flag!"
    else:
        return False, "..."
