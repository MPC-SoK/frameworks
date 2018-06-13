import sys, getopt

usage = sys.argv[0] + " -i <inputFile> -o <outputFile>"

try:
  opts, args = getopt.getopt(sys.argv[1:], 'i:o:', ['inputFile', 'outputFile'])
except getopt.GetoptError:
  print usage
  sys.exit(0)

inputDefined = False
outputDefined = False

for opt, arg in opts:
  if opt in ('-i', '--inputFile'):
    inputFileName = arg
    inputFile = open(inputFileName, 'r')
    inputDefined = True
  elif opt in ('-o', '--outputFile'):
    outputFileName = arg
    outputFile = open(outputFileName, 'w')
    outputDefined = True

if not (inputDefined and outputDefined):
  print usage
  sys.exit(2)


for line in inputFile:
  intVal = int(line)
  intVal = intVal % 2**32 # Represent negative-numbers using mod 2^32
  bitStr32 = '{0:032b}'.format(intVal)
  reversedBitStr32 = ''.join(reversed(bitStr32))
  outputFile.write(reversedBitStr32 + '\n')
