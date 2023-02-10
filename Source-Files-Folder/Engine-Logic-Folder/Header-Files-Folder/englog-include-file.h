
#ifndef ENGLOG_INCLUDE_FILE_H
#define ENGLOG_INCLUDE_FILE_H

#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "engine-point-values.h"
#include "engine-piece-values.h"
#include "engine-move-values.h"
#include "engine-state-values.h"

#include "engine-point-macros.h"
#include "engine-piece-macros.h"
#include "engine-move-macros.h"
#include "engine-state-macros.h"

#include "chess-engine-values.h"
#include "chess-engine-macros.h"
#include "chess-board-values.h"

#include "handler-field-state.h"
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
#include "move-pattern-handler.h"

#include "string-board-parser.h"
#include "create-string-board.h"
#include "string-type-handler.h"
#include "chess-symbol-defines.h"

#endif
