
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/Exe

SRC= main.c Game.c snakeConstructor.c SDLRender.c foodSpawn.c

# generic build details

CC=      cc
COPT=    -O
CFLAGS= -lm -framework SDL2 -framework SDL2_image



# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE) 
	rm -f $(OBJ)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:	main.c 
Game.o: Game.c
snakeConstructor.o: snakeConstructor.c
SDLRender.o: SDLRender.c
foodSpawn.o: foodSpawn.c




