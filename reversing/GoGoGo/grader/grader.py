def grade(arg, key):
    if "XCTF{K3y_G3n_M3_B@by}".lower() == key.lower():
        return True, "Key Generated! +30 Points to you!"
    else:
        return False, "..."
