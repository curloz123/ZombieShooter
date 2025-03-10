CXX = g++
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: sln

sln: textureHolder.o Zombie.o CreateHorde.o Player.o CreateBackground.o ZombieShooter.o Bullet.o Pickup.o
	@$(CXX) ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o Bullet.o Pickup.o -o sln $(LDFLAGS)
	@echo ""
	@echo "Time for the mission, get ready.."
	@chmod +x sln

ZombieShooter.o: ZombieShooter.cpp
	@echo "Almost There"
	@$(CXX) -c  ZombieShooter.cpp 

Player.o: Player.cpp
	@echo "Armouring you up..."
	@$(CXX) -c Player.cpp 

CreateBackground.o: CreateBackground.cpp
	@echo "Setting your arena..."
	@$(CXX) -c CreateBackground.cpp

Zombie.o: Zombie.cpp
	@echo "Awaking Zombies.."
	@$(CXX) -c Zombie.cpp

textureHolder.o: textureHolder.cpp
	@echo "loading textures"
	@$(CXX) -c textureHolder.cpp

CreateHorde.o: CreateHorde.cpp
	@echo "Creating horde"
	@$(CXX) -c CreateHorde.cpp
 
Bullet.o: Bullet.cpp
	@echo "Readying Bullets"
	@$(CXX) -c Bullet.cpp

Pickup.o: Pickup.cpp
	@echo "setting up your enhancements"
	@$(CXX) -c Pickup.cpp

clean: 
	@echo "Removed ZombieShooter.o Player.o CreateBackground.o Zombie.o textureHolder.o CreateHorde.o Pickup.o and the sln executable"
	@rm *.o sln
