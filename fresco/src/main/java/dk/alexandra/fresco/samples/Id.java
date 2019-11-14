package dk.alexandra.fresco.samples;

public enum Id {

    ALICE(1), BOB(2), CAROL(3);

    private int myId;

    Id(int myId) {
      this.myId = myId;
    }

    public int id() {
      return myId;
  }

}
