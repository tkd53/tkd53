TARGETS_DIR = ../../bin
TARGETS = bigram.o bigram_converter.o lattice.o lattice_builder.o

TESTS_INSTALL_DIR = ../../tests/bin/converter
GTEST_OBJ_DIR = ${TESTS_INSTALL_DIR}/../gtest
GTEST_DIR = ../third_party/googletest/googletest
GTEST_DEPS = ${GTEST_OBJ_DIR}/libgtest_main.a ${GTEST_OBJ_DIR}/libgtest.a

CXX=g++
# CXX = clang++
WARNING_OPTIONS = -Wall -Wextra -Woverloaded-virtual -Werror -Weffc++ # -fcolor-diagnostics
INCLUDE_OPTIONS = -I../ -I${GTEST_DIR}/include/
CXXFLAGS = $(WARNING_OPTIONS) $(INCLUDE_OPTIONS) -std=c++11
TEST_CXXFLAGS = $(INCLUDE_OPTIONS) -std=c++11

TEST_SOURCES = $(wildcard *_test.cpp)

TESTS = $(patsubst %_test.cpp, ${TESTS_INSTALL_DIR}/%_test, $(TEST_SOURCES))


all:${TARGETS_DIR} $(TARGETS)

test: ${TESTS_INSTALL_DIR} ${TESTS}

clean:
	rm -rf  ../base/*.o ./*.o ${TESTS} ${TESTS_INSTALL_DIR} ${TARGETS}

${TARGETS_DIR}:
	@mkdir -p $@

${TESTS_INSTALL_DIR}:
	@mkdir -p $@

%_test.o: %_test.cpp
	$(CXX) -o $@ -c $< $(TEST_CXXFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

../base/%.o: ../base/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

${TESTS_INSTALL_DIR}/bigram_test:bigram_test.o bigram.o ${GTEST_DEPS}
	$(CXX) -o $@ $^ -lpthread
