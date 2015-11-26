#!/usr/bin/python
import binascii
import sys, getopt



def getDict(f):
    byte = [[] for x in range(0,1000)]
    i=0
    while 1:
        byte[i].append(binascii.hexlify(f.read(1)))
        if byte[i][-1] == "":
            break
        if (byte[i][-1] == '0a') and (len(byte[i])>1):
            i=i+1
    dict = {}
    #print byte
    for j in range(0, i):
        if byte[j][-1]=='0a':
            byte[j].pop(-1)
        if byte[j][-1]=='20':
            byte[j].pop(-1)
        byte[j][4]=int(byte[j][4])-30
        for k in range(5, len(byte[j])):
            byte[j][4]=str((byte[j][4]))+str((int(byte[j][5])-30))
            byte[j].pop(5)
        byte[j][4]=int(byte[j][4])
        dict[byte[j][0]] = byte[j][4]
    return dict


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
   f = open(inputfile, "rb")
   dict1 = getDict(f)
   f.close()
   print "Expected ASCII count is", dict1
   f = open(outputfile, "rb")
   dict2 = getDict(f)
   f.close()
   print "Your ASCII count is", dict2
   flag=0
   if cmp(dict1, dict2) == 0:
       print 1.0
   elif len(dict2) == 256:
       for i in dict1.keys():
           if dict1[i]!=dict2[i]:
               flag=1
               break
       if flag==1:
           print 0.0
       else: 
           print 1.0
   else:
       print 0.0

if __name__ == "__main__":
    main(sys.argv[1:])
