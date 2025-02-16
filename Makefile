CFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: ZombieShooter

ZombieShooter: textureHolder.o Zombie.o CreateHorde.o Player.o CreateBackground.o ZombieShooter.o Bullet.o
	@g++ $(CFLAGS) ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o Bullet.o -o ZombieShooter
	@echo ""
	@echo "Time for the mission, get ready.."
	@chmod +x ZombieShooter

ZombieShooter.o: ZombieShooter.cpp
	@echo "Almost There"
	@g++ -c $(CFLAGS) ZombieShooter.cpp 

Player.o: Player.cpp
	@echo "Armouring you up..."
	@g++ -c $(CFLAGS) Player.cpp 

CreateBackground.o: CreateBackground.cpp
	@echo "Setting your arena..."
	@g++ -c $(CFLAGS) CreateBackground.cpp

Zombie.o: Zombie.cpp
	@echo "Awaking Zombies.."
	@gcc -c $(CFLAGS) Zombie.cpp

textureHolder.o: textureHolder.cpp
	@echo "loading textures"
	@gcc -c $(CFLAGS) textureHolder.cpp

CreateHorde.o: CreateHorde.cpp
	@echo "Creating horde"
	@gcc -c $(CFLAGS) CreateHorde.cpp
 
Bullet.o: Bullet.cpp
	@echo "Readying Bullets"
	@gcc -c $(CFLAGS) Bullet.cpp

clean: 
	@echo "Removed ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o and ZombieShooter"
	@rm ZombieShooter.o CreateBackground.o Player.o Zombie.o textureHolder.o CreateHorde.o ZombieShooter Bullet.o
