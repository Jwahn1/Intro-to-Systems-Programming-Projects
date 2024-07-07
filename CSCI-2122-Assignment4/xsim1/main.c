#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

int main(int argc, char **argv) {
  //argv[1] is the maximum amount of cycles the program should run for 
  //argv[2] is the name of the file that houses the code

  //instantiates the xcpu struct
  xcpu *computer = malloc(sizeof(xcpu));

  //initialize the ram
  xmem_init(65536);


  //get the program path
//   char full_path[256];  
//   strcpy(full_path, "tests/");
//   strcat(full_path, argv[2]); 


  FILE *code = fopen(argv[2], "rb");
  
  //store the program code into the cpu
   unsigned char data[2];
   unsigned short addr = 0;
    
    //move 2 bytes at a time to memstore starting from address 0 then address+2 
    //and so one with every other pairs of bytes (2 bytes == 1 assembly instruction)
    while (fread(data, 1, 2, code) == 2) {
        xmem_store(data, addr);
        addr += 2;
    }
    
     fclose(code);

  //initialize the values in our cpu
  memset(&computer, 0, sizeof(xcpu));

  //run program 
  int max_cycles = atoi(argv[1]); //converts from string to int
  int cycles = 0;
  while (max_cycles == 0 || cycles < max_cycles) { //both conditions specificed in the doc
    if (!xcpu_execute(computer)) { //stop the cpu if all commands are done (returns 0)
      break;  // Exit loop if execution returns 0
    }
    cycles++;
  }

  return 0;
}


