CFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: ZombieShooter

ZombieShooter: ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o
	@echo "Compiling game"
	@g++ $(CFLAGS) ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o -o ZombieShooter
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

Zombie.o: Zombie.cpp
	@echo "Compiling Zombies.."
	@gcc -c $(CFLAGS) Zombie.cpp

textureHolder.o: textureHolder.cpp
	@echo "Compiling textures"
	@gcc -c $(CFLAGS) textureHolder.cpp

CreateHorde.o: CreateHorde.cpp
	@echo "Creating horde"
	@gcc -c $(CFLAGS) CreateHorde.cpp
 

clean: 
	@echo "Removed ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o and ZombieShooter"
	@rm ZombieShooter.o CreateBackground.o Player.o Zombie.o textureHolder.o CreateHorde.o ZombieShooter
