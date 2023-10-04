RISCV=/home/abal # Directory of tools

compile: 
	meson compile -C builddir

install:
	meson install -C builddir
	
build:
	meson setup builddir --native-file native-file.txt --buildtype release -Dspike_install_dir=${RISCV} --prefix /home/abal/hammer
	meson install -C builddir
	meson compile -C builddir

clean:
	rm -r include lib builddir 