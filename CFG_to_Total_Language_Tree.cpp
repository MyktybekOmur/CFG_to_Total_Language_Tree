#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agaclar {
    struct agaclar *childs[1000];
    char string[16];
    int ch_t=0;
}agac;

typedef struct bilgiler{
	char cfg_h[2];
	char cfg_s[100];
	int sayi;
	struct bilgiler *next;
}bilgi;

typedef struct sonuclar {
    struct sonuclar *next;
    char veri[10];
    int tekrar_s=0;
}sonuc;

agac *node=NULL,*temp2=NULL;
sonuc *ilk=NULL,*temp=NULL,*yeni;
bilgi *ilk_b=NULL,*temp_b=NULL,*yeni_b;
//Kullanicidan aldigimiz CFG listeye ekledim
void ekle2(char *string,int sayi){
	int i,kontrol=0,j=0;
	char *gecici;
	gecici=(char *) malloc(sizeof(char));
	for(i=0;string[i]!=NULL;i++){
		
		if(i>3){
			gecici[j]=string[i];
			j++;
		}
		
	}
	gecici[j]='\0';
	
	if(ilk_b==NULL){
		ilk_b = (bilgi*) malloc(sizeof (bilgi));
		strcpy(ilk_b->cfg_s,gecici);
		ilk_b->cfg_h[0]=string[0];
		ilk_b->cfg_h[1]='\0';
		ilk_b->sayi=sayi;
		ilk_b->next=NULL;
	}else{
			yeni_b=(bilgi*) malloc(sizeof (bilgi));
			strcpy(yeni_b->cfg_s,gecici);
			yeni_b->cfg_h[0]=string[0];
			yeni_b->cfg_h[1]='\0';
			yeni_b->sayi=sayi;
			temp_b=ilk_b;
			while(temp_b->next!=NULL){
				temp_b=temp_b->next;
			}
			temp_b->next=yeni_b;
			yeni_b->next=NULL;
			temp_b=temp_b->next;
		}		
	
}
//Agacin yapraklarindaki sonulari yeni bagli listeye ekledim
void ekle(char *string){
	int i,kontrol=0;
	
	if(ilk==NULL){
		ilk = (sonuc*) malloc(sizeof (sonuc));
		strcpy(ilk->veri,string);
		ilk->next=NULL;
	}else{
		temp=ilk;
		while(temp!=NULL){
			if(strcmp(temp->veri,string)==0){
			
				kontrol=0;
				temp->tekrar_s=1;
				break;
			}else kontrol=1;
			temp=temp->next;
		}
		temp=ilk;
		if(kontrol==1){
			yeni=(sonuc*) malloc(sizeof (sonuc));
			strcpy(yeni->veri,string);
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=yeni;
			yeni->next=NULL;
		}
		
		
		
		
	}
}
//Sonucu yazdir
void listele(){
	temp=ilk;
	printf("Uretilen kelimeler:\n");
	while(temp!=NULL){
		printf("%s ",temp->veri);
		temp=temp->next;
	}
	printf("\n");
	temp=ilk;
	printf("\nTekrarlanan kelimeler:\n");
	while(temp!=NULL){
		if(temp->tekrar_s==1)
		printf("%s ",temp->veri);
		temp=temp->next;
	}
	printf("\n218-219 satiri aktiflestirirsek agac yapisini net gorebiliriz!\n");
}

//Yeni olusan duyum CFGsi
char *childs_cfg(char *string,int kac,char *b,int sayi){

	char *gecici;
	gecici=(char *) malloc(100*sizeof(char));
	int j=0,z=0,w=0;
	for(int k=0;k<sayi;k++){
		j=0;
		while(string[j]!='\0')
		{
			if(j==kac)
			{
				for(int q=w;b[q]!=NULL;q++)
				{
					if(b[q]!='|'){
						gecici[z]=b[q];
					    z++;
					}  
					else {
						w=q;
						w++;
						break;	
					}
				}
			}else
			{
				gecici[z]=string[j];
				z++;
			}
			j++;
				
		}
		gecici[z]='|';
		z++;
	}
	gecici[z]='\0';
	return gecici;
	
}

//Kelime turetme fonksiyonu
void kelime_turet(agac *temp4,char *al,char *cfg,char *x,int ch){
	int n=0,t=0,ch_s=0,kon=0;
	char *gecici,*gecici2,chil_cfg[1];

	for(int i=0;i<ch;i++){		
		temp4->childs[i]=(agac*)malloc(sizeof(agac));
		t=0;
		ch_s=0;
		for(int j=n;cfg[j]!=NULL;j++)
		{
			if(cfg[j]!='|')
			{
				if(cfg[j]>64 && cfg[j]<91)
				{
					kon=1;
					temp_b=ilk_b;
					while(temp_b!=NULL)
					{
						if(temp_b->cfg_h[0]==cfg[j])
						{
							chil_cfg[0]=cfg[j];
						
							break;
						}
						temp_b=temp_b->next;
					}
					
					ch_s++;
					temp4->childs[i]->ch_t=ch_s;
				 }
				temp4->childs[i]->string[t]=cfg[j];
				t++;
			}else {
				temp4->childs[i]->string[t]='\0';
			
				break;	
				
			}
		
			n++;
		}
		if(ch_s>0){
			gecici=(char *) malloc(100*sizeof(char));
			gecici2=(char *) malloc(100*sizeof(char));
			int j=0,w=0,z=0,kon=0,s=0,dizi[10];
			while(temp4->childs[i]->string[j]!='\0'){
				
					if(temp4->childs[i]->string[j]==chil_cfg[0]){
						dizi[s]=j;s++;
					}
					j++;
						
				}		
			for(int k=0;k<ch_s;k++){
				gecici=childs_cfg(temp4->childs[i]->string,dizi[k],temp_b->cfg_s,temp_b->sayi);
				for(j=0;gecici[j]!=NULL;j++,z++)gecici2[z]=gecici[j];
				
			}
			gecici2[z]='\0';		
			//printf("%s ",temp4->childs[i]->string);
			//printf("duyumunun child sayisi %d, childs: %s\n",ch_s*2,gecici2);
			temp4=temp4->childs[i];
			 kelime_turet(temp4,al,gecici2,temp_b->cfg_s,ch_s*2);
	
		}else{
			ekle(temp4->childs[i]->string);
		}
		
		n++;
	
	}

	
}




int main(){
	int j=0,k=0,say=0;
	char *alfabe,input[50],cfg[50],*x;
	alfabe=(char *) malloc(sizeof(char));
	
	printf("Alfabe(Or:a,b,X): ");scanf("%s",alfabe);
	printf("CFG giriniz(Or:S-->aa|bX|aXX,X-->ab|b): ");scanf("%s",input);

	for(int i=0;input[i]!=NULL;i++){
		if(input[i]!=',' && input[i+1]!=NULL){
			if(input[i]=='|')say++;
			cfg[j]=input[i];
			j++;
		}else{
			if(input[i+1]==NULL){
				cfg[j]=input[i];j++;
			}
			cfg[j]='\0';
			ekle2(cfg,say+1);
			j=0; say=0;
		}
		
	}

	node=(agac *)malloc(sizeof(agac));
	temp2=node;
	
	kelime_turet(temp2,alfabe,ilk_b->cfg_s,ilk_b->next->cfg_s,ilk_b->sayi);
	listele();
	
	return 0;	
}
