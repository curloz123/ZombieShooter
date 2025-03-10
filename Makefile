CXX = g++
CFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: sln

sln: textureHolder.o Zombie.o CreateHorde.o Player.o CreateBackground.o ZombieShooter.o Bullet.o Pickup.o
	@$(CXX) $(CFLAGS) ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o Bullet.o Pickup.o -o sln
	@echo ""
	@echo "Time for the mission, get ready.."
	@chmod +x sln

ZombieShooter.o: ZombieShooter.cpp
	@echo "Almost There"
	@$(CXX) -c $(CFLAGS) ZombieShooter.cpp 

Player.o: Player.cpp
	@echo "Armouring you up..."
	@$(CXX) -c $(CFLAGS) Player.cpp 

CreateBackground.o: CreateBackground.cpp
	@echo "Setting your arena..."
	@$(CXX) -c $(CFLAGS) CreateBackground.cpp

Zombie.o: Zombie.cpp
	@echo "Awaking Zombies.."
	@$(CXX) -c $(CFLAGS) Zombie.cpp

textureHolder.o: textureHolder.cpp
	@echo "loading textures"
	@$(CXX) -c $(CFLAGS) textureHolder.cpp

CreateHorde.o: CreateHorde.cpp
	@echo "Creating horde"
	@$(CXX) -c $(CFLAGS) CreateHorde.cpp
 
Bullet.o: Bullet.cpp
	@echo "Readying Bullets"
	@$(CXX) -c $(CFLAGS) Bullet.cpp

Pickup.o: Pickup.cpp
	@echo "setting up your enhancements"
	@$(CXX) -c $(CFLAGS) Pickup.cpp

clean: 
	@echo "Removed ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o Pickup.o and the sln executable"
	@rm *.o sln
