#include<stdio.h>
#include<obliv.h>
#include<bcrandom.h>

#include<../../common/util.h>
#include"../crossTabs.h"

int main(int argc,char* argv[])
{
  if(argc < 4){
    fprintf(stderr, "Usage: %s <port> <--|localhost> <inputFile>\n", argv[0]);
    return 2;
  }

  ProtocolDesc pd;
  sorterIO io;
  
  // Get and check connection
  const char* remote_host = (strcmp(argv[2], "--")==0?NULL:argv[2]);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
  setCurrentParty(&pd,remote_host?2:1);
 

  // Read inputs from file
  FILE *file;

  file = fopen(argv[3], "r");
  fscanf(file, "%zu\n", &(io.iN));
  
  person *arr=malloc(sizeof(person)*(io.iN));
  int id, category, data;
  for(size_t i=0; i<io.iN;i++){
    if(!remote_host){
      fscanf(file, "%d\t%d\n", &id, &category);
      person p;
      p.id = id;
      p.category = category;
      p.data = 0;
      arr[i] = p;
    } else {
      fscanf(file, "%d\t%d\n", &id, &data);
      person p;
      p.id = id;
      p.category = 0;
      p.data = data;
      arr[i] = p;
    }
  }
  
  fclose(file);

  // Set protcolIO
  size_t oN = 0;
  io.input = arr;
  io.oN = &oN;

  // Find size of output
  execYaoProtocol(&pd,sum, &io);


  person *res=calloc(*(io.oN), sizeof(person));
  io.output = res;

  // Run protocol
  execYaoProtocol(&pd,testPersonSorter, &io);

  for(size_t i=0; i<oN; i++){
    person p = io.output[i];
  }
  
  // Verify is sorted
  for(size_t i=0; i<oN-1; i++){
     if(io.output[i].id > io.output[i+1].id){
       fprintf(stderr, "ERROR: List is not sorted by id.\n");
       exit(2);
     }
  }
  fprintf(stdout, "Sorted successfully!\n");

  // CleanUp
  free(arr);
  free(res);
  cleanupProtocol(&pd);
  return 0;
}
