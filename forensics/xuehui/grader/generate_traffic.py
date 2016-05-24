import requests
import random
import hashlib


def main():
    url = "http://139.59.224.70/php.zip"
    chunksz = 13337
    fullfile = requests.get(url).content
    hsh = hashlib.md5(fullfile).hexdigest()
    print "MD5: %s" % hsh
    print "Need to split up %d byte file into chunks of %d" % (len(fullfile),
                                                               chunksz)
    chunks = range(0, len(fullfile), chunksz)
    print "This means we have to make %d requests." % (len(chunks))

    print "Randomising order..."
    random.shuffle(chunks)

    print "Preparing verification array."
    verification = [None]*len(fullfile)

    raw_input("[Press enter to begin traffic generation]")
    print "Starting the traffic generation..."
    for i in chunks:
        print i
        r = "bytes=%d-%d" % (i, i + chunksz - 1)
        data = requests.get(url, headers={"Range": r}).content
        print len(data)
        verification[i:i+chunksz] = list(data)

    hshv = hashlib.md5("".join(verification)).hexdigest()
    print "MD5 of Reassembled: %s" % hshv

    print "Traffic generation done."

if __name__ == "__main__":
    main()
