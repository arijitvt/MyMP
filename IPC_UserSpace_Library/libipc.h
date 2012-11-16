#ifndef LIBIPC_H
#define LIBIPC_H

extern int Hyb_Send(int ,const char *, int);
extern int Hyb_ARecv(int, char*, int);
extern int Hyb_Recv(int , char *, int);
//extern int Hyb_Recv(int source, char *data, int count);
#endif
