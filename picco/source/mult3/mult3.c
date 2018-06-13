/*
 * multiplies three inputs
 */

public int main() {

    private int<16> A, B, C;

    // to do: input from separate parties
    smcinput(A,1);
    smcinput(B,1);
    smcinput(C,1);

    private int<48> p;
    p = A * B * C;

    smcoutput(p,1);
    return 0;

}
