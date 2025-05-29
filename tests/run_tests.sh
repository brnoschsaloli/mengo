#!/bin/bash

echo "Running Mengo Language Tests"
echo "==========================="

# Function to run a test
run_test() {
    echo -e "\nRunning test: $1"
    echo "------------------------"
    ../mengo "$1" < entradas.txt
    echo "------------------------"
}

# Run all tests
run_test "arithmetic.fla"
run_test "logical.fla"
run_test "control_flow.fla"
run_test "lists.fla"
run_test "io.fla"

echo -e "\nAll tests completed!" 