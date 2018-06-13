#!/usr/bin/python

import re, sys

class InputWire:
  party = 0
  wire = 0

class OutputWire:
  party = 0
  wire = 0

class Gate:
  gateType = 0
  inWire1 = 0
  inWire2 = 0
  outWire = 0


def scanInWire(line):
  inWire = InputWire()
  m = re.search('IN\W([0-9]*)\W([0-9]*)', line)
  inWire.wire = int(m.group(1))
  # Frigate uses 1-indexed party numbers, but we will use 0-indexed
  inWire.party = int(m.group(2)) - 1 
  return inWire

def scanOutWire(line):
  outWire = OutputWire()
  m = re.search('OUT\W([0-9]*)\W([0-9]*)', line)
  outWire.wire = int(m.group(1))
  # Frigate uses 1-indexed party numbers, but we will use 0-indexed 
  outWire.party = int(m.group(2)) - 1
  return outWire

def scanGate(line):
  gate = Gate()
  m = re.search('[a-z]*\W?([0-9]*)\W+([0-9]*)\W([0-9]*)\W([0-9]*).*', line)
  gate.gateType = int(m.group(1))
  gate.outWire = int(m.group(2))
  gate.inWire1 = int(m.group(3))
  gate.inWire2 = int(m.group(4))
  return gate

# BMR implementation doesn't allow 0 or 15 as gate values
def fixConstants(gate):
  # 0 = a XOR a
  if gate.gateType == 0:
    gate.gateType = 6
    gate.inWire2 = gate.inWire1
  # 1 = a NXOR a
  elif gate.gateType == 15:
    gate.gateType = 9
    gate.inWire2 = gate.inWire1
  

def semiHonestBMRPrint(nParties, maxWireId, inWires, outWires, gates):
  print '#'
  print str(len(gates)) + ' ' + str(nParties) + ' ' + str(maxWireId + 1) 

  # Print Inputs
  for i in range(0, nParties):
    inWiresP = []
    for inWire in inWires:
      if inWire.party == i:  
        inWiresP.append(inWire)

    print 'P' + str(i) + ' ' + str(len(inWiresP))
    for inWire in inWiresP:
      print inWire.wire

  # Print Outputs. (Uses P0's output for everone.)
  outWiresP0 = []
  for outWire in outWires:
    if outWire.party == 0:
      outWiresP0.append(outWire)
  
  print 'Out ' + str(len(outWiresP0))
  for outWire in outWiresP0:
    print outWire.wire

  # Print Gates
  print '#'
  for gate in gates:
    fixConstants(gate)
    t = gate.gateType
    gateStr = str(t%2) + str((t/2)%2) + str((t/4)%2) + str((t/8)%2)
    print str(gate.inWire1) + ' ' + str(gate.inWire2) + ' ' + str(gate.outWire) + ' ' + gateStr



if (len(sys.argv) < 2) :
  print 'Too few arguments.'
  sys.exit(2)

with open(sys.argv[1], 'r') as fp:
  nParties = 1
  inWires = []
  outWires = []
  gates = []
  wireConv = {}
  maxWireId = 0
  usedWireIds = []
  for line in fp:
    if re.match('IN.*', line) is not None:
      inWire = scanInWire(line)
      nParties = max(inWire.party + 1, nParties)
      maxWireId = max(int(inWire.wire), maxWireId)
      usedWireIds.append(inWire.wire)
      inWires.append(inWire)
    elif re.match('OUT.*', line) is not None:
      outWire = scanOutWire(line)
      nParties = max(outWire.party, nParties)
      if outWire.wire in wireConv:
        outWire.wire = wireConv[outWire.wire]
      outWires.append(outWire)
    else:
      gate = scanGate(line)
      if gate.inWire1 in wireConv:
        gate.inWire1 = wireConv[gate.inWire1]
      if gate.inWire2 in wireConv:
        gate.inWire2 = wireConv[gate.inWire2]
      # If the output wire is already used, use a new larger wireId
      # Require output wires have higher IDs than input wires 
      if (gate.inWire1 >= gate.outWire
          or gate.inWire2 >= gate.outWire
          or gate.outWire in usedWireIds):
        wireConv[gate.outWire] = maxWireId + 1
        gate.outWire = maxWireId + 1
      gates.append(gate)
      maxWireId=max(gate.outWire, maxWireId)
      usedWireIds.append(gate.outWire)

  semiHonestBMRPrint(nParties, maxWireId, inWires, outWires, gates)
  
