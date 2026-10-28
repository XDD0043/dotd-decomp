# crt/

Exact ports of the C runtime pieces that feed the simulation (Dinkumware libm, rand/srand, qsort)
and `ppc_ops.h`, the helpers that reproduce PPC arithmetic exactly (fused multiply-add,
saturating float-to-int, division and shift edge cases).
