#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include<unistd.h>
#include <thread>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
std::map<int,map<std::string, std::map<int, std::string>>> channels;
union d0
{int num :8 ;
    map <int,string> ch{{ 0,"altvoltage1"}, { 1,"voltage0"}, { 2,"voltage3"},{ 3,"altvoltage0"},{ 4,"voltage2"},{5,"tmp"},{6,"out"},{7,"voltage0"}};

};
struct comp
{
    short  i,Q ;
};
void com2mag(int len , short * A,comp * d)
{
  for(int i=0;i<len;i++)
  {
    A[i]=((d[i].i)) ;
  }
  return;
}
void sine(comp * A,int len,int N,int S,float th)
{
for(int i=0;i<len;i+=4){
    for(int I=0;I<N;I++)
{
   A[i+I].i=(short)(cos((2*3.141*I/N)+th)*32767)/S ;
   A[i+I].Q=(short)(sin((2*3.141*I/N)+th)*32767)/S ;
}
}
    return;
}
void ran(comp * A,int len,int N)
{float th=((360/N)*3.141)/180;
for(int i=0;i<len;i+=4){
    for(int I=0;I<N;I++)
{
   A[i+I].i=(short)rand() ;
   A[i+I].Q=(short)rand() ;
}
}
    return;
}
void QPSk(comp *Qpsk,unsigned char * data,int len ,int N)
{comp I[len],Q[len];
 sine(I,len, N,2,0) ;
 sine(Q,len, N,2,(90*3.141)/180) ;
 char a,b;
   for(int i=0,q=0;i<len;i+=4,q++)
   {
        if(q%4==0)
   {
    data ++;

   }
      a=*data&1;
   *data=*data>>1;
   b=*data&1;
   *data=*data>>1;

   if(!a)a=-1;
   if(!b)b=-1;

       for(int ii=0;ii<N;ii++)
       {
        Qpsk[i+ii].i=(I[i+ii].i*a)+(Q[i+ii].i*b);
        Qpsk[i+ii].Q=(I[i+ii].Q*a)+(Q[i+ii].Q*b);
       }
   }
 return;
}

void com2re(short *A,short *B, int len)
{

 for(int i=0;i<len;i+=2,B++)
 {
  *B=A[i]  ;
 }
   return;
}

void short2byte(short *A,char* B,int len)
{
  float c=0;
  for(int i=0;i<len;i++,B++)
  {
    c= ((float)A[i]/32768)*128 ;
    *B=(char)c;
  }
  return;
}

