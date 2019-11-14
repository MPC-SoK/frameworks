package dk.alexandra.fresco.samples.innerproduct;

import static dk.alexandra.fresco.samples.Id.*;

import dk.alexandra.fresco.framework.Party;
import dk.alexandra.fresco.framework.configuration.NetworkConfiguration;
import dk.alexandra.fresco.framework.configuration.NetworkConfigurationImpl;
import dk.alexandra.fresco.framework.network.CloseableNetwork;
import dk.alexandra.fresco.samples.SpdzParty;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
   Runs the inner product demo.
 */
public class InnerProductParty {

  private static final List<Integer> ALICE_VECTOR = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  private static final List<Integer> BOB_VECTOR = Arrays.asList(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);

  private static final Logger logger = LoggerFactory.getLogger(InnerProductParty.class);

  public static void main(String[] args) throws IOException {
    int partyId = partyIdFromArgs(args);
    logInfo();
    HashMap<Integer, Party> parties = new HashMap<>();
    parties.put(ALICE.id(), new Party(ALICE.id(), "localhost", 12000));
    parties.put(BOB.id(), new Party(BOB.id(), "localhost", 12001));
    NetworkConfiguration netConf = new NetworkConfigurationImpl(partyId, parties);
    SpdzParty party = SpdzParty.builder(netConf).build();
    CloseableNetwork net = party.getNetwork();
    int result;
    if (partyId == 1) {
      result = party.getSce().runApplication(new InnerProduct(ALICE_VECTOR),  party.getRp(), net);
    } else {
      result = party.getSce().runApplication(new InnerProduct(BOB_VECTOR),  party.getRp(), net);
    }
    party.getSce().shutdownSCE();
    net.close();
    logger.info("Got result: {}", result);
  }

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
    if (!(myId == ALICE.id() || myId == BOB.id())) {
      throw new IndexOutOfBoundsException("Party id must be either 1 or 2, but was " + myId);
    }
    return myId;
  }

  private static void logInfo() {
    StringBuilder sb = new StringBuilder();
    sb.append("\n"
        +
        "    __________  ___________ __________\n" +
        "   / ____/ __ \\/ ____/ ___// ____/ __ \\\n" +
        "  / /_  / /_/ / __/  \\__ \\/ /   / / / /\n" +
        " / __/ / _, _/ /___ ___/ / /___/ /_/ /\n" +
        "/_/   /_/ |_/_____//____/\\____/\\____/\n" +
        "\n" +
        "    ____                                           __           __     ____\n" +
        "   /  _/___  ____  ___  _________  _________  ____/ /_  _______/ /_   / __ \\___  ____ ___  ____\n" +
        "   / // __ \\/ __ \\/ _ \\/ ___/ __ \\/ ___/ __ \\/ __  / / / / ___/ __/  / / / / _ \\/ __ `__ \\/ __ \\\n" +
        " _/ // / / / / / /  __/ /  / /_/ / /  / /_/ / /_/ / /_/ / /__/ /_   / /_/ /  __/ / / / / / /_/ /\n" +
        "/___/_/ /_/_/ /_/\\___/_/  / .___/_/   \\____/\\__,_/\\__,_/\\___/\\__/  /_____/\\___/_/ /_/ /_/\\____/\n" +
        "                         /_/\n");
    sb.append("\nComputing innerproduct on inputs:\n");
    sb.append("Vector a: " + ALICE_VECTOR + "\n");
    sb.append("Vector b: " + BOB_VECTOR + "\n");
    logger.info("{}", sb.toString());
  }

}
