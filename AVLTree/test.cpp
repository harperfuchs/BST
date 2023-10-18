/*#include "../src/tree_structure.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "stdlib.h"
#include <string>
*/
/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/
/*
TEST_CASE("BST InOrder with left rotation", "[flag]"){
        AVLTree tree;   // Create a Tree object
        tree.insert("a", "12345678");
        tree.insert("b", "23456789");
        tree.insert("c", "34567890");
        std::vector<string> actualOutput = tree.printAsVector("in");
        std::vector<string> expectedOutput = {"a", "b", "c"};
        REQUIRE(expectedOutput.size() == actualOutput.size());
        REQUIRE(actualOutput == expectedOutput);
	REQUIRE(1 == 1);
}

// edge cases
TEST_CASE("BST Remove node by id that doesnt exist", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "34567890");
    string actualOutput = tree.removeID("11111111");
    string expectedOutput = {"unsuccessful"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
    REQUIRE(1 == 1);
}

TEST_CASE("BST Remove nth node that doesnt exist", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "34567890");
    string actualOutput = tree.removeInorderN(3);
    string expectedOutput = {"unsuccessful"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
    REQUIRE(1 == 1);
}

TEST_CASE("BST Search Name w multiple of name", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "34567890");
    tree.insert("a", "45678901");
    string actualOutput = tree.searchNAME("a");
    string expectedOutput = {"12345678\n45678901\n"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
    REQUIRE(1 == 1);
}

TEST_CASE("BST print postorder", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "33766449");
    tree.insert("c", "87654321");
    vector<string> actualOutput = tree.printAsVector("post");
    vector<string> expectedOutput = {"a", "c", "b"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST insert all 0s for id", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "00000000");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}


TEST_CASE("BST remove root", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "34567890");
    tree.insert("d", "45678901");
    tree.removeID("23456789");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a", "c", "d"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

// incorrect commands

TEST_CASE("BST remove in order in tree with no nodes", "[flag]"){
    AVLTree tree;
    string actualOutput = tree.removeInorderN(3);
    string expectedOutput = "unsuccessful";
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST remove in tree with no nodes", "[flag]"){
    AVLTree tree;
    string actualOutput = tree.removeID("11111111");
    string expectedOutput = "unsuccessful";
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST search in tree with no nodes", "[flag]"){
    AVLTree tree;
    string actualOutput = tree.searchID("22222222");
    string expectedOutput = "unsuccessful";
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST Insert non-letter char in name", "[flag]"){
    AVLTree tree;
    tree.insert("/", "33766449");
    tree.insert("h8ter", "11111111");
    tree.insert("!happy", "11223344");
    tree.insert("hi girly", "77777777"); // this one should work
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"hi girly"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST insert invalid length", "[flag]"){
    AVLTree tree;
    tree.insert("a", "123456789");
    tree.insert("b", "1234");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST insert duplicate IDs", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "12345678");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST search for id not in tree", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "11111111");
    string actualOutput = tree.searchID("22222222");
    string expectedOutput = "unsuccessful";
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST search for name not in tree", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "23456789");
    string actualOutput = tree.searchNAME("b");
    string expectedOutput = "unsuccessful";
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

// --> 4/4 ROTATION CASES <--
TEST_CASE("BST rotate left", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "34567890");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a", "b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST rotate right", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "98765432");
    tree.insert("b", "87654321");
    tree.insert("c", "12345678");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"c", "b", "a"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST lr rotation", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "11112222");
    tree.insert("c", "87654321");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"b", "a", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST rl rotation", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "99996666");
    tree.insert("c", "11117777");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"c", "a", "b"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

// delete cases (4 cases) for both delete id and delete nth
TEST_CASE("BST delete nth w no child", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.removeInorderN(0);
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete nth w one kid left", "[flag]") {
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.insert("d", "11112222");
    tree.removeInorderN(1);
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"d", "b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete nth w one kid right", "[flag]") {
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.insert("d", "14112222");
    tree.removeInorderN(0);
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"d", "b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete nth w two kids", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.removeInorderN(1);
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete w no child", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.removeID("12345678");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete w one kid left", "[flag]") {
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.insert("d", "11112222");
    tree.removeID("12345678");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"d", "b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete w one kid right", "[flag]") {
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.insert("d", "14112222");
    tree.removeID("12345678");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"d", "b", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("BST delete w two kids", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.insert("a", "12345678");
    tree.insert("b", "23456789");
    tree.insert("c", "98765432");
    tree.removeID("23456789");
    vector<string> actualOutput = tree.printAsVector("in");
    vector<string> expectedOutput = {"a", "c"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

// test case for 100 random, remove 10
TEST_CASE("BST insert 100, remove 10", "[flag]"){
    AVLTree tree;   // Create a Tree object
    int random;
    for(int i = 0; i < 102; i++){
        random = rand() % (89999999) + 10000000;
        tree.insert("a", to_string(random));
    }
    vector<string> originallyInserted = tree.printAsVector("in");
    /*for(int i = 0; i < 10; i++){
        random = rand() % (90);
        tree.removeInorderN(random);
    }*/
    //vector<string> postRemoval = tree.printAsVector("in");
   /* REQUIRE(100 == originallyInserted.size());
    //REQUIRE(90 == postRemoval.size());
    //REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}
*/