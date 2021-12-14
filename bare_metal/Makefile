PROJECT_NAME = explorer_power_test
EXECUTABLE = build/${PROJECT_NAME}.xe
BOARD ?= XCORE-AI-EXPLORER

CMAKE_ADD_ARGS = -DBOARD=$(BOARD)

.PHONY: all clean distclean $(EXECUTABLE)

all: $(EXECUTABLE)

clean:
	rm -rf build

distclean:
	rm -rf build
	rm -rf bin

$(EXECUTABLE):
	cmake -B build $(CMAKE_ADD_ARGS)
	cd build && make -j
