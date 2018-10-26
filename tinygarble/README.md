TinyGarble is an implementation of Yao's garbled circuits, developed by
researchers at Rice University and TU Darmstadt.

TinyGarble extends Verilog, a hardware circuit description language, to generate
highly optimized circuits for use in Yao's garbled circuit protocol.
It requires the Synopsys Design Compiler, which is not open source. 

We were unable to produce any working examples. This Docker instance downloads and builds the TinyGarble source code. You can run computations on pre-compiled circuits following the [provided TinyGarble documentation](https://github.com/esonghori/TinyGarble#run-an-example).

We tested using an older version of the code from October 2017 and we revert the repository to the most recent branch we tested. However, TinyGarble is under active development and we are hopeful that it will eventually be compatible with open-source tools.

