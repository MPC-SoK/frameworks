CBMC_GC = cbmc-gc
CIRCUIT_SIM = circuit-sim
ABY_CBMC_GC = ../../../ABY/bin/aby-cbmc-gc.exe

.PHONY: clean run-sim run-aby

output.gate.txt: main.c
	$(CBMC_GC) $^ --minimization-time-limit 10

run-sim:
	@$(CIRCUIT_SIM) --spec-file test.spec

run-aby:
	@$(ABY_CBMC_GC) -r 0 --spec "INPUT_B := 35; print;" &
	@$(ABY_CBMC_GC) -r 1 --spec "INPUT_A := 25; print;"
	@$(ABY_CBMC_GC) -r 1 --spec "INPUT_C := 2; print;"

clean:
	rm -f output.*.txt
