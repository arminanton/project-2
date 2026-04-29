SHELL := /bin/bash

BUILD_DIR ?= build
BUILD_TYPE ?= Release
EXECUTABLE ?= geopulse
DATASET ?= data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
CMAKE ?= cmake
CTEST ?= ctest
CLANG_FORMAT ?= clang-format
CLANG_TIDY ?= clang-tidy
CPPLINT ?= cpplint

.PHONY: help configure build rebuild test run benchmark clean distclean hooks format lint style tree package lfs-init

help:
	@echo "GeoPulse developer commands"
	@echo "  make configure   Configure the CMake build and export compile commands"
	@echo "  make build       Build the project"
	@echo "  make rebuild     Clean build directory, configure, and build"
	@echo "  make test        Run unit tests"
	@echo "  make run         Run the CLI against DATASET=$(DATASET)"
	@echo "  make benchmark   Run benchmark mode against DATASET=$(DATASET)"
	@echo "  make format      Run clang-format on tracked source files"
	@echo "  make lint        Run clang-format, clang-tidy, and optional cpplint checks"
	@echo "  make hooks       Enable local git hooks from scripts/setup-hooks.sh"
	@echo "  make lfs-init    Enable Git LFS support for snapshot datasets"
	@echo "  make package     Create a zip archive that excludes gitignored files"
	@echo "  make clean       Remove compiled outputs"
	@echo "  make distclean   Remove the full build directory"
	@echo "  make tree        Print the top-level project tree"

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
	$(CMAKE) --build $(BUILD_DIR) --config $(BUILD_TYPE)

rebuild:
	rm -rf $(BUILD_DIR)
	$(MAKE) configure
	$(MAKE) build

test: build
	cd $(BUILD_DIR) && $(CTEST) --output-on-failure

run: build
	./$(BUILD_DIR)/$(EXECUTABLE) --data "$(DATASET)"

benchmark: build
	./$(BUILD_DIR)/$(EXECUTABLE) --data "$(DATASET)" --benchmark

format:
	bash scripts/format.sh

lint:
	bash scripts/check-style.sh

style: format lint

clean:
	$(CMAKE) --build $(BUILD_DIR) --target clean || true

distclean:
	rm -rf $(BUILD_DIR)

hooks:
	bash scripts/setup-hooks.sh

lfs-init:
	git lfs install

package:
	git archive --format=zip --output=geopulse-source.zip HEAD 2>/dev/null || \
		zip -r geopulse-source.zip . -x "*.git*" "build/*" "data/local/*" "*.checkpoint.json" "*.accepted.tsv"

tree:
	@find . -maxdepth 3 | sort
