
#include "../Header-Files-Folder/screen-includer.h"

bool setup_display_screen(Screen* screen, char title[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Quit();

		return false;
	}

	if(!create_screen_window(&screen->window, screen->height, screen->width, title))
	{
		SDL_Quit();

		return false;
	}

	if(!create_window_surface(&screen->surface, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_renderer(&screen->renderer, screen->surface))
	{
		SDL_FreeSurface(screen->surface);

		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool create_surface_texture(Texture** texture, Renderer* renderer, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(renderer, surface);

	return (texture != NULL);
}

bool create_surface_renderer(Renderer** renderer, Surface* surface)
{
  *renderer = SDL_CreateSoftwareRenderer(surface);

	return (*renderer != NULL);
}

bool create_window_surface(Surface** surface, Window* window)
{
  *surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool create_screen_window(Window** window, unsigned short height, unsigned short width, char title[])
{
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	return (*window != NULL);
}

void free_display_screen(Screen screen)
{
	SDL_DestroyRenderer(screen.renderer);

	SDL_FreeSurface(screen.surface);

	SDL_DestroyWindow(screen.window);

	SDL_Quit();
}

bool render_board_image(Renderer* renderer, Surface* surface, Rect position)
{
	Texture* texture = NULL;

	if(!create_surface_texture(&texture, renderer, surface))
	{
		return false;
	}

	SDL_RenderCopy(renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);

	return true;
}

bool load_filename_image(Surface** image, char filename[])
{
	*image = IMG_Load(filename);

	return (*image != NULL);
}

const char* teamWords[] = {"none", "white", "black"};
const char* typeWords[] = {"none", "pawn", "knight", "bishop", "rook", "queen", "king"};

bool extract_piece_image(Surface** image, Piece piece)
{
	char* filename;

	if(!extract_piece_file(&filename, piece))
	{
		return false;
	}

	if(!load_filename_image(image, filename))
	{
		free(filename);

		return false;
	}

	free(filename);

	return true;
}

bool extract_piece_file(char** filename, Piece piece)
{
	*filename = malloc(sizeof(char) * 128);

	unsigned short team = PIECE_TEAM_MACRO(piece);
	unsigned short type = PIECE_TYPE_MACRO(piece);

	const char* teamWord = teamWords[team];
	const char* typeWord = typeWords[type];

	sprintf(*filename, "%s/%s-%s.png", PIECE_FOLDER, teamWord, typeWord);

	return true;
}

bool render_board_squares(Screen screen)
{
	Surface* whiteSquare, *blackSquare;

	if(!load_filename_image(&whiteSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/white-square.png"))
	{
		return false;
	}

	if(!load_filename_image(&blackSquare, "../Source-Files-Folder/Game-Screen-Folder/Screen-Images-Folder/black-square.png"))
	{
		return false;
	}

	for(Point point = 0; point < 64; point += 1)
	{
		Rect position;

		if(!board_point_position(&position, screen, point))
		{
			return false;
		}

		unsigned short rank = POINT_RANK_MACRO(point);
		unsigned short file = POINT_FILE_MACRO(point);

		Surface* image = (rank + file) % 2 == 0 ? whiteSquare : blackSquare;

		if(!render_board_image(screen.renderer, image, position))
		{
			return false;
		}
	}

	SDL_RenderPresent(screen.renderer);

  	return true;
}

bool render_move_squares(Screen screen, const Piece board[], Info info, Point point)
{
	return true;
}

bool render_board_move(Screen screen, Move move, Surface* image)
{
	return true;
}

bool render_check_squares(Screen screen, const Piece board[], Info info)
{
	return true;
}

bool board_point_position(Rect* position, Screen screen, Point point)
{
	if(!point_inside_board(point)) return false;

	unsigned short rank = POINT_RANK_MACRO(point);
	unsigned short file = POINT_FILE_MACRO(point);

	float squareWidth = (screen.width / BOARD_FILES);
	float squareHeight = (screen.height / BOARD_RANKS);

	float realHeight = squareHeight * rank;
	float realWidth = squareWidth * file;

	*position = (Rect) {realWidth, realHeight, squareWidth, squareHeight};

	return true;
}

bool render_board_pieces(Screen screen, const Piece board[])
{
	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		if(!board_piece_exists(board[point])) continue;

		if(!render_board_piece(screen, board[point], point))
		{
			printf("Could not render_board_piece\n");
			return false;
		}
	}

	return true;
}

bool render_board_piece(Screen screen, Piece piece, Point point)
{
	if(!board_piece_exists(piece)) return false;

	Surface* pieceImage;

	if(!extract_piece_image(&pieceImage, piece))
	{
		printf("Could not extract piece image!\n");
		return false;
	}

	Rect position;

	if(!board_point_position(&position, screen, point))
	{
		printf("Could not board_point_position!\n");
		return false;
	}

	if(!render_board_image(screen.renderer, pieceImage, position))
	{
		printf("Could not render_board_image!\n");
		return false;
	}

	SDL_RenderPresent(screen.renderer);

	return true;
}

bool render_chess_board(Screen screen, const Piece board[], Info info, Point point)
{
	if(!render_board_squares(screen))
	{
		printf("!render_board_squares\n");
		return false;
	}

	SDL_UpdateWindowSurface(screen.window);

	if(!render_check_squares(screen, board, info))
	{
		// I don't know...
	}

	// if(!render_board_move())

	if(!render_move_squares(screen, board, info, point))
	{
		// Nothing!
	}

	if(!render_board_pieces(screen, board))
	{
		printf("if(!render_board_pieces(screen, board))\n");
		return false;
	}

	return true;
}
