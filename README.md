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

1. The Big O of our interpreter is O(n). In this case n is the number of nodes in our tree. The parsing portion of the interpreter touches each character of input, many of which subsequently become independent nodes. Thus, we can drop the small effect of reading in extra characters. Building the tree is similarly done in O(n) time, as we are always inserting new nodes in leaf positions while constructing the tree. Finally, the interpretation phase again requires O(n) time. This is because using a stack we are able to push and pop the leaf nodes for each level of the tree while traversing up it from the bottom, while slicing the leaf nodes off the bottom of tree as we move up. Essentially, this means that for the bottom level of the tree, we perform (n+1)/2 total operations pushing the leafs into the stack. For the next level, we pop each of these nodes, adding half the previous number of values into the array. This halving process occurs repeatedly as we execute up the tree. By the time we have reached the top, we have essentially pushed and popped all n nodes (2*n). Thus, we can deem the operation to be O(n). In summing the time complexities of each of the distinct parts of the interpreter, we get O(3n), which simplifies to O(n).

2. The smart pointer executable is larger. Intuitively, this seems to be because there is more code overhead associated with using smart pointers. This is because our executable must incorporate all of the functionality associated with smart pointers. At runtime, both executables seem to use roughly the same amount of memory. This is because we are efficiently managing our own memory, in much the same way as the smart pointers would. We prefer performing manual memory management over using smart pointers, at least in the context of this project. We realize that the advantage of smart pointers is automatic memory management and automatic reference counting, which is extremely useful. However, there are certainly a few disadvantages that can come with using smart pointers. Firstly, using them entails incorporating ugly, complex syntax into your code. Another, perhaps more meaningful disadvantage, is that it is less clear when memory associated with a pointer is deallocated behind the scenes. This, in many cases, can be problematic if the programmer needs to perform specific tasks when a destructor is run or if they need tight control on an object's lifecycle. Due to the relatively small scale of this project, manually managing the memory of our objects via the heap is not overly complicated. Thus, in this context, the benefits of using smart pointers may not outweigh their disadvantages.

3. There are a few ways in which we could implement this type of interpreter. One would be to support an indefinite number of child nodes at each root node. This would allow for multiple operands to be stored as children to operators. In this implementation, the parse_token function would essentially remain the same but the parse__expression function would change to support any number of operands, up until a closing brace was found ')'. The major difference in the interpretation phase would be regarding traversal of the tree. As of now, we are only able to traverse down and up 2 children nodes. In the case of multiple children nodes, we could use a map data structure to hold the various children nodes, accessing them by iterating through the keys of the map. This would allow for an indefinite amount of children and is often used in the implementation of a trie or prefix tree (using a letter as the key, node pointer as val). Thus, we could iterate through each key in the map, traversing down the associated value (which would be a pointer to the child node). Recursing up the tree and calculating values would work very similarly to how it does now, again iterating through the children of a node and performing the specified operation across all nodes. The biggest change in this process would be iterating through all children nodes of a root to calculate the values specified.


Contributions:

Robert Simari --> wrote evaluate_r() and parse__token() for the most part by myself. We really partner coded most of the project. Together we did the changes to support smart pointers.

John Joyce --> wrote evaluate(), parse_expression() and tree traversal helper functions. Worked closely with Rob on implementation using smart pointers.

Overall, we worked on the entirety of the project in person together.
