#!/usr/bin/python
import binascii
import sys, getopt


import binascii
def getDict(f):
    byte = []
    while 1:
        byte.append(binascii.hexlify(f.read(1)))
        if byte[-1] == "":
            break
    byte.pop(-1)
    return byte

def main(argv):
   inputfile = ''
   outputfile = ''
   try:
      opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
   except getopt.GetoptError:
      print 'countchar.py -i <inputfile> -o <outputfile>'
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print 'countchar.py -i <inputfile> -o <outputfile>'
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg
      elif opt in ("-o", "--ofile"):
         outputfile = arg

   fp = open(inputfile, "rb")
   first=getDict(fp)
   print "Expected File is", first

   fp = open(outputfile, "rb")
   second=getDict(fp)
   print "Your File is", second

   if cmp(first, second) == 0:
      print 1.0
   else:
      sumcheck=sum([first[i]==second[i] for i in range(0, len(first))])-len(first)
      #print sumcheck
      if sumcheck==0:
         print 1.0
      else:
         print 0.0

if __name__ == "__main__":
    main(sys.argv[1:])
