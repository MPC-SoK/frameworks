package dk.alexandra.fresco.samples.xtabs;

import static dk.alexandra.fresco.samples.Id.*;

import dk.alexandra.fresco.framework.Party;
import dk.alexandra.fresco.framework.configuration.NetworkConfiguration;
import dk.alexandra.fresco.framework.configuration.NetworkConfigurationImpl;
import dk.alexandra.fresco.framework.network.CloseableNetwork;
import dk.alexandra.fresco.samples.SpdzParty;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
   Runs the xtabs demo.
*/
public class XtabsParty {

  private static final int[] ALICE_IDS = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  private static final int[] BOB_IDS = new int[] { 3, 60, 11, 1, 5, 42, 10, 8, 100, 7 };
  private static final int[] BINS = new int[] { 1, 1, 1, 2, 0, 3, 4, 0, 0, 1 };
  private static final int[] VALUES = new int[] { 20, 2, 1, 30, 80, 1, 150, 20, 3, 500 };

  private static final Logger logger = LoggerFactory.getLogger(XtabsParty.class);

  public static void main(String[] args) throws IOException {
    int partyId = partyIdFromArgs(args);
    logInfo();
    HashMap<Integer, Party> parties = new HashMap<>();
    parties.put(ALICE.id(), new Party(ALICE.id(), "localhost", 12000));
    parties.put(BOB.id(), new Party(BOB.id(), "localhost", 12001));
    NetworkConfiguration netConf = new NetworkConfigurationImpl(partyId, parties);
    SpdzParty party = SpdzParty.builder(netConf).build();
    CloseableNetwork net = party.getNetwork();
    List<Integer> result;
    if (partyId == ALICE.id()) {
      result = party.getSce().runApplication(
          Xtabs.getAliceInstance(ALICE_IDS, BINS), party.getRp(), net);
    } else {
      result = party.getSce().runApplication(
          Xtabs.getBobInstance(BOB_IDS, VALUES), party.getRp(), net);
    }
    party.getSce().shutdownSCE();
    net.close();
    logger.info("Got result: " + result);
  }

  private static void logInfo() {
    StringBuilder sb = new StringBuilder();
    sb.append("\n"
        + "_   ____________  ___________ __________     _  ________      __            ____\n" +
        "__  _/ ____/ __ \\/ ____/ ___// ____/ __ \\   | |/ /_  __/___ _/ /_  _____   / __ \\___  ____ ___  ____\n" +
        " __ / /_  / /_/ / __/  \\__ \\/ /   / / / /   |   / / / / __ `/ __ \\/ ___/  / / / / _ \\/ __ `__ \\/ __ \\\n" +
        "_  / __/ / _, _/ /___ ___/ / /___/ /_/ /   /   | / / / /_/ / /_/ (__  )  / /_/ /  __/ / / / / / /_/ /\n" +
        "__/_/   /_/ |_/_____//____/\\____/\\____/   /_/|_|/_/  \\__,_/_.___/____/  /_____/\\___/_/ /_/ /_/\\____/\n");
    sb.append("\nComputing xtabs on input:\n");
    sb.append(String.format("%1$10s", "ID A |"));
    sb.append(String.format("%1$10s", "BIN |"));
    sb.append(String.format("%1$10s", "ID B |"));
    sb.append(String.format("%1$10s", "VALUE |\n"));
    sb.append("=======================================\n");
    for (int i = 0; i < ALICE_IDS.length; i++) {
      sb.append(String.format("%1$10s", ALICE_IDS[i] + " |"));
      sb.append(String.format("%1$10s", BINS[i] + " |"));
      sb.append(String.format("%1$10s", BOB_IDS[i] + " |"));
      sb.append(String.format("%1$10s", VALUES[i] + " |\n"));
    }
    logger.info("{}", sb.toString());
  }

  private static int partyIdFromArgs(String[] args) {
    int partyId = -1;
    if (args.length < 1) {
      throw new IllegalArgumentException(
          "Missing arguments. A single argument is needed indicating the party id as an integer (1 or 2). "
              + "No arguments given");
    } else if (args.length > 1) {
      throw new IllegalArgumentException(
          "Too many arguments. A single argument is needed indicating the party id as an integer (1 or 2). "
              + "Arguments given were: " + String.join(" ", args));

    }
    try {
      partyId = Integer.parseInt(args[0]);
    } catch (NumberFormatException e) {
      throw new IllegalArgumentException("Malformed arguments. A single argument is needed "
          + "indicating the party id as an integer (1 or 2). Argument given \"" + args[0] + "\"",
          e);
    }
    if (!(partyId == ALICE.id() || partyId == BOB.id())) {
      throw new IllegalArgumentException(
          "Party id out of range. A single argument is needed indicating the party id"
              + " as an integer (1 or 2). The argument given was \"" + partyId + "\"");
    }
    return partyId;
  }

}
