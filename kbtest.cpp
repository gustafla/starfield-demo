/*#include <iostream>
#include <cstdlib>

void cleanup() {
    system("/bin/stty cooked");
}

int main(int argc, char* argv[]) {
    atexit(cleanup);
    char key=0;
    char const ESC=27;
    system("/bin/stty raw");
    for(;;) {
        key = std::cin.peek();
        std::cout << int(key) << std::endl;
        sleep(1);
        if (key == ESC)
            exit(0);
    }
    return 0;
}
*//*
#include <stdio.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <iostream>

int main(void){   
    char const ESC = 27;
    static struct termios oldt, newTt;

    
    tcgetattr( STDIN_FILENO, &oldt);
    newTt = oldt;

    
    newTt.c_lflag &= ~(ICANON);          


    tcsetattr( STDIN_FILENO, TCSANOW, &newTt);

    while(getchar() != ESC)      
        std::cout << "running\n";                 

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);


    return 0;
}
*/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }

/* Let's test it out */
int main(void) {
  char c;
  char const ESC = 27;
  for(;;) {
      c = getch();
      if (c == ESC)
          break;
      std::cout << "Running\n";
  }
  return 0;
} 
