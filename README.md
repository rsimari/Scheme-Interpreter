Project 01: uScheme
===================

This is a simple implementation of a [Scheme] interpreter that supports the
following syntax:

    <digit>         = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <number>        = {<digit>}
    <op>            = - | + | * | /
    <expression>    = (<op> <expression> <expression>) | <number>

Examples
--------

    :::scheme
    1
    (+ 1 2)
    (+ 1 (- 2 3))
    (+ (* 1 2) (- 3 4))

[Scheme]:   https://en.wikipedia.org/wiki/Scheme_(programming_language)

1. The Big O of our interpreter is O(n). In this case n is the number of tokens plus the number of chars in the input line. This is because the parsing is done is O(c) time where c is the number of characters and each char is touched once. Building the tree is done in O(t) time where t is the number of tokens that are created from the line. This is because each token is a node in the tree. When interpreting the tree it takes O(t) time again because each node/token is essentially touched once. We do recognize that operator nodes are technically touched twice because they are evaluated and then touched again as an operand but this will not affect the Big O of the function.

2. The smart pointer version is larger. // TODO. We see the biggest advantage of smart pointers as the automatic memory management and automatic reference counting. The biggest disadvantage is that // TODO. We prefer using the regular pointers because managing memory is much easier than dealing with the syntax of smart pointers. 

3. The interpreter tree would need to support an indefinite number of child nodes. The parse_token function would stay the same but the parse__expression function would change to support more operands until you hit a ')'. The interpreter would mainly change by when you build and traverse the tree. Right now they both support just 2 nodes. They would need to go to each pointer to each child, check if its a nullptr and if its not then keep going and then evaluate. For the most part the building of the tree would not change that much because it already checks for the nullptr with recursion, the only thing that would change would be it would need to check all Node pointers not just the 2 it currently supports.

Contributions:

Robert Simari --> wrote evaluate_r() and parse__token() for the most part by myself. We really partner coded most of the project. We did the changes to support smart pointers together.

John Joyce --> 
