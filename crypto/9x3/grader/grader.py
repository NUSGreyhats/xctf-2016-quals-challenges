def grade(arg, key):
    if "XCTF{YOUWANTMOARCRYPTOCHALLENGES}".lower() == key.lower():
        return True, "Getting warmed up for more crypto. +3 Points to you!"
    else:
        return False, "Try harder!"
