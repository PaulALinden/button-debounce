CC = gcc
CXX = g++
CFLAGS = -Wall -Wpedantic -Wextra -Werror -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs -ftest-coverage
BUILD_DIR = build
LIB_DIR = lib/button
TEST_DIR = test/test_button
UNITY_DIR = test/unity
TEST_EXE = test

# Inkluderingsvägar
INCLUDES = -I./$(LIB_DIR) -I./$(TEST_DIR) -I./$(UNITY_DIR)

# Alla .cpp-filer som ska kompileras
OBJECTS = $(BUILD_DIR)/button.o $(BUILD_DIR)/test_bsp.o $(BUILD_DIR)/test.o $(BUILD_DIR)/unity.o

.PHONY: all check clean

all: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "=============== TARGETS ==================="
	@echo "==> clean: to clean the project"
	@echo "==> check: to build and run the test"
	@echo "==========================================="

# Bygg testprogrammet
$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CXX) $(LDFLAGS) $^ -o $@

# Objektfiler
$(BUILD_DIR)/button.o: $(LIB_DIR)/button.cpp $(LIB_DIR)/button.h
	@$(CXX) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(BUILD_DIR)/test_bsp.o: $(TEST_DIR)/bsp.cpp $(TEST_DIR)/bsp.h
	@$(CXX) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(BUILD_DIR)/test.o: $(TEST_DIR)/test.cpp $(TEST_DIR)/bsp.h $(LIB_DIR)/button.h
	@$(CXX) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(BUILD_DIR)/unity.o: $(UNITY_DIR)/unity.cpp $(UNITY_DIR)/unity.h
	@$(CXX) -c $(CFLAGS) $< $(INCLUDES) -o $@

# Kör tester och generera coverage
check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "================================================="
	@echo "================ RUN TEST ======================="
	@echo "================================================="
	@./$(BUILD_DIR)/$(TEST_EXE)
	@gcovr -r . --filter $(LIB_DIR)/button.cpp --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

# Automatiska beroenden
-include $(BUILD_DIR)/*.d


