# Giving-Tree
## Giving Tree Coding Question

### Input Format:
        (A,B) (B,C) (C,D) (A,C) (C,E) (E,F) ...

### Errors:
        E1 - Invalid Input Format
              - One Line
              - Leading/Trailing Whitespace Not Allowed
              - Each Pair Is Formatted Strictly with '(', Parent, Comma, Child, ')'
                  - Example: (A,B)
              - All Values are Uppercase
              - Parent-Child Pairs Are Separated By Single Spaces
              - Sequence Of Pairs Have No Particular Order
        E2 - Duplicate Pair
        E3 - Parent Has More Than Two Children
        E4 - Multiple Roots
        E5 - Input Contains Cycle

### If No Errors:
    Output = Lexicographically Smallest S-Expression
        S-Exp(node) = ( node->value ( S-Exp( node->smallest_child ) )( S-Exp( node->biggest_child ) ) )
