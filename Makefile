RISCV=/home/abal # Directory of RISCV tools

compile: 
	meson compile -C builddir

build:
	meson setup builddir --native-file native-file.txt --buildtype release -Dspike_install_dir=${RISCV}
	meson compile -C builddir	

clean:
	rm -r include lib builddir 

# build_install:
# 	meson setup builddir --native-file native-file.txt --buildtype release -Dspike_install_dir=${RISCV} --prefix SOMEPATH
# 	meson install -C builddir
# 	meson compile -C builddir