#include<stdio.h>
#include<obliv.h>
#include<bcrandom.h>

#include"../common/util.h"
#include"crossTabs.h"


double lap;
int main(int argc,char* argv[])
{
  if(argc < 4){
    fprintf(stderr, "Usage: %s <port> <--|localhost> <inputFile>\n", argv[0]);
    return 2;
  }

  ProtocolDesc pd;
  protocolIO io;
  
  size_t N_CATEGORIES=5;

  // Get and check connection
  const char* remote_host = (strcmp(argv[2], "--")==0?NULL:argv[2]);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
  setCurrentParty(&pd,remote_host?2:1);
 

  // Read inputs from file
  FILE *file;

  file = fopen(argv[3], "r");
  fscanf(file, "%zu\n", &(io.iN));
  
  printf("Read n from file %s, value=%zu\n", argv[3], io.iN);

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
  io.input = arr;
  io.nCategories = N_CATEGORIES;

  // Run protocol
  execYaoProtocol(&pd,crossTabs, &io);

  fprintf(stdout, "Cat\tSum\tCount\n");
  for(size_t i=0; i<N_CATEGORIES; i++){
    result r = io.results[i];
    fprintf(stdout, "%d\t%d\t%d\n", r.category, r.dataSum, r.count);
  }

  // CleanUp
  free(arr);
  cleanupProtocol(&pd);
  return 0;
}
