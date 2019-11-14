package dk.alexandra.fresco.samples.xtabs;

import static dk.alexandra.fresco.samples.Id.*;

import dk.alexandra.fresco.framework.Application;
import dk.alexandra.fresco.framework.DRes;
import dk.alexandra.fresco.framework.builder.numeric.Comparison;
import dk.alexandra.fresco.framework.builder.numeric.Numeric;
import dk.alexandra.fresco.framework.builder.numeric.ProtocolBuilderNumeric;
import dk.alexandra.fresco.framework.value.SInt;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
   Defines the MPC computation to input the private values, compute the xtabs
   computation and output the result to all parties.
 */
public class Xtabs implements Application<List<Integer>, ProtocolBuilderNumeric> {

  /**
   * The number of bins.
   */
  public static final int NUM_BINS = 5;

  /**
   * The number of bits required to represent a bin label (0-4)
   */
  public static final int BIN_LABEL_BITS = 4;

  /**
   * The number of bits required to represent an id (this is not specified in the criteria for
   * sample programs but seems a reasonable upper bound)
   */
  public static final int ID_BITS = 10;

  private int[] ids;
  private int[] values;
  private int[] bins;
  private int partyId;

  private Xtabs(int partyId, int[] ids, int[] values, int[] bins) {
    this.ids = ids;
    this.values = values;
    this.bins = bins;
    this.partyId = partyId;
  }

  public static Xtabs getAliceInstance(int[] ids, int[] bins) {
    return new Xtabs(ALICE.id(), ids, null, bins);
  }

  public static Xtabs getBobInstance(int[] ids, int[] values) {
    return new Xtabs(BOB.id(), ids, values, null);
  }

  @Override
  public DRes<List<Integer>> buildComputation(ProtocolBuilderNumeric builder) {
    if (partyId != builder.getBasicNumericContext().getMyId()) {
      throw new IllegalStateException("This party should be run with id " + partyId
          + " but is using id " + builder.getBasicNumericContext().getMyId());
    }
    Numeric numeric = builder.numeric();
    // Input id columns from both parties
    List<DRes<SInt>> aliceIds = new ArrayList<>();
    List<DRes<SInt>> bobIds = new ArrayList<>();
    for (int i : ids) {
      DRes<SInt> idA = numeric.input(BigInteger.valueOf(i), ALICE.id());
      DRes<SInt> idB = numeric.input(BigInteger.valueOf(i), BOB.id());
      aliceIds.add(idA);
      bobIds.add(idB);
    }
    // Input bin and value columns
    List<DRes<SInt>> binsList = new ArrayList<>();
    List<DRes<SInt>> valuesList = new ArrayList<>();
    for (int i = 0; i < ids.length; i++) {
      BigInteger bin = (partyId == ALICE.id()) ? BigInteger.valueOf(bins[i]) : BigInteger.ZERO;
      DRes<SInt> sBin = builder.numeric().input(bin, ALICE.id());
      binsList.add(sBin);
      BigInteger value = (partyId == BOB.id()) ? BigInteger.valueOf(values[i]) : BigInteger.ZERO;
      DRes<SInt> sValue = builder.numeric().input(value, BOB.id());
      valuesList.add(sValue);
    }
    // Initialize bin labels and sums
    List<DRes<SInt>> binLabels = new ArrayList<>(NUM_BINS);
    List<DRes<SInt>> binSums = new ArrayList<>(NUM_BINS);
    for (int i = 0; i < NUM_BINS; i++) {
      binLabels.add(numeric.known(BigInteger.valueOf(i)));
      binSums.add(numeric.known(BigInteger.ZERO));
    }
    // Compute bin sums
    Comparison comparison = builder.comparison();
    for (int i = 0; i < aliceIds.size(); i++) {
      DRes<SInt> idA = aliceIds.get(i);
      List<DRes<SInt>> indexVector = new ArrayList<>(binLabels.size());
      for (DRes<SInt> label : binLabels) {
        indexVector.add(comparison.equals(BIN_LABEL_BITS, binsList.get(i), label));
      }
      for (int j = 0; j < bobIds.size(); j++) {
        DRes<SInt> idB = bobIds.get(j);
        DRes<SInt> idMatch = comparison.equals(ID_BITS, idA, idB);
        DRes<SInt> term = numeric.mult(idMatch, valuesList.get(j));
        for (int k = 0; k < binLabels.size(); k++) {
          DRes<SInt> indexterm = numeric.mult(indexVector.get(k), term);
          binSums.set(k, numeric.add(indexterm, binSums.get(k)));
        }
      }
    }
    // Output bin sums
    List<DRes<BigInteger>> binSumOuts = new ArrayList<>();
    for (DRes<SInt> sum : binSums) {
      binSumOuts.add(numeric.open(sum));
    }
    // Unwrap results
    return () -> binSumOuts.stream().map(DRes::out).map(BigInteger::intValue)
        .collect(Collectors.toList());
  }

}
