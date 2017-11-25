CFLAGS = -Wall -fpic -coverage -lm

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c testHelpers.c rngs.c dominion.c
	echo "**********Nathan Stauffer - Assignment 3 unit tests**************" > unittestresults.out

	echo "unittest1 - initializeGame function:" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest2 - fullDeckCount function:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	unittest2 >> unittestresults.out	
	gcov -b dominion.c >> unittestresults.out

	echo "unittest3 - endTurn function:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest4 - gainCard function:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardTest1 - adventurer:" >> unittestresults.out    
	gcc -o cardtest1 cardtest1.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardTest2 - smithy:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardTest3 - embargo:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardTest4 - sea hag:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestcard1.out:
	echo "***********Nathan Stauffer - Assignment 4 - randomtestcard1*********" > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

randomtestcard2.out:
	echo "***********Nathan Stauffer - Assignment 4 - randomtestcard2*********" > randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

randomtestadventurer.out:
	echo "***********Nathan Stauffer - Assignment 4 - randomtestadventurer*********" > randomtestdadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c testHelpers.c rngs.c -g $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out




rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe *1 *2 *3 *4 *adventurer
