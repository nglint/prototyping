#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <zstd.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include<unistd.h>
#include <limits>
extern "C" {
#include <zlib.h>
}

#define M_PI 3.14159265358979323846
using namespace std;

union d0
{int num :8 ;
    map <int,string> ch{{ 0,"altvoltage1"}, { 1,"voltage0"}, { 2,"voltage3"},{ 3,"altvoltage0"},{ 4,"voltage2"},{5,"tmp"},{6,"out"},{7,"voltage0"}};

};
struct comp
{
    short  i,Q ;
};
struct Centroid {
    float x;
    float y;
};
int sim(int b);
int gzip(char *data, int len);
int zstd_compress(const char* input, int inputSize);
void de_Dpsk(char *A,int len ,int N,unsigned char *d);
void Dpsk(comp *dpsk,unsigned char * data,int len ,int N);
void com2mag(int len , short * A,comp * d);
int che(char *A);
void sine(comp * A,int len,int N,int S,float th);
int com2reT(comp *A,short *B, int len);
void short2byte2(short *A, char* B,int len);
void ran(comp * A,int len,int N);
void QPSk2(comp *Qpsk,unsigned char * data,int len ,int N);
void QPSk(comp *Qpsk,unsigned char * data,int len ,int N);
int S_comp(char *A, char *B, int len ,int N,int v);
int S_decomp(unsigned char *A,unsigned  char *B, int len ,int N);
double add_angles(double a, double b);
double subtract_angles(double a, double b) ;
double an_difference(double theta1, double theta2) ;
template <typename t> float demod(t *A ,int N);
char deQPSK(char *A ,int N, float th );
int sy2by(char *A,unsigned char *B,int N,float th,int len);
double BER(unsigned char *A,unsigned char *B, int l);
int short2byte(short *A, char* B,int len);
template <typename t> double AvP(t *a,int len);
float AvA(char *a,int len);
float er(float a);
int Max(short* a,int len);
float PO(char *A ,int N );
float chint(char *A,int N,int f);
void cor(char *A,comp *a,int N,int len);
int com2re(comp *A,short *B, int len);
float cal(char *B1,int N,float ph);
int ana(char * B1,int l,float g,float *th);
double gaussian_sample(double mean, double stddev);
void start();

void computeKMeansAngles(const comp* samples, int length, float* outAngles);

static double urand();
class adalm
{public:
map <int ,string>mp;
map <int ,map<int,string>>t;
map <int ,string>co{{0,"WRITE"},{1,"READ"},{2,"READBUF"},{3,"OPEN"},{3,"WRITEBUF"}};
unsigned long long *d,con,re,wr;
 adalm() ;
string av="";
int intcontrol(char *ip);
int intwrite(char *ip,int buff);
int  intread(char *ip,int buff);
int writebuff(char *recvBuffer,int bufsize);
int readbuff(char *recvBuffer,int bufsize);
void information();
int sam_av(int ud);
int fir(char *a,int bw,int sample);
int path(int o);
int WandR(char* data,char de,char ch,unsigned char art,bool w);
int opentransfer(unsigned long long *s,sockaddr_in *add,bool rec);
int sendun(unsigned long long *a,int m );
int recany(unsigned long long *a,char * da );
int timeout(unsigned long long *a,int t);

};
