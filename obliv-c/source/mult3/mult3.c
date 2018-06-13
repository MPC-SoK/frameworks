#include<stdio.h>
#include<obliv.h>

#include"mult3.h"

int main(int argc, char** argv){

  if(argc != 4){
    fprintf(stderr, "Usage: %s <port> <--|localhost> <inputFIle>\n", argv[0]);
    return 2;
  }

  ProtocolDesc pd;
  protocolIO io;

  // Read inputs from file
  FILE* file;
  file = fopen(argv[3], "r");

  char* errorMsg = "Input file must me in format:\nOPERAND_1\nOPERAND_2\nOPERAND_3\n";
  if(fscanf(file, "%d\n", &io.aShare) == EOF){
    fprintf(stderr, errorMsg);
    return 2;
  } if (fscanf(file, "%d\n", &io.bShare) == EOF){
    fprintf(stderr, errorMsg);
    return 2;
  } if (fscanf(file, "%d\n", &io.cShare) == EOF){
    fprintf(stderr, errorMsg);
    return 2;
  }

  fclose(file);

  const char* remote_host = (strcmp(argv[2], "--")==0?NULL:argv[2]);
 // ocTestUtilTcpOrDie(&pd, remote_host, argv[1]);
  if(!remote_host){
    if(protocolAcceptTcp2P(&pd, argv[1])){
      fprintf(stderr, "TCP accept failed\n");
      exit(1);
    }
  }
  else{
    if(protocolConnectTcp2P(&pd,remote_host,argv[1])!=0){
      fprintf(stderr,"TCP connect failed\n");
      exit(1);
    }
  }

  int currentParty = remote_host?2:1;
  setCurrentParty(&pd, currentParty); 

  execYaoProtocol(&pd, mult3, &io);

  fprintf(stderr, "Mult3: result = %d\n", io.prod);

  cleanupProtocol(&pd);
  return 0;
}
