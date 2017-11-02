CFLAGS = -Wall -fpic -coverage -lm -g

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffects.o: cardEffects.h cardEffects.c
	gcc -c cardEffects.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffects.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cardEffects.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o cardEffects.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o cardEffects.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o cardEffects.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testing.o: testing.c testing.h dominion.h 
	gcc -c testing.c $(CFLAGS)

cmpGameState.o: cmpGameState.c cmpGameState.h dominion.h
	gcc -c cmpGameState.c $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

player: player.c interface.o cardEffects.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cardEffects.o $(CFLAGS)

randomtest1: randomtest1.c dominion.o rngs.o cardEffects.o testing.o cmpGameState.o		
	gcc -o randomtest1 randomtest1.c -g dominion.o rngs.o cardEffects.o testing.o cmpGameState.o $(CFLAGS)

cardtests: cardtest1 cardtest2 cardtest3 cardtest4

unittests: unittest1 unittest2 unittest3 unittest4

unittestresults.out: cardtests unittests
	./cardtest1 > unittestresults.out 
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	gcov -bf cardEffects.c >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
