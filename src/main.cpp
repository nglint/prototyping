#include<project.h>
#include <thread>
#include <chrono>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")


int main() {

//sim(1);
cout<<"dd";
//exit(1);
adalm A;
srand(time(NULL));
    start();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
A.intcontrol("192.168.2.1");






    const char* sendData = "ZPRINT\r\n";
    if (send(A.con, sendData, strlen(sendData), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(A.con);
        WSACleanup();
        return 1;
    }

    printf("Data sent: %s\n", sendData);



   char *recvBuffer = new char[128000];
    char trash[1000];
    comp *z=( comp*)recvBuffer;

    int bytesReceived = recv(A.con, trash, sizeof(trash), 0);
    if (bytesReceived > 0) {
        trash[bytesReceived] = '\0'; ////////////
        printf("Received from server: %s\n", trash);
    } else if (bytesReceived == 0) {
        printf("Connection closed by server.\n");
    } else {
        printf("Receive failed: %d\n", WSAGetLastError());
    }

    if (send(A.con, "TIMEOUT 2500\r\n", 14, 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(A.con);
        WSACleanup();
        return 1;
    }
    recv(A.con, trash, sizeof(trash), 0);

char fil[2000];
A.path(1);


A.WandR("2700000000",0,1,5,1);
A.WandR("2700000000",0,0,5,1);
A.WandR("1000000",0,9,2,1);
A.WandR("1000000",0,5,7,1);

//while(A.WandR("1000000",2,6,3,0)==-1);
//while(A.WandR("1000000",0,6,9,0)==-1);//read range
while(A.WandR("1000000",3,2,5,0)==-1);
cout<<A.av.substr(1, A.av.find(' '));

char str[20];
snprintf(str, sizeof(str), "%d", A.sam_av(1));
cout<<str<<endl;
//A.WandR(str,0,6,8,1);
//
A.WandR(str,3,2,4,1);

//A.WandR("0",0,3,0,0);

if(A.av=="1"){ A.WandR("3000000",0,6,8,1);
A.WandR("0",0,3,0,1);
}
A.fir(fil ,1000000,1000000);
A.WandR(fil,0,2,8,1);


//A.WandR("3000000",0,6,8,1);
A.WandR("1",0,3,0,1);

A.WandR("1000000",0,6,8,1);
A.WandR("1000000",2,6,2,1);
//A.WandR("1000000",3,2,4,1);

A.WandR("1000000",0,6,8,0);
A.path(1);




//write filter

//A.WandR(str,0,6,8,1);






//A.WandR((char *)(A.av.substr(1, A.av.find(' ')-1)+"\0\n").c_str(),0,6,8,1);



getchar();
//while(A.WandR("1000000",2,6,2,0)==-1);
//while(A.WandR("1000000",2,6,3,0)==-1);
A.WandR("manual",0,5,2,1);
A.WandR("40",0,5,4,1);
A.WandR("1",0,5,6,1);
A.WandR("1",0,5,0,1);
A.WandR("1",0,5,9,1);

A.WandR("3000000",0,6,8,1);
A.WandR("0",0,3,0,1);
//A.WandR("1000000",3,2,4,1);////XXXXXXXXXXXXXXXXXX
A.fir(fil ,1000000,1000000);
A.WandR(fil,0,2,8,1);


//A.WandR("3000000",0,6,8,1);
A.WandR("1",0,3,0,1);

A.WandR("1000000",0,6,8,1);
A.WandR("1000000",2,6,2,1);
//A.WandR("1",0,1,6,1);
//A.WandR("1",0,5,0,1);
getchar();


A.intwrite("192.168.2.1",65536);





//A.WandR("3000000000",3,0,0,0);
comp *f=(comp*)malloc(65536 * sizeof(comp));
unsigned char *te=(unsigned char*)malloc(10001 * sizeof(unsigned char)),*data=(unsigned char*)malloc(10001 * sizeof(unsigned char));
unsigned char *te2=(unsigned char*)malloc(10001 * sizeof(unsigned char));
int pream=32,block =200,snr=16,ree=1;
     for(int i=0;i<pream/4;i++)    te[i]=0x0;

for(int i=pream/4;i<4096;i++){
         te[i]=rand()%256;

}for(int i=0;i<4096;i++)te2[i]=te[i];
    //sine(f,32000,4,1,45*3.141/180.0);
    sine(f,8,8,4,-2.356);
    sine(&f[8],8,8,4,-2.356);
    //sine(f+8,8,8,2,M_PI);
    //sine(f+16,8,8,2,0);
cout<<"  "<<(short)te[0];
   QPSk2(&f[16],te,65536-8,8);

cout<<"  "<<(short)te2[0];

  // f[0].i=0x7f,f[0].Q=0x7f;
   char  *buf=(char *)f;
A.intread("192.168.2.1",32768);
A.WandR("0x80000088 0x6",3,1,1,1);
A.WandR("2147483784",3,1,1,1);

   /*

   int I=0,Q=0;
   char tt[32000];
short tt2[32000];

com2re((short *)f,tt2,32000);
short2byte(tt2,tt,32000);
   for(int i=4 ;i<8;i++)
{I+=(cos((2*3.141*i/4))*tt[i]);
Q+=(-sin((2*3.141*i/4))*tt[i]);
    printf("%x   %x   ",tt[i],tt[i]);
}

cout<<atan2(Q,I)*(180/3.141)<<endl;
getchar();*/
//cout<<A.writebuff(recvBuffer,32000*4)<<endl;

//A.WandR("2400000000",0,1,5,1);
//A.WandR("20000000",2,6,2,1);

//comp1 *f3=(comp1*)malloc(60000 * sizeof(comp1));
complex<double> f3[60000];
comp *f2=(comp*)malloc(60000 * sizeof(comp));

comp *f1=(comp*)malloc(60000 * sizeof(comp));
char * buf2=(char *)f1;
int u=0,st=0;

st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);


double fill1[17]={ -0.001725024291928052,
-0.003554925804471201,
 0.062665051968945479,
 0.258241035532769836,
 0.387342418295130719,
 0.258241035532583318,
 0.062665051968817345,
-0.003554925804492431,
-0.001725024291926981
};
//cconv(fill1, f1, 9, 65536
        int eee;

while(u<1){

   // thread F(&adalm::writebuff,&A,buf,32000*4);
   // usleep(500);
   //

   //
   A.writebuff(buf,65536*4);
sleep(1);
//thread F1(&adalm::readbuff,&A,(char*)f,32000*4);
//cout<<"dd";
//A.readbuff(buf,32000*4);
//cout<<"wdw";
  //F1.join();
 // thread F2(&adalm::readbuff,&A,(char*)f,32000*4);
jjj:
eee=A.readbuff(buf2,32768*4);

if(eee<1)goto jjj;
cout<<"received samples:"<<eee/4<<endl;
//cout<<A.readbuff(buf2,32000*4);
//A.writebuff(buf,32000*4);
//A.readbuff(buf2,32000*4);
 // F2.join();
//F.join();
//

       // A.readbuff(buf,32000*4);
u++;
       // usleep(30);
//A.WandR("3000000000",2,0,0,0);

}

//exit(1);
int k=0;

short *hh=(short*)malloc(162768 * sizeof(short));
short *hh1=(short*)malloc(162768 * sizeof(short));
//for(int i=0;i<16000;i++)printf("(0x%02X,0x%02X),  ",(int)(uint16_t) f1[i].i,(int)(uint16_t) f1[i].Q);
//exit(1);
//

//for(int i=0;i<40000;i++)cout<<(short)f1[i].i<<",    ";
//exit(1);
//for(int i =0;i<32768;i++)cout<<f1[i].i<<",  ";
//exit(1);
eee/=4;
int su=com2re(f1,hh,eee);
cout<<"received samples:"<<su<<endl;

for(int i=eee-su,ii=0;i<eee+8;i++,ii++)f2[ii]=f1[i];

char * buf3=(char *)&f2[su];


do{
        int u=A.readbuff(buf3,32768*4);
//cout<<"("<<f2[su+8].i<<","<<f2[su+8].Q<<"), ";
        if (u>0)buf3+=u,  su+=(u/4);

}while(su<40000);
cout<<"received samples2:"<<su<<endl;
for(int i=0;i<40010;i++)f1[i]=f2[i];
cout<<endl;
com2reT(f2,hh,40010);
for(int i =0;i<400;i+=16)cout<<demod(&hh[i],8)*(180/M_PI)<<",  ";
cout<<endl;
cout<<endl;
for(int i =0;i<400;i+=16)cout<<atan2(f2[i].Q,f2[i].i)*(180/M_PI)<<",   ";
cout<<endl;
/*for(int i =1;i<400;i+=16)cout<<demod(&hh[i],8)*(180/M_PI)<<",  ";
cout<<endl;
for(int i =2;i<400;i+=16)cout<<demod(&hh[i],8)*(180/M_PI)<<",  ";
cout<<endl;
for(int i =3;i<400;i+=16)cout<<demod(&hh[i],8)*(180/M_PI)<<",  ";
*/

double av=0;


//av=AvP(&hh[9],80);
for(int i=1,ii=0;ii<5000;i+=8,ii++)av+=pow(sqrt(pow(f2[i].i,2)+pow(f2[i].Q,2))/sqrt(2),2);
av/=5000;
double lin=pow(10,(double)(snr)/10);
int m=100;
cout<<endl;

float th=0,re=0,im=0;

 //m=ana(hh,8000,0,&th);


char ne[su],ne2[su],ll;

int kj,h=0,vv=1;



////////////////////////////
int e=0;
float avt[100];
float M1=0;
double filll[17]={
 0.000000000000000000,
 0.087343440359072211,
 0.000000000000000000,
 0.577113616423154951,
 0.000000000000000000,
-0.577113616423154951,
 0.000000000000000000,
-0.087343440359072211,
 0.000000000000000000

};
for(int i=0;i<40010;i++)f1[i]=f2[i];
for(int fd=0;fd<ree;fd++){
for(int ZZ=0;ZZ<100;ZZ++){

 com2reT(f1,hh,40010);
com2im(f1,hh1,40010);

////////////////////////////////////////////////////////////////////////////////
for(int i=0;i<su;i++)
    {
        short noi=(short)gaussian_sample(0, sqrt((double)av/lin));
    hh[i]+=noi;//i1
  //  f1[i].i+=noi;
     noi=(short)gaussian_sample(0, sqrt((double)av/lin));
    hh1[i]+=noi;//Q
//f1[i].Q+=noi;

    }
////////////////////////////////////////////////////////////////////////////////




/*0.026021764007752919,
 0.069775488004793329,
 0.127393887221440044,
 0.177822073611312526,
 0.197973574309402461,
 0.177822073611312526,
 0.127393887221440044,
 0.069775488004793329,
 0.026021764007752919*/
 conv(filll, hh1, 9, 40010);


int r=-1;
 for(int i=0;i<40010;i++)
{
        hh[i]=hh[i]-hh1[i];
        hh1[i]=hh[i];
        if(abs(hh[i])>127)r=1;

}



conv(filll, hh1, 9, 40010);

 //for(int i=0;i<40010;i++)f2[i].i=hh[i],f2[i].Q=hh1[i];

if(r==1)short2byte(&hh[0],&ne[0],su),short2byte(&hh1[0],&ne2[0],40010);
else short2byte2(&hh[0],&ne[0],su),short2byte2(&hh1[0],&ne2[0],40010);
for(int i=0,ii=17;i<(40010/8);i++,ii+=8){f3[i]=std::complex<double>(ne[ii],ne2[ii]);
}

std::complex<double > me=std::complex<double>(0,0);

for(int i = pream; i < pream+block; i++) {

    std::complex<double > temp = f3[i] * f3[i]; // z^2
    me +=( temp * temp) ;                     // z^4

}
me/=block;
short ph[4];
ph[0]=round((0.25 *atan2(me.imag(),me.real()))*(180/M_PI));
//cout<<"Ph[0]="<<ph[0]<<endl;
if(ph[0]<0)ph[0]+=90;
//cout<<"after Ph[0]="<<ph[0]<<endl;
//
ph[1] =ph[0]+90;
    ph[1] = (ph[1] + 180) % 360 - 180;
    ph[2] =ph[1]+90;
    ph[2] = (ph[2] + 180) % 360 - 180;
    ph[3] =ph[2]+90;
    ph[3] = (ph[3] + 180) % 360 - 180;

//phas3 (&f3[1],200,4,ph);


std::complex<double>  zz=std::complex<double>(0,0);
for(int i=0;i<pream;i++)zz+=f3[i];
//cout<<zz<<"  ";

short x=atan2(zz.imag(),zz.real())*(180/M_PI);
int o=-1;

for (int i =0;i<4;i++){
   if( an_difference_deg2(ph[i],x)<=45 )o=i;
}//cout<<"O is :"<<o<<endl;
   float th2=an_difference_deg(ph[o],-135);

 avt[ZZ]=th2;

cout<<ph[0]<<endl;
cout<<ph[1]<<endl;
cout<<ph[2]<<endl;
cout<<ph[3]<<endl;

//float th2=atan2f(sinf(-2.3561944 -ph[0]), cosf(-2.3561944 - ph[0]));
//cout<<"pahse is :"<<th2<<endl;
//cout<<"x :"<<x<<endl;
th2*=(M_PI/180);
float co_s=cos(-th2);
float si_n=sin(-th2);
for(int i=0;i<40000/8;i++){
     //  cout<<((subtract_angles(atan2(f3[i].Q,f3[i].i),-th2))*(180/M_PI))<<",   ";
short x=f3[i].real()*co_s-f3[i].imag()*si_n;
short y =f3[i].real()*si_n+f3[i].imag()*co_s;

f3[i]=std::complex<signed char>(x,y);
//cout<<"("<<x<<","<<y<<")"<<",   ";
}
for(int i=0, d=0; i < 5000; i += 4, d++)
{
    unsigned char da = 0;
    for(int j=0; j<4; j++) {
        unsigned char d2 = 0;
        if(f3[i+j].imag() > 0) d2 |= 1;
        if(f3[i+j].real() > 0) d2 |= 2;
        da |= (d2 << (2 * j));
    }
    data[d] = da;
}

//for(int i =0;i<30;i++)cout<<(short)data[i]<<"==="<<(short)te2[i]<<"   ";

int e2=BER((unsigned char *)data,(unsigned char *)te2,10000);
cout<<"error is:"<<e2<<endl;
e+=e2;

}
float mean =0,var=0,le=0,ri=0,lo=0;

for (int i=0 ; i<100;i++)le+=sin(avt[i]*(M_PI/180)),ri+=cos(avt[i]*(M_PI/180));
    mean=atan2((le/100.0),(ri/100.0))*(180/M_PI);

cout<<"mean is:"<<mean<<endl;
for (int i=0 ; i<100;i++)var+=pow(an_difference_deg(avt[i],mean),2);
var/=100;
cout<<"var deg is :"<<var<<endl;
var *=pow((M_PI/180),2);
cout<<"var rad is :"<<var<<endl;
if(var!=0)lo=10*log10(1/var);
else lo =50;
cout<<"1/var rad  :"<<lo<<endl;
M1+=lo;
;
}cout<<((double)e/10000000);//cout<<"ssdvsd:"<<M1/ree;
exit(1);

for(int i =0;i<su;i++)ne[i]=ne[i];//just comm this
int N=8;
//and make this 16
//here send to cloud


char *s=(char*)malloc(200000 * sizeof(char));



/*
for(int i=0;i<1;i++)
    {vv=0;
do{cout<<"at v="<<vv<<endl;
m=syn <char>(&ne[0],100,N,4,vv,ph);//SYN in cloud
vv++;
}while(m==-1);
cout<<endl<<m<<endl;
}



cout<<ph[0]<<endl;
cout<<ph[1]<<endl;
cout<<ph[2]<<endl;
cout<<ph[3]<<endl;
ph[0]*=(M_PI/180);
//system("cls");
for(int i =m;i<8000;i+=N)demod(&ne[i],N)*(180/M_PI);
cout<<endl;

th=atan2f(sinf(-2.3561944 - ph[0]), cosf(-2.3561944 - ph[0]));
//sy2by2(&ne[N],data,16,th,40000);

cout<<th*(180/M_PI)<<endl;
//for(;;);
*/
//cout<<BER((unsigned char *)data,te,5000);
//exit(1);
//th=atan2f(sinf(-2.3561944 - demod<char>(&ne[m],N)), cosf(-2.3561944 - demod<char>(&ne[m],N)));
//th+=atan2f(sinf(0.785398 - demod<char>(&ne[m+N],N)), cosf(0.785398 - demod<char>(&ne[m+N],N)));
//th=th/2;
cout<<th*(180/M_PI)<<endl;
for(int i =m;i<4000;i+=N)demod1(&ne[i],N,-th);
    //subtract_angles((demod<char>(&ne[i],N)),-th)*(180/M_PI);



exit(1);
//cout<<A.readbuff(buf2,32768*4);
//com2reT(f1,&hh[su+32768],32768);
//cout<<endl;
//cout<<endl<<32000-su;
//cout<<(32000*4)-su;
//exit(1);



    exit(1);


for(float db =15;db>-6;db-=0.5)
{

double e=0,e2=0,lin=pow(10,(float)(db-6)/10);



for(int ii=0;ii<100;ii++){

//for(int i=0;i<40010;i++)hh1[i]=hh[i];
//for(int i=0;i<400;i++)cout<<(short)hh1[i]<<",   ";
//exit(1);


//=cal(&com[9],8,-2.3561944);


if(db==18&&ii==0)cout<<"m="<<m<<endl;

for(int i=0;i<40010;i++)f2[i]=f1[i];


for(int i=m;i<40010;i++)
{
 f2[i].i+=(short)gaussian_sample(0, sqrt((double)av/lin));
 f2[i].Q+=(short)gaussian_sample(0, sqrt((double)av/lin));
//if(hh1[i]<-127)hh1[i]=-127;
//if(hh1[i]>127)hh1[i]=127;
    //cout<<hh1[i]<<",   ";

}
char *s=(char*)malloc(200000 * sizeof(char));
auto ss = chrono::steady_clock::now();
int u=S_comp2(f2,s,40010,4,round(sqrt(av)));
auto E = chrono::steady_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(E - ss);
//cout << "Elapsed: " <<duration.count() << " us\n";
//if(ii==0)cout<<u<<endl;
//S_decomp2(f3,s,u,4);
//com2reT(f3,hh,40010);
//com2reT(f2,hh1,40010);
char com[su],com2[su];
sy2by2(&hh[m+6],data,8,th,40009);

//de_Dpsk(ne,su,8,data);

e+=BER((unsigned char *)data,te,10000);

sy2by2(&hh1[m+6],data,8,th,40009);

//de_Dpsk(ne,su,8,data);

e2+=BER((unsigned char *)data,te,10000);

//cout<<e<<endl;

}

//zstd_compress(ne,40000);
//gzip(com,40000);
//cout<<"CNR="<<db<<" cmpression="<<h<<" BER="<<e/1000000<<endl;
cout<<e/1000000<<"   "<<e2/1000000<<endl;
}
//cout<<"comp"<<kj<<endl;
while(1)
{
  //
/*
 //usleep(32000) ;



   A.readbuff(buf2,32768*4);
//auto s = chrono::steady_clock::now();
//A.writebuff(buf,32000*4);
 //auto E = chrono::steady_clock::now();
   com2reT(f1,hh,32768);
   short2byte(&hh[0],&ne[0],32768);

    kj=S_comp(&ne[0],com, 32768 ,4,2);
    S_decomp((unsigned char *)&com[0], (unsigned char *)com2, kj-1 ,4);
   cout<< kj<<endl;
   //for(int i=0;i<100;i++)cout<<(short)ne[i]<<",  ";
//ana(com2,32768,th);
exit(1);
  // auto duration = chrono::duration_cast<chrono::milliseconds>(E - s);

   // cout << "Elapsed: " <<duration.count() << " ms\n";

*/
}
for(int i=10000;i<5;i++){
      //  if(i%8==0)cout<<endl<<i<<endl;
    // cout<<endl<<i<<":"<<((int)com2[i])<<"  "<<(int)ne[i];

}

//cout<<kj<<endl;
//for(int i=0;i+=5;i<kj)cout<<(int)com[i]<<"  ";
//exit(1);
//for(int i=0;i<su;i++)cout<<(int)ne[i]<<"   ";

//ana(ne,32768);
exit(1);
cin>>ll;
if(ll=='a')
{
    for(int i=0;i<su;i++)
    {
        printf("0x%02X , ",(int)(uint16_t) hh[i]);
    }
}
exit(1);

for(int i=0 ;i<32000;i++)
{if(sqrt(pow(f1[i].i,2)+pow(f1[i].Q,2))>0xff&&k==0)k=1;
  if(1)  printf("%x   %x   ",f1[i].i,f1[i].Q);
}




    closesocket(A.con);
    WSACleanup();

    return 0;
}
