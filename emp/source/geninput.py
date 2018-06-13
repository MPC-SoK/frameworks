import argparse, random, os

def create_dirs(program):
    dirname = "data/"+program
    if not os.path.exists(dirname):
        try:
            os.makedirs(dirname)
        except OSError as e:
            if e.errno != errno.EEXIST: raise

def gen_input(program, n, l):
    for party in [1,2]:
        with open("data/%s/%d.%s.dat"%(program,n,party),'w') as f:
            for i in range(l):
                x = random.getrandbits(n)
                f.write("%d\n"%x)

def gen_xtabs_input(n, l):
    LEN = l
    IDMAX = min(2 * LEN, 2**n)
    BINS = 5

    with open("data/xtabs/%d.bins.dat"%n,'w') as f:
        for i in range(LEN):
            x = "%d %d\n"%(random.randint(0,IDMAX), random.randint(1, BINS))
            f.write(x)

    with open("data/xtabs/%d.vals.dat"%n,'w') as f:
        for i in range(LEN):
            y = "%d %d\n"%(random.randint(0,IDMAX), random.randint(1,n))
            f.write(y)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='generates input for emp-toolkit sample programs')
    parser.add_argument('-n', default=32, type=int, 
        help="integer bit length")
    parser.add_argument('-l', default=10, type=int, 
        help="array length (for innerprod, xtabs)")
    programs = ["mult3","innerprod","xtabs"]
    parser.add_argument('-e', default="xtabs", choices = programs,
        help="program selection")
    args = parser.parse_args()

    create_dirs(args.e)

    if args.e == "mult3":
        gen_input(args.e, args.n, 3)

    elif args.e == "innerprod":
        gen_input(args.e, args.n, args.l)

    elif args.e == "xtabs":
        gen_xtabs_input(args.n, args.l)


