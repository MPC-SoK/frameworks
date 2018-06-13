import random, argparse

# useful tools
def str_struct(mems, vals):
    out = "{"
    for m,v in zip(mems,vals):
        out += "%s: %s;"%(m,v)
    out += "}"
    return out

def str_iv(player, val):
    return "INPUT_%s := %s;\n"%(player, val)

def gen_random_array(ll, bits=10):
    return [int(random.getrandbits(bits)) for _ in range(ll)]

# program input generation
def write_input(program, trials, gen_function):
    with open("%s/test.spec"%program, 'w') as fo:
        for t in range(trials):
            gen_function(fo)
            if t != trials-1:
                fo.write('---\n')

def gen_mult3_input(fo):
    p = 1
    for player in ["A","B","C"]:
        val = int(random.getrandbits(10))
        p *= val
        pl = str_iv(player, val)
        fo.write(pl)
    fo.write("return_value == %d;\n" % p)


def gen_innerprod_input(fo):
    LEN = 10
    bits = 14
    arA = gen_random_array(LEN,bits)
    arB = gen_random_array(LEN,bits)
    ip = sum([a*b for (a,b) in zip(arA,arB)])

    for player,ar in [("A",arA),("B",arB)]:
        pl = str_iv(player, str_struct(["xs"],[ar]))
        fo.write(pl)

    fo.write("return_value == %d;\n" % ip)

def gen_xtabs_input(fo):
    LEN = 50
    BINS = 5
    bits = 8

    # parallel arrays (id, value)
    arA = [gen_random_array(LEN,bits), gen_random_array(LEN,bits)]
    arB = [gen_random_array(LEN, bits), [b % BINS for b in gen_random_array(LEN)]]

    # calculate correct answer
    ID = 0
    VAL = 1
    expected_output = [0] * BINS
    for idA in range(LEN):
        for idB in range(LEN):
            if arA[ID][idA] == arB[ID][idB]:
                expected_output[ arB[VAL][idB] ] += arA[VAL][idA]
    
    # write values 
    for player,ar in [("A",arA),("B",arB)]:
        pl = str_iv(player, str_struct(["d"],[ar]))
        fo.write(pl)

    output = str_struct(["d"], [[eo % 256 for eo in expected_output]])
    fo.write("return_value == %s;\n"%(output))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='generates input for cbmc-gc sample programs')
    #parser.add_argument('-l', default=10, type=int, 
    #    help="array length (for innerprod, xtabs)")
    programs = ["mult3","innerprod","xtabs", "xtabs-hash"]
    parser.add_argument('-e', default="xtabs", choices = programs,
        help="program selection")
    parser.add_argument('-t', default=3, type=int, help="number of trials")
    args = parser.parse_args()

    if args.e == "mult3":
        write_input(args.e, args.t, gen_mult3_input)
    elif args.e == "innerprod":
        write_input(args.e, args.t, gen_innerprod_input)
    elif "xtabs" in args.e:
        write_input(args.e, args.t, gen_xtabs_input)

