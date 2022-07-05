
#ifndef ENGINE_INCLUDE_FILE_H
#define ENGINE_INCLUDE_FILE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#include "engine-field-point.h"
#include "engine-field-piece.h"
#include "engine-field-move.h"
#include "engine-field-info.h"
#include "engine-field-kings.h"

#include "chess-engine-values.h"
#include "chess-engine-macros.h"

#include "handler-field-info.h"
#include "handler-field-kings.h"
#include "handler-field-move.h"
#include "handler-field-point.h"
#include "handler-field-piece.h"

#include "field-parts-handler.h"

#include "game-boolean-logic.h"
#include "execute-chess-moves.h"
#include "ident-board-moves.h"
#include "chess-game-actions.h"

#include "chess-moves-legal.h"
#include "move-ability-valid.h"
#include "move-pattern-fits.h"
#include "move-prevent-check.h"

#include "piece-pattern-moves.h"
#include "move-patterns-valid.h"

#include "board-value-defines.h"
#include "create-board-value.h"
#include "create-engine-move.h"
#include "move-array-sorter.h"

#include "string-board-parser.h"
#include "create-string-board.h"
#include "string-type-handler.h"
#include "chess-symbol-defines.h"

#endif
