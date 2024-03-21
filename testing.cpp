//
// Created by Fawzy on 3/20/2024.
//
#include "testOperator.h"
//#include <gtest/gtest.h>
#include "Logic_Gate.h"
#include "circuit.h"

/*// Helper function to setup a Logic_Gate and evaluate its expression
int testEvaluateExpression(const std::string& expression, const std::vector<std::pair<std::string, int>>& inputs) {
    circuit c;
    Logic_Gate gate("", inputs.size(), 0, expression);
    gate.set_cir_Input_Names(inputs);
    std::vector<Logic_Gate> gates = {gate};
    c.setusedGates(gates);
    return evaluate(c, 0); // Assuming '0' is the index of our gate in usedGates
}

// Test for AND operation
TEST(LogicExpressionTests, TestANDOperation) {
std::vector<std::pair<std::string, int>> inputs = {{"A", 1}, {"B", 1}};
EXPECT_EQ(testEvaluateExpression("A & B", inputs), 1);

inputs = {{"A", 1}, {"B", 0}};
EXPECT_EQ(testEvaluateExpression("A & B", inputs), 0);
}

// Test for OR operation
TEST(LogicExpressionTests, TestOROperation) {
std::vector<std::pair<std::string, int>> inputs = {{"A", 0}, {"B", 0}};
EXPECT_EQ(testEvaluateExpression("A | B", inputs), 0);

inputs = {{"A", 1}, {"B", 0}};
EXPECT_EQ(testEvaluateExpression("A | B", inputs), 1);
}

// Test for NOT operation
TEST(LogicExpressionTests, TestNOTOperation) {
std::vector<std::pair<std::string, int>> inputs = {{"A", 0}};
EXPECT_EQ(testEvaluateExpression("~A", inputs), 1);

inputs = {{"A", 1}};
EXPECT_EQ(testEvaluateExpression("~A", inputs), 0);
}

// Test for combined operations
TEST(LogicExpressionTests, TestCombinedOperations) {
std::vector<std::pair<std::string, int>> inputs = {{"A", 1}, {"B", 0}, {"C", 1}};
EXPECT_EQ(testEvaluateExpression("(A & B) | C", inputs), 1);

inputs = {{"A", 1}, {"B", 1}, {"C", 0}};
EXPECT_EQ(testEvaluateExpression("~((A & B) | C)", inputs), 0);
}
*/