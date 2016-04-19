TARGETS_DIR = ../../bin
TARGETS = engine.o

TESTS_INSTALL_DIR = ../../tests/bin/engine
GTEST_OBJ_DIR = ${TESTS_INSTALL_DIR}/../gtest
GTEST_DIR = ../third_party/googletest/googletest
GTEST_DEPS = ${GTEST_OBJ_DIR}/libgtest_main.a ${GTEST_OBJ_DIR}/libgtest.a

CXX=g++
#CXX = clang++
WARNING_OPTIONS = -Wall -Wextra -Weffc++ -Woverloaded-virtual -Werror # -fcolor-diagnostics
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

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

%_test.o: %_test.cpp
	$(CXX) -o $@ -c $< $(TEST_CXXFLAGS)

../base/%.o: ../base/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

${TESTS_INSTALL_DIR}/engine_test:engine_test.o ../converter/bigram_converter.o ../converter/bigram.o ../dictionary/map_dictionary.o ../converter/lattice.o ../converter/lattice_builder.o engine.o ${GTEST_DEPS}
	$(CXX) -o $@ $^ -lpthread
