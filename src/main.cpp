#include<project.h>
#include <thread>
#include <chrono>
#pragma comment(lib, "Ws2_32.lib")



int main() {
//sim(1);

cout<<"dd";
//exit(1);
adalm A;
    start();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
A.intcontrol("192.168.2.1");


    char dd[100000];



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
//A.WandR("100000",0,9,2,1);
//A.WandR("100000",0,5,7,1);

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
;



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
comp f[65536];
unsigned char te[10001],data[10001]={0};


         te[0]=0x63;
         te[1]=0x9c;



for(int i=2;i<4096;i++){
         te[i]=rand()%256;//0x00;

}
    //sine(f,32000,4,1,45*3.141/180.0);
    sine(f,8,8,4,0);
    //sine(f+8,8,8,2,M_PI);
    //sine(f+16,8,8,2,0);
   QPSk2(&f[8],te,65536,8);
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


comp f1[32768];
char * buf2=(char *)f1;
int u=0,st=0;

st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);st+=A.readbuff(buf2,32768*4);



while(u<1){

   // thread F(&adalm::writebuff,&A,buf,32000*4);
   // usleep(500);
   //

   //
   A.writebuff(buf,65536*4);

//thread F1(&adalm::readbuff,&A,(char*)f,32000*4);
//cout<<"dd";
//A.readbuff(buf,32000*4);
//cout<<"wdw";
  //F1.join();
 // thread F2(&adalm::readbuff,&A,(char*)f,32000*4);

cout<<A.readbuff(buf2,32768*4);

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
auto s = chrono::steady_clock::now();
// A.writebuff(buf,32768*4);
auto E = chrono::steady_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(E - s);
cout << "Elapsed: " <<duration.count() << " us\n";
//exit(1);
int k=0;
short hh[162768];
short hh1[162768];
//for(int i=0;i<16000;i++)printf("(0x%02X,0x%02X),  ",(int)(uint16_t) f1[i].i,(int)(uint16_t) f1[i].Q);
//exit(1);
//

//for(int i=0;i<32000;i++)cout<<(short)f1[i].i<<",    ";
int su=com2re(f1,hh,32768);

//for(int i=0;i<32768;i++)cout<<(short)f1[i].i<<",   ";

//exit(1);
cout<<A.readbuff(buf2,32768*4);

com2reT(f1,&hh[su],32768);

cout<<A.readbuff(buf2,32768*4);

com2reT(f1,&hh[su+32768],32768);
cout<<endl;
//cout<<endl<<32000-su;
//
//cout<<(32000*4)-su;
//exit(1);

su+=(32768*2);

char ne[su],ne2[su],ll;
int kj,h=0;
for(float db =18;db>-6;db--){
float e=0,lin=pow(10,(float)(db-6)/10);



for(int ii=0;ii<100;ii++){

int ma=short2byte(&hh[6],&ne[0],su);

for(int i=6;i<40000;i++)
{
  if(abs(hh[i])>127)exit(1);
//cout<<(short)ne[i]<<",  ";
}
//exit(1);
for(int i=0;i<su;i++)hh1[i]=hh[i];
float th=0;//=cal(&com[9],8,-2.3561944);
int m=ana(ne,8000,0,&th);
if(db==18&&ii==0)cout<<"m="<<m<<endl;

double av=AvP(&hh1[m],80);



for(int i=m;i<40000;i++)
{
       // if((int)ne[i]+gaussian_sample(0, sqrt(av))>127)exit(1);
      //   if((int)ne[i]+gaussian_sample(0, sqrt(av))<-127)exit(1);
    hh1[i]+=(short)gaussian_sample(0, sqrt((double)av/lin));

    //cout<<hh1[i]<<",   ";

}
short2byte(&hh1[6],&ne[0],su);

//su=(su-(su%8))8
//cout<<"Data size: "<<su<<endl;

char com[su],com2[su];

 //cout<<"signal power:"<<av<<endl;




 kj=S_comp(&ne[0],com, 40000 ,4,round(sqrt(av)*0.7));//round(sqrt(av))*0

 //cout<<round(sqrt(av))<<endl;
 h=kj;
//exit(1);
//cout<<"compress date :"<<kj<<endl;
//exit(1);
kj=S_decomp((unsigned char *)&com[0], (unsigned char *)&com2[0], kj-1 ,4);
//cout<<kj;
//kj=S_decomp((unsigned char *)&com2[0], (unsigned char *)&com[0], cu[1]-1 ,8);
//cout<<kj;
//kj=S_decomp((unsigned char *)&com[0], (unsigned char *)&com2[0], cu[0]-1 ,8);
//cout<<"Decompressed data"<<kj<<endl;

//for(int i=32000-10;i<32000;i++)cout<<i<<":"<<(short)ne[i]<<"  ";
//kj=S_decomp((unsigned char *)&com[0], (unsigned char *)com2, kj-1 ,8);
//cout<<endl;
//A.WandR("",3,0,1,0);
//A.WandR("",3,0,1,0);




 //for(int i=0;i<kj;i++)com2[i]+=(rand()%16)-7;
kj=sy2by(&com2[m],data,8,th,kj);
//de_Dpsk(ne,su,8,data);

//cout<<endl;
//for(int i=0;i<1250;i++)cout<< static_cast<unsigned int8_t>(data[i])<<"=="<<(short)te[i]<<"  ,";

e+=BER((unsigned char *)data,te,10000);


}
cout<<"CNR="<<db<<" cmpression="<<h<<" BER="<<e/1000000<<endl;

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
