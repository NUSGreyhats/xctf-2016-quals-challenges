def grade(arg, key):
    if "XCTF{Woah_did_u_just_br34k_md5?}" in key:
        return True, "Your web skills are formidable."
    else:
        return False, "Wrong."
