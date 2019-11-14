package dk.alexandra.fresco.samples;

import dk.alexandra.fresco.framework.builder.numeric.ProtocolBuilderNumeric;
import dk.alexandra.fresco.framework.configuration.NetworkConfiguration;
import dk.alexandra.fresco.framework.network.AsyncNetwork;
import dk.alexandra.fresco.framework.network.CloseableNetwork;
import dk.alexandra.fresco.framework.sce.SecureComputationEngine;
import dk.alexandra.fresco.framework.sce.SecureComputationEngineImpl;
import dk.alexandra.fresco.framework.sce.evaluator.BatchedProtocolEvaluator;
import dk.alexandra.fresco.framework.sce.evaluator.BatchedStrategy;
import dk.alexandra.fresco.framework.util.AesCtrDrbg;
import dk.alexandra.fresco.framework.util.Drbg;
import dk.alexandra.fresco.framework.util.ModulusFinder;
import dk.alexandra.fresco.framework.util.OpenedValueStoreImpl;
import dk.alexandra.fresco.suite.spdz.SpdzProtocolSuite;
import dk.alexandra.fresco.suite.spdz.SpdzResourcePool;
import dk.alexandra.fresco.suite.spdz.SpdzResourcePoolImpl;
import dk.alexandra.fresco.suite.spdz.storage.SpdzDataSupplier;
import dk.alexandra.fresco.suite.spdz.storage.SpdzDummyDataSupplier;
import dk.alexandra.fresco.suite.spdz.storage.SpdzMascotDataSupplier;
import dk.alexandra.fresco.tools.mascot.field.FieldElement;
import dk.alexandra.fresco.tools.ot.otextension.RotList;
import java.math.BigInteger;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * A TestSetup using the SPDZ protocol suite to run MPC computations. This will use dummy
 * preprocessing.
 */
public class SpdzParty {

  private final NetworkConfiguration netConf;
  private final SpdzResourcePool resourcePool;
  private final SecureComputationEngine<SpdzResourcePool, ProtocolBuilderNumeric> sce;

  /**
   * Constructs a SpdzTestSetup given the required resources.
   *
   * @param netConf a network configuration
   * @param resourcePool a SpdzResourcePool
   * @param sce an sce
   */
  public SpdzParty(NetworkConfiguration netConf, SpdzResourcePool resourcePool,
      SecureComputationEngine<SpdzResourcePool, ProtocolBuilderNumeric> sce) {
    this.netConf = netConf;
    this.resourcePool = resourcePool;
    this.sce = sce;
  }

  /**
   * Returns a new {@link Builder} used to build tests setups for a given number of parties.
   *
   * @param parties the number of parties.
   * @return a new Builder
   */
  public static Builder builder(NetworkConfiguration netConf) {
    return new Builder(netConf);
  }

  public NetworkConfiguration getNetConf() {
    return netConf;
  }

  public CloseableNetwork getNetwork() {
    return new AsyncNetwork(netConf);
  }

  public SpdzResourcePool getRp() {
    return resourcePool;
  }

  public SecureComputationEngine<SpdzResourcePool, ProtocolBuilderNumeric> getSce() {
    return sce;
  }

  /**
   * Builder class used to configure and build test setups for a set of parties.
   */
  public static class Builder {

    private static final int DEFAULT_MOD_BIT_LENGTH = 128;
    private static final int DEFAULT_MAX_BIT_LENGTH = 64;
    private static final byte[] DEFAULT_SEED = new byte[32];

    private int maxLength = DEFAULT_MAX_BIT_LENGTH;
    private int modLength = DEFAULT_MOD_BIT_LENGTH;
    private byte[] seed = DEFAULT_SEED;
    private NetworkConfiguration netConf;
    private int fixedPointLength = -1;

    public Builder(NetworkConfiguration netConf) {
      this.netConf = netConf;
    }

    public Builder modLength(int modLength) {
      this.modLength = modLength;
      return this;
    }

    public Builder maxLength(int maxLength) {
      this.maxLength = maxLength;
      return this;
    }

    public Builder fixedPointLength(int fixedPointLength) {
      this.fixedPointLength = fixedPointLength;
      return this;
    }

    /**
     * Builds test setups for a number of parties using the specified parameters or default values
     * if none are given.
     *
     * @return a Map from party id to test setup
     */
    public SpdzParty build() {
      this.fixedPointLength = fixedPointLength == -1 ? maxLength / 8 : fixedPointLength;
      SpdzDummyDataSupplier supplier = new SpdzDummyDataSupplier(netConf.getMyId(),
          netConf.noOfParties(), ModulusFinder.findSuitableModulus(modLength));
      SpdzResourcePool rp = new SpdzResourcePoolImpl(netConf.getMyId(), netConf.noOfParties(),
          new OpenedValueStoreImpl<>(), supplier, new AesCtrDrbg(seed));
      SpdzProtocolSuite suite = new SpdzProtocolSuite(maxLength, fixedPointLength);
      BatchedProtocolEvaluator<SpdzResourcePool> evaluator =
          new BatchedProtocolEvaluator<>(new BatchedStrategy<>(), suite);
      SecureComputationEngine<SpdzResourcePool, ProtocolBuilderNumeric> sce =
          new SecureComputationEngineImpl<>(suite, evaluator);
      SpdzParty party = new SpdzParty(netConf, rp, sce);
      return party;
    }

    private SpdzDataSupplier createMascotSupplier() {
      List<Integer> partyIds = IntStream.range(1, netConf.noOfParties() + 1).boxed().collect(Collectors.toList());
      int PRG_SEED_LENGTH = 265;
      Drbg drbg = new AesCtrDrbg();
      BigInteger modulus = ModulusFinder.findSuitableModulus(this.modLength);
      Map<Integer, RotList> seedOts =
          getSeedOts(netConf.getMyId(), partyIds, PRG_SEED_LENGTH, drbg, new AsyncNetwork(netConf));
      FieldElement ssk = SpdzMascotDataSupplier.createRandomSsk(modulus, PRG_SEED_LENGTH);
      /*
      supplier = SpdzMascotDataSupplier.createSimpleSupplier(myId, numberOfParties,
          () -> tripleGenerator.createExtraNetwork(myId), modBitLength, modulus,
          new Function<Integer, SpdzSInt[]>() {

            private SpdzMascotDataSupplier tripleSupplier;
            private CloseableNetwork pipeNetwork;

            @Override
            public SpdzSInt[] apply(Integer pipeLength) {
              if (pipeNetwork == null) {
                pipeNetwork = expPipeGenerator.createExtraNetwork(myId);
                tripleSupplier = SpdzMascotDataSupplier.createSimpleSupplier(myId, numberOfParties,
                    () -> pipeNetwork, modBitLength, modulus, null, seedOts, drbg, ssk);
              }
              DRes<List<DRes<SInt>>> pipe =
                  createPipe(myId, numberOfParties, pipeLength, pipeNetwork, tripleSupplier);
              return computeSInts(pipe);
            }
          }, seedOts, drbg, ssk);
          */
      return null;
    }

    /**

     * @return
     */
    private Map<Integer, RotList> getSeedOts(int myId, List<Integer> partyIds, int seedLength,
        Drbg drbg, AsyncNetwork asyncNetwork) {
      // TODO Auto-generated method stub
      return null;
    }
  }
}
