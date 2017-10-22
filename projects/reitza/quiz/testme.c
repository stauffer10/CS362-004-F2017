#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    int c[27] = {91, 40, 123, 32, 97, 120, 125, 41, 93};
                //,93, 29, 125, 120, 97, 32, 123, 28, 91
                //,97, 32, 120, 123, 125, 28, 29, 91, 93};

    char character;
    character = c;
    return c[rand()%28];
}

char *inputString()
{
    // TODO: rewrite this function
    static char string[] = "rest";
    char *randomString = NULL;
    randomString = malloc(sizeof(char)*5);
    int i,r;
    for(i=0; i < 5;i++)
    {
        r=rand()%4;
        randomString[i]= string[r];
    }
    string[5]='\0';
    return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  int x;
   /* for(x=0;x<100;x++)
    {
        printf("Character: %c\n", inputChar());
        printf("String: %s\n",inputString());
    }*/

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
