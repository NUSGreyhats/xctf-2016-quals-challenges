def grade(arg, key):
    if "XCTF{h4il_l0rd_artgerm!}".lower() == key.lower():
        return True, "You found the real artist! +10 points to you."
    else:
        return False, ""
