package dk.alexandra.fresco.samples.innerproduct;

import dk.alexandra.fresco.framework.Application;
import dk.alexandra.fresco.framework.DRes;
import dk.alexandra.fresco.framework.builder.numeric.ProtocolBuilderNumeric;
import dk.alexandra.fresco.framework.value.SInt;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
   Defines the MPC computation to input private values, compute the inner
   product, and output the result to all parties.
 */
public class InnerProduct implements Application<Integer, ProtocolBuilderNumeric> {

  private final List<BigInteger> vector;

  /**
     Constructs a new MPC computation for inner product using a given list of
     integers as the vector of this party.
   */    
  public InnerProduct(List<Integer> vector) {
    this.vector = vector.stream().map(BigInteger::valueOf).collect(Collectors.toList());
  }

  @Override
  public DRes<Integer> buildComputation(ProtocolBuilderNumeric builder) {
    List<DRes<SInt>> sVec1 = new ArrayList<>(vector.size());
    List<DRes<SInt>> sVec2 = new ArrayList<>(vector.size());
    for (int i = 0; i < vector.size(); i++) {
      // Note: the below is a bit of a cheat as we are inputting the same vector
      // for both party 1 and 2. This works because if we are not party i our
      // input for party i will be disregarded.
      sVec1.add(builder.numeric().input(vector.get(i), 1));
      sVec2.add(builder.numeric().input(vector.get(i), 2));
    }
    DRes<SInt> result = builder.advancedNumeric().innerProduct(sVec1, sVec2);
    DRes<BigInteger> openResult = builder.numeric().open(result);
    return () -> openResult.out().intValue();
  }

}
