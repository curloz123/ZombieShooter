CFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: ZombieShooter

ZombieShooter: ZombieShooter.o Player.o CreateBackground.o 
	@echo "Compiling game"
	@g++ $(CFLAGS) ZombieShooter.o Player.o CreateBackground.o -o ZombieShooter
	@chmod +x ZombieShooter

ZombieShooter.o: ZombieShooter.cpp
	@echo "Compiling main file"
	@g++ -c $(CFLAGS) ZombieShooter.cpp 

Player.o: Player.cpp
	@echo "Compiling Player"
	@g++ -c $(CFLAGS) Player.cpp 

CreateBackground.o: CreateBackground.cpp
	@echo "Compiling Background"
	@g++ -c $(CFLAGS) CreateBackground.cpp
 

clean: 
	@echo "Removed ZombieShooter.o Player.o CreateBackground.o and ZombieShooter"
	@rm ZombieShooter.o CreateBackground.o Player.o ZombieShooter
