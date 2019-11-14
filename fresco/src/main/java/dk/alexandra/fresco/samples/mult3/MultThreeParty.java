package dk.alexandra.fresco.samples.mult3;

import static dk.alexandra.fresco.samples.Id.*;

import dk.alexandra.fresco.framework.Party;
import dk.alexandra.fresco.framework.configuration.NetworkConfiguration;
import dk.alexandra.fresco.framework.configuration.NetworkConfigurationImpl;
import dk.alexandra.fresco.framework.network.CloseableNetwork;
import dk.alexandra.fresco.samples.SpdzParty;
import java.io.IOException;
import java.util.HashMap;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
   Runs the mult3 demo.
*/
public class MultThreeParty {

  private static final Logger logger = LoggerFactory.getLogger(MultThreeParty.class);

  private static final int FACTOR_A = 10;
  private static final int FACTOR_B = 20;
  private static final int FACTOR_C = 30;

  public static void main(String[] args) throws IOException {
    int partyId = partyIdFromArgs(args);
    logInfo();
    SpdzParty party = setupSpdz(partyId);
    CloseableNetwork net = party.getNetwork();
    int result;
    if (partyId == ALICE.id()) {
      result = party.getSce().runApplication(new MultThree(FACTOR_A),  party.getRp(), net);
    } else if (partyId == BOB.id()) {
      result = party.getSce().runApplication(new MultThree(FACTOR_B),  party.getRp(), net);
    } else if (partyId == CAROL.id()) {
      result = party.getSce().runApplication(new MultThree(FACTOR_C),  party.getRp(), net);
    } else {
      throw new IndexOutOfBoundsException("Party id should be 1, 2 or 3, but was " + partyId);
    }
    party.getSce().shutdownSCE();
    net.close();
    logger.info("Got result: " + result);
  }

  private static SpdzParty setupSpdz(int partyId) {
    HashMap<Integer, Party> parties = new HashMap<>(3);
    parties.put(1, new Party(ALICE.id(), "localhost", 12000));
    parties.put(2, new Party(BOB.id(), "localhost", 12001));
    parties.put(3, new Party(CAROL.id(), "localhost", 12002));
    NetworkConfiguration netConf = new NetworkConfigurationImpl(partyId, parties);
    SpdzParty party = SpdzParty.builder(netConf).build();
    return party;
  }

  /**
   * Parses arguments in order to get the party id
   *
   * @param args command line arguments
   * @return the party id of this party
   */
  private static int partyIdFromArgs(String[] args) {
    int myId = -1;
    if (args.length != 1) {
      throw new IllegalArgumentException("A single argument is needed indicating the party id. Arguments given were \"" + String.join(" ", args) + "\"");
    }
    try {
      myId = Integer.parseInt(args[0]);
    } catch (NumberFormatException e) {
      throw new IllegalArgumentException("Could not parse argument \"" + args[0] + "\" as an integer (this argument should specify the party id)");
    }
    if (!(myId == 1 || myId == 2 || myId == 3)) {
      throw new IndexOutOfBoundsException("Party id must be either 1, 2 or 3, but was " + myId);
    }
    return myId;
  }

  private static void logInfo() {
    StringBuilder sb = new StringBuilder();
    sb.append("\n"
        +
        "    __________  ___________ __________     __  ___      ____ _____    ____\n" +
        "   / ____/ __ \\/ ____/ ___// ____/ __ \\   /  |/  /_  __/ / /|__  /   / __ \\___  ____ ___  ____\n" +
        "  / /_  / /_/ / __/  \\__ \\/ /   / / / /  / /|_/ / / / / / __//_ <   / / / / _ \\/ __ `__ \\/ __ \\\n" +
        " / __/ / _, _/ /___ ___/ / /___/ /_/ /  / /  / / /_/ / / /____/ /  / /_/ /  __/ / / / / / /_/ /\n" +
        "/_/   /_/ |_/_____//____/\\____/\\____/  /_/  /_/\\__,_/_/\\__/____/  /_____/\\___/_/ /_/ /_/\\____/\n");
    sb.append("\nComputing Mult3 on inputs:\n");
    sb.append("Factor a: " + FACTOR_A + "\n");
    sb.append("Factor b: " + FACTOR_B + "\n");
    sb.append("Factor c: " + FACTOR_C + "\n");
    logger.info("{}", sb.toString());
  }

}
