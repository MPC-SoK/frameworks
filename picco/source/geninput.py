import argparse, random, os

def create_dirs(program):
    dirname = program+"/data"
    if not os.path.exists(dirname):
        try: os.makedirs(dirname)
        except OSError as e:
            if e.errno != errno.EExist: raise


def gen_mult3_input(n):
    p = 1
    # to do: implement this with 3 separate input parties
    with open("mult3/data/input.A.dat", 'w') as f:
        for var in ["A","B","C"]:
            x = random.getrandbits(n)
            f.write("%s = %d\n"%(var,x))
            p = p * x
    print("expected output: %d"%p)


def gen_ip_input(n, LEN):
    xs = [random.getrandbits(n) for _ in range(LEN)]
    ys = [random.getrandbits(n) for _ in range(LEN)]
    expected = sum([x*y for (x,y) in zip(xs,ys)])
    print("expected output: %d"%expected)

    for party,data in [("A",xs),("B",ys)]:
        with open("innerprod/data/input.%s.dat"%(party), 'w') as f:
            f.write("%s = "%party)
            dw = ",".join(map(str,data))
            f.write("%s\n"%dw)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='generates input for picco sample programs')
    parser.add_argument('-n', default=16, type=int, 
            help="integer bit length")
    parser.add_argument('-l', default=10, type=int, 
            help="array length (for innerprod, xtabs)")

    programs = ["mult3","innerprod","xtabs"]
    parser.add_argument('-e', default="innerprod", choices = programs,
            help="program selection")
    args = parser.parse_args()

    create_dirs(args.e)

    if args.e == "mult3":
        gen_mult3_input(args.n)

    elif args.e == "innerprod":
        gen_ip_input(args.n, args.l)

    elif args.e == "xtabs":
        print("xtabs input gen not implemented")
        #gen_xtabs_input(args.n, args.l)




