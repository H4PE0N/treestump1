# treestump
Treestump is going to be a smart, simple and fast chess engine. The name comes from the tree in the minimax algorithm.

Todo:
- rename 'info' to 'state' maybe?
- create engine struct for [wtime, btime, winc, binc] and so on
- create a history of positions. That way, a move list can be created, and moves can be undone
- implement transposition tables that let you look up positions that have already been evaluated
- implement look up table for openings
- change data types to more specific and optimized, like (uint8)
