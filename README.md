# treestump
Treestump is going to be a smart, simple and fast chess engine. The name comes from the tree in the minimax algorithm.

Todo:
- rename 'info' to 'state' maybe?
- create engine struct for [wtime, btime, winc, binc] and so on
- create a history of positions. That way, a move list can be created, and moves can be undone
- implement three fold repitition rule (maybe using zobrist hash for lookup)
- implement look up table for openings
- store images of chess pieces ans so on in a variable for fast lookup
- implement sound effects, like in my minesweeper game
