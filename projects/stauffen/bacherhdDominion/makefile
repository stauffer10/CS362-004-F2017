CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: cardtest1.c cardtest2.c cardtest4.c randomtestadventurer.c randomtestcard1.c rngs.c testHelpers.c cardEffects.c dominion.c
	echo "cardtest1.c:" >> tests.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c testHelpers.c cardEffects.c $(CFLAGS)
	cardtest1 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "cardtest2.c:" >> tests.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c testHelpers.c cardEffects.c $(CFLAGS)
	cardtest2 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "cardtest4.c:" >> tests.out
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c testHelpers.c cardEffects.c $(CFLAGS)
	cardtest4 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "randomtestadventurer.c:" >> tests.out
	gcc -o randomtestadventurer1 randomtestadventurer.c dominion.c rngs.c testHelpers.c cardEffects.c $(CFLAGS)
	randomtestadventurer1 >> tests.out
	gcov dominion.c >> tests.out
	
	echo "randomtestcard1.c:" >> tests.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c testHelpers.c cardEffects.c $(CFLAGS)
	randomtestcard1 >> tests.out
	gcov dominion.c >> tests.out

clean: 
	rm tests.out *1 *2 *4 *.gcda *.gcno *.gcov