class adalm
{public:
    map <int ,string>mp;
    map <int ,map<int,string>>t;
     map <int ,string>co{{0,"WRITE"},{1,"READ"},{2,"READBUF"},{3,"OPEN"},{3,"WRITEBUF"}};
    unsigned long long *d,con,re,wr;
  adalm() {   mp[0]="iio:device0",mp[1]="iio:device1",mp[2]="iio:device2",mp[3]="iio:device3";
  t[0][0]="OUTPUT", t[0][1]="OUTPUT", t[0][2]="DEBUG", t[0][3]="INPUT" , t[0][4]="INPUT", t[0][5]="INPUT", t[0][6]="OUTPUT", t[0][7]="INPUT", t[0][8]="OUTPUT", t[0][9]="OUTPUT";
   t[1][0]="INPUT", t[1][1]="INPUT", t[1][2]="INPUT", t[1][3]="INPUT", t[1][4]="INPUT", t[1][5]="INPUT", t[1][6]="INPUT", t[1][7]="INPUT", t[1][8]="INPUT", t[1][9]="" ;
  t[2][0]="", t[2][1]="OUTPUT", t[2][2]="OUTPUT", t[2][3]="OUTPUT", t[2][4]="", t[2][5]="DEBUG", t[2][4]="OUTPUT", t[2][5]="OUTPUT";
   t[3][2]="", t[3][3]="DEBUG",t[3][2]="INPUT", t[3][3]="INPUT";
  }

intcontrol(char *ip)
{
 con = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    if ( con == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(30431); // Server port
    serverAddr.sin_addr.s_addr = inet_addr("192.168.2.1"); // Server IP (localhost)

    // Connect to the server
    if (connect( con, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket( con);
        WSACleanup();
        return 1;
    }

    printf("Connected to server!\n");}




 intwrite(char *ip,int buff)
  {wr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
string da="OPEN iio:device2 ";
da=da+std::to_string(buff);
da=da+" 00000003\r\n";
    if (wr == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());

        return -1;
    }

    // Define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(30431); // Server port
    serverAddr.sin_addr.s_addr = inet_addr(ip); // Server IP (localhost)

    // Connect to the server
    if (connect(wr, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(wr);
        return -1;
    }

    if (send(wr, da.c_str(), da.length(), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(wr);
        return -1;
    }
    char r[10];
 recv(wr,r , 4, 0);

  }


  intread(char *ip,int buff)
  {re = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
string da="OPEN iio:device3 ";
da=da+std::to_string(buff);
da=da+" 00000003\r\n";
    if (re == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());

        return -1;
    }

    // Define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(30431); // Server port
    serverAddr.sin_addr.s_addr = inet_addr(ip); // Server IP (localhost)

    // Connect to the server
    if (connect(re, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(re);
        return -1;
    }

    if (send(re, da.c_str(), da.length(), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(re);
        return -1;
    }
    char r[10];
 recv(re,r , 4, 0);

  }

 int writebuff(char *recvBuffer,int bufsize)
 {string da="WRITEBUF iio:device2 ";
 da=da+std::to_string(bufsize)+"\r\n";
      if (send(wr,da.c_str(), da.length(), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        return -1;
    }
    int g=0,e=0,m=0;

    cout<<recv(wr, recvBuffer,2, 0)<<endl;

  do{
    g= send(wr, recvBuffer, bufsize, 0);
    if(g>0)m+=g;
    e++;
    if(e>10000)return -1;
  }while(g<1||m<bufsize);

  return m;
 }

  int readbuff(char *recvBuffer,int bufsize)
 {char data[1460];
     string da="READBUF iio:device3 ";
 da=da+std::to_string(bufsize)+"\r\n";
      if (send(re,da.c_str(), da.length(), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        return -1;
    }
    int g=0,e=0,m=0;
    char G[12];
    cout<<recv(re, G, to_string(bufsize).length()+1, 0)<<endl;
    cout<<recv(re, G, 9, 0)<<endl;
  do{
    g= recv(re, &recvBuffer[m], bufsize, 0);

    if(g>0){m+=g;


    }
    if (g < 0) {
    int wsa_error = WSAGetLastError();
    printf("WSA Error: %d\n", wsa_error);
      e++;
}

    if(e>100)return -1;
  }while(g<1||m<bufsize);

  return m;
 }


 void information()
 {
    cout<<"\nde0:\n0-altvoltage0\n1-altvoltage1\n2-debug\n3-out\n4-temp0\n5-voltage0_input\n6-voltage0_output\n7-voltage2_input\n8-voltage2_output\n9-voltage3\n"<<endl;
 cout<<"\nde1:\ntemp0\n0-voltage0\n1-voltage1\n2-voltage2\n3-voltage3\n4-voltage4\n5-voltage5\n6-voltage6\n7-voltage7\n8-voltage8\n9-zero"<<endl;
 cout<<"\nde2:\n0-altvoltage0\n1-altvoltage1\n2-altvoltage2\n3-altvoltage3\n4-buff\n5-debug\n6-voltage0\n7-voltage1"<<endl;
  cout<<"\nde3:\n0-buff\n1-debug\n2-voltage0\n3-voltage1"<<endl;
 }

int fir(char *a,int bw,int sample)
{
  if(bw==20000000&&sample==1000000) strcpy(a,"RX 3 GAIN -6 DEC 4.TX 3 GAIN 0 INT 4.-15,-15.-27,-27.-23,-23.-6,-6.17,17.33,33.31,31.9,9.-23,-23.-47,-47.-45,-45.-13,-13.34,34.69,69.67,67.21,21.-49,-49.-102,-102.-99,-99.-32,-32.69,69.146,146.143,143.48,48.-96,-96.-204,-204.-200,-200.-69,-69.129,129.278,278.275,275.97,97.-170,-170.-372,-372.-371,-371.-135,-135.222,222.494,494.497,497.187,187.-288,-288.-654,-654.-665,-665.-258,-258.376,376.875,875.902,902.363,363.-500,-500.-1201,-1201.-1265,-1265.-530,-530.699,699.1748,1748.1906,1906.845,845.-1089,-1089.-2922,-2922.-3424,-3424.-1697,-1697.2326,2326.7714,7714.12821,12821.15921,15921.15921,15921.12821,12821.7714,7714.2326,2326.-1697,-1697.-3424,-3424.-2922,-2922.-1089,-1089.845,845.1906,1906.1748,1748.699,699.-530,-530.-1265,-1265.-1201,-1201.-500,-500.363,363.902,902.875,875.376,376.-258,-258.-665,-665.-654,-654.-288,-288.187,187.497,497.494,494.222,222.-135,-135.-371,-371.-372,-372.-170,-170.97,97.275,275.278,278.129,129.-69,-69.-200,-200.-204,-204.-96,-96.48,48.143,143.146,146.69,69.-32,-32.-99,-99.-102,-102.-49,-49.21,21.67,67.69,69.34,34.-13,-13.-45,-45.-47,-47.-23,-23.9,9.31,31.33,33.17,17.-6,-6.-23,-23.-27,-27.-15,-15..");
else return -1;
return 1;
}




  int WandR(char* data,char de,char ch,unsigned char art,bool w)
  {
string se;
if(w)se+="WRITE ";
else se+="READ ";

se=se+mp[de]+' ';
if((de==0&&ch==2)||((de==1&&ch==9))||(de==2&&(ch==0||ch==4||ch==5))||(de==3&&(ch==0||ch==1)))ch*=-1;
if(ch>-1)
{int i=0;



        for (const auto& channel : channels[de]) {


cout<<channel.first<<endl;
        if(i==ch){se=se+t[de][ch]+' ';

            string cha = channel.first.substr(0, channel.first.find('_'));

                se+=cha +' '+channels[de][channel.first][art]+' ';

        break;}
        i++;
        }




}
else
{
  ch*=-1 ;
  int i=0;

  for (const auto& channel : channels[de]) {

        if(i==ch){

               /* if(channel.first=="debug")se+="DEBUG ";
                else if(channel.first=="buff")return -1;*/
                se+=channels[de][channel.first][art]+' ';

        break;}
        i++;
}
}
if(w)se+=to_string(strlen(data)+1);
se+="\r\n";
cout<<se;
int er=0;
if(w){
while(send(con,se.c_str(),se.length(),0)==-1){
    er++;
    if(er>100){cout<<"connection lost"<<endl;
            return -1;
    }

}er=0;
///////////////////////////////////////////////////////////////////////////////////////////////
while(send(con,data,strlen(data)+1,0)==-1){
    er++;
    if(er>100){cout<<"connection lost"<<endl;
            return -1;
    }
}
char ch[5];
er=recv(con,ch,to_string(strlen(data)).length(),0);

cout<<ch<<endl;
if(er==-1)
{
    cout<<"command not complete";
    return -1;
}else if(stoi(ch)<0)
{
   return stoi(ch);
}
}else{


while(send(con,se.c_str(),se.length(),0)==-1){
    er++;
    if(er>100){cout<<"connection lost1"<<endl;
            return -1;
    }}
  //  recany(d,data);
int U=0,e=0;
cout<<"dsd\n";
char da[8],da1[80];
do
{
  U=recv(con,da,4,0)  ;
  e++;





}while(U==-1&&e<100);



if(atoi(da)<1)return -1;



while(recv(con,da1,atoi(da),0)==-1){

};

cout<<">>>"<<atoi(da1)<<"<<<"<<endl;
}

return 1;
  }





int opentransfer(unsigned long long *s,sockaddr_in *add,bool rec)
    {
        s[0]=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    if (s[0] == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

         if (connect(s[0], (struct sockaddr*)add, sizeof(add)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(s[0]);

        return 1;
    }
char da[100]="OPEN iio:device2 3276800000003\r\n";
if (rec)da[15]++;
    printf("Connected to server!\n");
    int er=0;
    while(send(s[0],da,strlen(da),0)==-1)
    {
     er++;
      if(er>100)

      {
          cout<<"connection lost"<<endl;
          return -1;
      }
    }
    return 1;
    }

int sendun(unsigned long long *a,int m )
{int er=0;
    switch(m)
        {
       case 0:
          while( send(*a,"ZPRINT\r\n",8,0)==-1)
          {
              if(er>100){cout<<"connection lost";
                return -1;
              }
          }
        break;
       case 1:
           while(send(*a,"PRINT\r\n",7,0)==-1)
           {
              if(er>100){cout<<"connection lost";
                return -1;
              }
           }
        break;
       case 2:

        break;
        }
}
int recany(unsigned long long *a,char * da )
{
    char len[10];
    int er=0;
    er=recv(*a,len,7,0);
    int r,r2;
    if(er==-1){
        cout<<"not received1";
        return -1;
    }
    if(len[0]<30||len[0]>39){cout<<"kopljilhoi";
            return -1;
    }
    while(er<stoi(len)){
    r=recv(*a,da,stoi(len),0);
    if(r!=-1)er+=r;
    if(r==-1){r++;
    if(r>100){
        er=-1;
        break;
    }
    break;}
    }

     if(er==-1){
        cout<<"not received2";
        return -1;
    }
return 1;
}
int timeout(unsigned long long *a,int t)
{string s="TIMEOUT ";
s+=to_string(t);
s+="\r\n";
   int er=0;
   while(send(*a,s.c_str(),s.length(),0)==-1){
    er++;
    if(er<100){
        cout<<"connection lost"<<endl;
        return -1;
    }
   }
   recv(*a,NULL,2,0);
   return 1;

}
};
void start(){

    // Channel altvoltage1
    channels[0]["altvoltage1"] = {
        {0, "external"},
        {1, "fastlock_load"},
        {2, "fastlock_recall"},
        {3, "fastlock_save"},
        {4, "fastlock_store"},
        {5, "frequency"},
        {6, "frequency_available"},
        {7, "powerdown"}
    };

    // Channel voltage0 (input)
    channels[0]["voltage0_input"] = {
        {0, "bb_dc_offset_tracking_en"},
        {1, "filter_fir_en"},
        {2, "gain_control_mode"},
        {3, "gain_control_mode_available"},
        {4, "hardwaregain"},
        {5, "hardwaregain_available"},
        {6, "quadrature_tracking_en"},
        {7, "rf_bandwidth"},
        {8, "rf_bandwidth_available"},
        {9, "rf_dc_offset_tracking_en"},
        {10, "rf_port_select"},
        {11, "rf_port_select_available"},
        {12, "rssi"},
        {13, "sampling_frequency"},
        {14, "sampling_frequency_available"}
    };

    // Channel voltage3
    channels[0]["voltage3"] = {
        {0, "filter_fir_en"},
        {1, "raw"},
        {2, "rf_bandwidth"},
        {3, "rf_bandwidth_available"},
        {4, "rf_port_select_available"},
        {5, "sampling_frequency"},
        {6, "sampling_frequency_available"},
        {7, "scale"}
    };

    // Channel altvoltage0
    channels[0]["altvoltage0"] = {
        {0, "external"},
        {1, "fastlock_load"},
        {2, "fastlock_recall"},
        {3, "fastlock_save"},
        {4, "fastlock_store"},
        {5, "frequency"},
        {6, "frequency_available"},
        {7, "powerdown"}
    };

    // Channel voltage2 (output)
    channels[0]["voltage2_output"] = {
        {0, "filter_fir_en"},
        {1, "raw"},
        {2, "rf_bandwidth"},
        {3, "rf_bandwidth_available"},
        {4, "rf_port_select_available"},
        {5, "sampling_frequency"},
        {6, "sampling_frequency_available"},
        {7, "scale"}
    };

    // Channel temp0
    channels[0]["temp0"] = {
        {0, "in_temp0_input"}
    };

    // Channel voltage0 (output)
    channels[0]["voltage0_output"] = {
        {0, "filter_fir_en"},
        {1, "hardwaregain"},
        {2, "hardwaregain_available"},
        {3, "rf_bandwidth"},
        {4, "rf_bandwidth_available"},
        {5, "rf_port_select"},
        {6, "rf_port_select_available"},
        {7, "rssi"},
        {8, "sampling_frequency"},
        {9, "sampling_frequency_available"}
    };

    // Channel voltage2 (input)
    channels[0]["voltage2_input"] = {
        {0, "bb_dc_offset_tracking_en"},
        {1, "filter_fir_en"},
        {2, "gain_control_mode_available"},
        {3, "offset"},
        {4, "quadrature_tracking_en"},
        {5, "raw"},
        {6, "rf_bandwidth"},
        {7, "rf_bandwidth_available"},
        {8, "rf_dc_offset_tracking_en"},
        {9, "irf_port_select_available"},
        {10, "sampling_frequency"},
        {11, "sampling_frequency_available"},
        {12, "scale"}
    };
channels[0]["out"] = {
        {0, "voltage_filter_fir_en"}
    };
try{
channels[0]["debug"] = {
    {0, "calib_mode"},
    {1, "calib_mode_available"},
    {2, "dcxo_tune_coarse"},
    {3, "dcxo_tune_coarse_available"},
    {4, "dcxo_tune_fine"},
    {5, "dcxo_tune_fine_available"},
    {6, "ensm_mode"},
    {7, "ensm_mode_available"},
    {8, "filter_fir_config"},
    {9, "gain_table_config"},
    {10, "multichip_sync"},
    {11, "rssi_gain_step_error"},
    {12, "rx_path_rates"},
    {13, "trx_rate_governor"},
    {14, "trx_rate_governor_available"},
    {15, "tx_path_rates"},
    {16, "xo_correction"},
    {17, "xo_correction_available"},
    {18, "digital_tune"},
    {19, "calibration_switch_control"},
    {20, "multichip_sync"},
    {21, "gaininfo_rx2"},
    {22, "gaininfo_rx1"},
    {23, "bist_timing_analysis"},
    {24, "gpo_set"},
    {25, "bist_tone"},
    {26, "bist_prbs"},
    {27, "loopback"},
    {28, "initialize"},
    {29, "adi,bb-clk-change-dig-tune-enable"},
    {30, "adi,axi-half-dac-rate-enable"},
    {31, "adi,txmon-2-lo-cm"},
    {32, "adi,txmon-1-lo-cm"},
    {33, "adi,txmon-2-front-end-gain"},
    {34, "adi,txmon-1-front-end-gain"},
    {35, "adi,txmon-duration"},
    {36, "adi,txmon-delay"},
    {37, "adi,txmon-one-shot-mode-enable"},
    {38, "adi,txmon-dc-tracking-enable"},
    {39, "adi,txmon-high-gain"},
    {40, "adi,txmon-low-gain"},
    {41, "adi,txmon-low-high-thresh"},
    {42, "adi,gpo3-tx-delay-us"},
    {43, "adi,gpo3-rx-delay-us"},
    {44, "adi,gpo2-tx-delay-us"},
    {45, "adi,gpo2-rx-delay-us"},
    {46, "adi,gpo1-tx-delay-us"},
    {47, "adi,gpo1-rx-delay-us"},
    {48, "adi,gpo0-tx-delay-us"},
    {49, "adi,gpo0-rx-delay-us"},
    {50, "adi,gpo3-slave-tx-enable"},
    {51, "adi,gpo3-slave-rx-enable"},
    {52, "adi,gpo2-slave-tx-enable"},
    {53, "adi,gpo2-slave-rx-enable"},
    {54, "adi,gpo1-slave-tx-enable"},
    {55, "adi,gpo1-slave-rx-enable"},
    {56, "adi,gpo0-slave-tx-enable"},
    {57, "adi,gpo0-slave-rx-enable"},
    {58, "adi,gpo3-inactive-state-high-enable"},
    {59, "adi,gpo2-inactive-state-high-enable"},
    {60, "adi,gpo1-inactive-state-high-enable"},
    {61, "adi,gpo0-inactive-state-high-enable"},
    {62, "adi,gpo-manual-mode-enable-mask"},
    {63, "adi,gpo-manual-mode-enable"},
    {64, "adi,aux-dac2-tx-delay-us"},
    {65, "adi,aux-dac2-rx-delay-us"},
    {66, "adi,aux-dac2-active-in-alert-enable"},
    {67, "adi,aux-dac2-active-in-tx-enable"},
    {68, "adi,aux-dac2-active-in-rx-enable"},
    {69, "adi,aux-dac2-default-value-mV"},
    {70, "adi,aux-dac1-tx-delay-us"},
    {71, "adi,aux-dac1-rx-delay-us"},
    {72, "adi,aux-dac1-active-in-alert-enable"},
    {73, "adi,aux-dac1-active-in-tx-enable"},
    {74, "adi,aux-dac1-active-in-rx-enable"},
    {75, "adi,aux-dac1-default-value-mV"},
    {76, "adi,aux-dac-manual-mode-enable"},
    {77, "adi,aux-adc-decimation"},
    {78, "adi,aux-adc-rate"},
    {79, "adi,temp-sense-decimation"},
    {80, "adi,temp-sense-periodic-measurement-enable"},
    {81, "adi,temp-sense-offset-signed"},
    {82, "adi,temp-sense-measurement-interval-ms"},
    {83, "adi,elna-gaintable-all-index-enable"},
    {84, "adi,elna-rx2-gpo1-control-enable"},
    {85, "adi,elna-rx1-gpo0-control-enable"},
    {86, "adi,elna-bypass-loss-mdB"},
    {87, "adi,elna-gain-mdB"},
    {88, "adi,elna-settling-delay-ns"},
    {89, "adi,ctrl-outs-enable-mask"},
    {90, "adi,ctrl-outs-index"},
    {91, "adi,rssi-duration"},
    {92, "adi,rssi-wait"},
    {93, "adi,rssi-delay"},
    {94, "adi,rssi-unit-is-rx-samples-enable"},
    {95, "adi,rssi-restart-mode"},
    {96, "adi,fagc-adc-large-overload-inc-steps"},
    {97, "adi,fagc-power-measurement-duration-in-state5"},
    {98, "adi,fagc-rst-gla-if-en-agc-pulled-high-mode"},
    {99, "adi,fagc-rst-gla-en-agc-pulled-high-enable"},
    {100, "adi,fagc-rst-gla-large-lmt-overload-enable"},
    {101, "adi,fagc-rst-gla-large-adc-overload-enable"},
    {102, "adi,fagc-energy-lost-stronger-sig-gain-lock-exit-cnt"},
    {103, "adi,fagc-rst-gla-engergy-lost-sig-thresh-below-ll"},
    {104, "adi,fagc-rst-gla-engergy-lost-goto-optim-gain-enable"},
    {105, "adi,fagc-rst-gla-engergy-lost-sig-thresh-exceeded-enable"},
    {106, "adi,fagc-rst-gla-stronger-sig-thresh-above-ll"},
    {107, "adi,fagc-optimized-gain-offset"},
    {108, "adi,fagc-rst-gla-stronger-sig-thresh-exceeded-enable"},
    {109, "adi,fagc-use-last-lock-level-for-set-gain-enable"},
    {110, "adi,fagc-gain-index-type-after-exit-rx-mode"},
    {111, "adi,fagc-gain-increase-after-gain-lock-enable"},
    {112, "adi,fagc-final-overrange-count"},
    {113, "adi,fagc-lmt-final-settling-steps"},
    {114, "adi,fagc-lpf-final-settling-steps"},
    {115, "adi,fagc-lock-level-gain-increase-upper-limit"},
    {116, "adi,fagc-lock-level-lmt-gain-increase-enable"},
    {117, "adi,fagc-lp-thresh-increment-steps"},
    {118, "adi,fagc-lp-thresh-increment-time"},
    {119, "adi,fagc-allow-agc-gain-increase-enable"},
    {120, "adi,fagc-state-wait-time-ns"},
    {121, "adi,fagc-dec-pow-measurement-duration"},
    {122, "adi,agc-immed-gain-change-if-large-lmt-overload-enable"},
    {123, "adi,agc-immed-gain-change-if-large-adc-overload-enable"},
    {124, "adi,agc-gain-update-interval-us"},
    {125, "adi,agc-sync-for-gain-counter-enable"},
    {126, "adi,agc-dig-gain-step-size"},
    {127, "adi,agc-dig-saturation-exceed-counter"},
    {128, "adi,agc-lmt-overload-large-inc-steps"},
    {129, "adi,agc-lmt-overload-small-exceed-counter"},
    {130, "adi,agc-lmt-overload-large-exceed-counter"},
    {131, "adi,agc-adc-lmt-small-overload-prevent-gain-inc-enable"},
    {132, "adi,agc-adc-large-overload-inc-steps"},
    {133, "adi,agc-adc-large-overload-exceed-counter"},
    {134, "adi,agc-adc-small-overload-exceed-counter"},
    {135, "adi,agc-outer-thresh-low-inc-steps"},
    {136, "adi,agc-outer-thresh-low"},
    {137, "adi,agc-inner-thresh-low-inc-steps"},
    {138, "adi,agc-inner-thresh-low"},
    {139, "adi,agc-inner-thresh-high-dec-steps"},
    {140, "adi,agc-inner-thresh-high"},
    {141, "adi,agc-outer-thresh-high-dec-steps"},
    {142, "adi,agc-outer-thresh-high"},
    {143, "adi,agc-attack-delay-extra-margin-us"},
    {144, "adi,mgc-split-table-ctrl-inp-gain-mode"},
    {145, "adi,mgc-dec-gain-step"},
    {146, "adi,mgc-inc-gain-step"},
    {147, "adi,mgc-rx2-ctrl-inp-enable"},
    {148, "adi,mgc-rx1-ctrl-inp-enable"},
    {149, "adi,gc-use-rx-fir-out-for-dec-pwr-meas-enable"},
    {150, "adi,gc-max-dig-gain"},
    {151, "adi,gc-dig-gain-enable"},
    {152, "adi,gc-low-power-thresh"},
    {153, "adi,gc-dec-pow-measurement-duration"},
    {154, "adi,gc-lmt-overload-low-thresh"},
    {155, "adi,gc-lmt-overload-high-thresh"},
    {156, "adi,gc-adc-large-overload-thresh"},
    {157, "adi,gc-adc-small-overload-thresh"},
    {158, "adi,gc-adc-ovr-sample-size"},
    {159, "adi,gc-rx2-mode"},
    {160, "adi,gc-rx1-mode"},
    {161, "adi,update-tx-gain-in-alert-enable"},
    {162, "adi,tx-attenuation-mdB"},
    {163, "adi,rf-tx-bandwidth-hz"},
    {164, "adi,rf-rx-bandwidth-hz"},
    {165, "adi,qec-tracking-slow-mode-enable"},
    {166, "adi,dc-offset-count-low-range"},
    {167, "adi,dc-offset-count-high-range"},
    {168, "adi,dc-offset-attenuation-low-range"},
    {169, "adi,dc-offset-attenuation-high-range"},
    {170, "adi,dc-offset-tracking-update-event-mask"},
    {171, "adi,clk-output-mode-select"},
    {172, "adi,external-rx-lo-enable"},
    {173, "adi,external-tx-lo-enable"},
    {174, "adi,xo-disable-use-ext-refclk-enable"},
    {175, "adi,tx-lo-powerdown-managed-enable"},
    {176, "adi,trx-synthesizer-target-fref-overwrite-hz"},
    {177, "adi,rx1-rx2-phase-inversion-enable"},
    {178, "adi,tx-rf-port-input-select-lock-enable"},
    {179, "adi,rx-rf-port-input-select-lock-enable"},
    {180, "adi,tx-rf-port-input-select"},
    {181, "adi,rx-rf-port-input-select"},
    {182, "adi,split-gain-table-mode-enable"},
    {183, "adi,1rx-1tx-mode-use-tx-num"},
    {184, "adi,1rx-1tx-mode-use-rx-num"},
    {185, "adi,2rx-2tx-mode-enable"},
    {186, "adi,digital-interface-tune-fir-disable"},
    {187, "adi,digital-interface-tune-skip-mode"},
    {188, "adi,tx-fastlock-pincontrol-enable"},
    {189, "adi,rx-fastlock-pincontrol-enable"},
    {190, "adi,rx-fastlock-delay-ns"},
    {191, "adi,tx-fastlock-delay-ns"},
    {192, "adi,tdd-skip-vco-cal-enable"},
    {193, "adi,tdd-use-dual-synth-mode-enable"},
    {194, "adi,debug-mode-enable"},
    {195, "adi,ensm-enable-txnrx-control-enable"},
    {196, "adi,ensm-enable-pin-pulse-mode-enable"},
    {197, "adi,frequency-division-duplex-independent-mode-enable"},
    {198, "adi,frequency-division-duplex-mode-enable"},
    {199, "direct_reg_access"}
};}
catch(const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return ;
    }
//cout<<channels[0]["debug"].max_size();

    // Populate the map with the given data
    channels[1]["voltage5"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage0"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage4"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["temp0"] = {
        {0, "offset"},
        {1, "raw"},
        {2, "scale"}
    };
    channels[1]["voltage7"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage1"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage2"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage3"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage8"] = {
        {0, "raw"},
        {1, "scale"}
    };
    channels[1]["voltage6"] = {
        {0, "raw"},
        {1, "scale"}
    };
 channels[1]["zero"] = {{0,"sampling_frequency"}};

    channels[2]["voltage0"] = {
        {0, "calibphase"},
        {1, "calibscale"},
        {2, "sampling_frequency"},
        {3, "sampling_frequency_available"}
    };
    channels[2]["voltage1"] = {
        {0, "calibphase"},
        {1, "calibscale"},
        {2, "sampling_frequency"},
        {3, "sampling_frequency_available"}
    };
    channels[2]["altvoltage3"] = {
        {0, "frequency"},
        {1, "phase"},
        {2, "raw"},
        {3, "frequency"},
        {4, "scale"}
    };
    channels[2]["altvoltage1"] = {
        {0, "frequency"},
        {1, "phase"},
        {2, "raw"},
        {3, "sampling_frequency"},
        {4, "scale"}
    };
    channels[2]["altvoltage0"] = {
        {0, "frequency"},
        {1, "phase"},
        {2, "raw"},
        {3, "frequency"},
        {4, "scale"}
    };
    channels[2]["altvoltage2"] = {
        {0, "frequency"},
        {1, "phase"},
        {2, "raw"},
        {3, "frequency"},
        {4, "scale"}
    };
channels[2]["BUFFER"] = {
   {0,"data_available" },
   {1,"length_align_bytes" }
   };
  channels[2]["DEBUG_"]=
   {
    {0,"watermark" },
    {1,"direct_reg_access" }
};

    channels[3]["voltage0"] = {
        {0, "calibbias"},
        {1, "calibphase"},
        {2, "calibscale"},
        {3, "samples_pps"},
        {4, "sampling_frequency"},
        {5, "sampling_frequency_available"}
    };
    channels[3]["voltage1"] = {
        {0, "calibbias"},
        {1, "calibphase"},
        {2, "calibscale"},
        {3, "samples_pps"},
        {4, "sampling_frequency"},
        {5, "sampling_frequency_available"}
    };

    // Populate the map for buffer attributes under the "buff" channel
    channels[3]["BUFFER"] = {
        {0, "data_available"},
        {1, "length_align_bytes"},
        {2, "watermark"}
    };

    // Populate the map for debug attributes under the "debug" channel
    channels[3]["DEBUG"] = {
        {0, "pseudorandom_err_check"},
        {1, "direct_reg_access"}
    };

/*for(const auto s :channels[0]["debug"])

cout<<s.first<<'-'<<s.second<<endl;
}*/}
int main() {



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


A.intwrite("192.168.2.1",32000);


A.intread("192.168.2.1",32000);


//A.WandR("3000000000",3,0,0,0);
comp f[32000];
unsigned char te[8001];

for(int i=0;i<8001;i++)te[i]=0x02;
    //sine(f,32000,4,1,45*3.141/180.0);
   QPSk(f,te,32000,4);
   char * buf=(char *)f;
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
getchar();
//cout<<A.writebuff(recvBuffer,32000*4)<<endl;

A.WandR("2400000000",0,1,5,1);
//A.WandR("20000000",2,6,2,1);

while(1){
        A.writebuff(buf,32000*4);
       // usleep(30);
A.WandR("3000000000",2,0,0,0);

}

for(int i ;i<32000;i++)
{
    printf("%x   %x   ",z[i].i,z[i].Q);
}
short plot[32000];
//com2mag(32000,plot,z);
for(int i ;i<32000;i++)
{
    printf("%x,  ",plot[i]);
}
//A.WandR("3000000000",0,0,5,1);
//A.WandR("1000000",3,2,4,1);
//A.WandR("k",0,2,8,1);
//A.WandR("1",0,3,0,1);
//A.WandR("slow_attack",0,5,2,1);
//A.WandR(dd,0,0,8,0);


    closesocket(A.con);
    WSACleanup();

    return 0;
}
