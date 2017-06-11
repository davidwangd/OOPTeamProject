//coder : jxt
#include "CPPToken.h"
#include "Analyzer.h"

bool cmpp(int a,int b)
{
	return HB[a]<HB[b];
}

double Analyzer::Hash()
{
	int Lena,Lenb,Lmax,Mi;
	int *Marka; int *Markb; int *Hasha; int *Hashb;
	Lena=Ha.size();
	Lenb=Hb.size();
	Lmax=max(Lena,Lenb);
	Marka=new int[Lena+1];
	Markb=new int[Lenb+1];
	Hasha=new int[Lena+1];
	Hashb=new int[Lenb+1];
	Hasha[0]=Hashb[0]=0;
	for(int i=1;i<=Lmax;i++){
		Marka[i]=Markb[i]=0;
		Hasha[i]=((long long)Hasha[i-1]*Ad%Mo+Ha[i-1])%Mo;
		Hashb[i]=((long long)Hashb[i-1]*Ad%Mo+Hb[i-1])%Mo;
	}
	Mi=1;
	for(int i=1;i<=M;i++)Mi=(long long)Mi*Ad%Mo;
	
	int ha,tot;
	int *HA; int *B; int **Loca;
	HA=new int[Lena-M+2];HB=new int[Lenb-M+2];B=new int[Lenb-M+2];
	tot=0;
	HH.clear();
	for(int i=1;i<=Lmax-M+1;i++){
		if(i<=Lenb-M+1){
			ha=((long long)Hashb[i+M-1]-(long long)Hashb[i-1]*Mi%Mo)%Mo;
			ha=(ha+Mo)%Mo;
			if(HH[ha]==0)HH[ha]=++tot;
			HB[i]=HH[ha];
		}
		if(i<=Lena-M+1){
			ha=((long long)Hasha[i+M-1]-(long long)Hasha[i-1]*Mi%Mo)%Mo;
			ha=(ha+Mo)%Mo;
			if(HH[ha]==0)HH[ha]=++tot;
			HA[i]=HH[ha];
		}
	}
	for(int i=1;i<=Lenb-M+1;i++)B[i]=i;
	sort(B+1,B+Lenb-M,cmpp);
	Loca=new int*[tot+1];
	for(int i=1;i<=tot;i++){
		Loca[i]=new int[2];
		Loca[i][0]=Loca[i][1]=0;
	}
	for(int i=1;i<=Lenb-M+1;i++)if(Loca[HB[B[i]]][0]==0)Loca[HB[B[i]]][0]=i;
	for(int i=Lenb-M+1;i>=1;i--)if(Loca[HB[B[i]]][1]==0)Loca[HB[B[i]]][1]=i;
	delete Hasha; delete Hashb;
	
	int Max,Len,Ans,Ms;
	int **Match;
	Match=new int*[Lmax+1];
	for(int i=0;i<=Lmax;i++)Match[i]=new int[2];
	Ms=0;
	Ans=0;
	bool p;
	do{
		Max=M;
		for(int i=1;i<=Lena-M+1;i++)if(Marka[i]==0&&Loca[HA[i]][0]!=0){
			for(int j=Loca[HA[i]][0];j<=Loca[HA[i]][1];j++)if(Markb[B[j]]==0){
				Len=1;
				while(i+Len<=Lena&&B[j]+Len<=Lenb&&Marka[i+Len]==0&&Markb[B[j]+Len]==0&&Ha[i+Len-1]==Hb[B[j]+Len-1])Len++;
				if(Len>Max){
					Max=Len;
					Ms=1;
					Match[1][0]=i;Match[1][1]=B[j];
				}
				else if(Len==Max){
					p=true;
					for(int k=1;k<=Ms;k++){
						if(i>=Match[k][0]&&i<=Match[k][0]+Len-1)p=false;
						if(B[j]>=Match[k][0]&&B[j]<=Match[k][0]+Len-1)p=false;
					}
					if(p){
						Ms++;
						Match[Ms][0]=i;
						Match[Ms][1]=B[j];
					}
				}
			}
		}
		for(int i=1;i<=Ms;i++){
			for(int j=0;j<Max;j++){
				Marka[Match[i][0]+j]=1;
				Markb[Match[i][1]+j]=1;
			}
			Ans=Ans+Max;
		}
		Ms=0;
	}while(Max>M);
	delete Marka;delete Markb;delete HA;delete HB;delete B;
	for(int i=0;i<=tot;i++)delete Loca[i]; delete Loca;
	for(int i=0;i<=Lmax;i++)delete Match[i]; delete Match;
	return (double)Ans*2.0/(double)(Lena+Lenb);
}

pd Analyzer::check(const vector<Token *> &A,const vector<Token *> &B)
{
	pd AA;
	int Lena,Lenb,Lmax;
	Lena=A.size();Lenb=B.size();Lmax=max(Lena,Lenb);
	Ha.clear();
	Hb.clear();
	for(int i=0;i<Lmax;i++){
		if(i<Lena)Ha.push_back(A[i].Value());
		if(i<Lenb)Hb.push_back(B[i].Value());
	}
	AA.first=Hash();
	for(int i=0;i<Lmax;i++){
		if(i<Lena)Ha[i]=A[i].ApproximateValue();
		if(i<Lenb)Hb[i]=B[i].ApproximateValue();
	}
	AA.second=Hash();
	return AA;
}