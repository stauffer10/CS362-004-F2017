#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//helper
void swap(char *c1, char *c2){
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

char inputChar()
{
	int randInt;
    	char c;
	
	//33-126
	randInt = (rand()%(126-32)) + 32;
	c = randInt;
	
    return c;
}

char *inputString()
{
	char string[6] = "eestr";
	int i, j;
	char *s = (char*)malloc(strlen(string)+1);
	char *sw1;
	char *sw2;
	
	//algorithm to randomly shuffle elements of an array
	//borrowed from http://www.geeksforgeeks.org/shuffle-a-given-array/
	for (i=4; i>=0; i--){
		j = rand()%(i+1);
		sw1 = &string[i];
		sw2 = &string[j];
		swap(sw1, sw2);
	}
	
	strcpy(s, string);
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
   
	srand(time(NULL));
    testme();
	
	
    return 0;
}
