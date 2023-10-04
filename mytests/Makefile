testcase ?= vadd
SEW?= 8
AVL?= 10
VLEN ?=64
COMP_OPTS = -static -mcmodel=medany -std=gnu99 -O2 -ffast-math -O2 -fno-common -Wall -march=rv32imacv
LINK_OPTS = -static -nostdlib -nostartfiles -lm -lgcc -T link.ld

compile_test: vadd_test.cpp compile_testcase
	cd "/home/abal/hammer"; meson compile -C "./builddir"

compile_testcase: ${testcase}.c ${testcase}.S
	python3 change_AVL.py ${testcase}.c ${AVL}
	riscv32-unknown-elf-gcc -o ${testcase} ${testcase}.c ${testcase}.S ${COMP_OPTS} ${LINK_OPTS}
	riscv32-unknown-elf-objdump -D ${testcase} > ${testcase}.dasm

simulate_py:
	python3 calc_speed_interactive.py ${testcase}.dasm ${testcase} ${SEW} ${AVL} ${VLEN}
	