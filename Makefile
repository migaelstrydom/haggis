.PHONY : all
all:
	mkdir build && ${MAKE} -C src build

.PHONY : clean
clean:
	${MAKE} -C src clean && rm -f *~ && rm -rf build
