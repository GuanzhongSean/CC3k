CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = game.o potion.o orc.o treasure.o barriersuite.o human.o elves.o item.o player.o dwarf.o cell.o grid.o enemy.o chamber.o vampire.o werewolf.o goblin.o merchant.o dragon.o phoenix.o troll.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
