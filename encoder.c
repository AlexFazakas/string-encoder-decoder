#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct sircomplex
	{
//Aceasta structura este cea folosita la task-ul 1.3(rearanjare).
//In sir memorez subsirul, iar in c voi memora complexitatea obtinuta drept
//media codurilor ASCII ale caracterelor.
	char *sir;
	double c;
	};
void rearanjare(struct sircomplex v[],int n)
{//In aceasta functie obtin sirul (*rearanjat) din alaturarea subsirurilor
//in ordinea 0,n-1,1,n-2,2 etc.
	int i=0,j=n-1;
	char *rearanjat;
	rearanjat=(char*)malloc(5000*sizeof(char));
	if(n%2==1)
		{	while(i!=j)
			{
			strcat(rearanjat,v[i].sir);
			strcat(rearanjat,v[j].sir);
			i++;
			j--;
			}
		strcat(rearanjat,v[i].sir);
		}
	else
		for(i=0;i<n/2;i++)
		{
		strcat(rearanjat,v[i].sir);
		strcat(rearanjat,v[n-i-1].sir);
		}
	printf("%s\n",rearanjat);
	if(strlen(rearanjat)!=0)
		free(rearanjat);
}
void sortare(struct sircomplex v[],int n)
{//Aceasta functie sorteaza un vector de tip "struct sircomplex"
//dupa componenta double c, reprezentand complexitatea unui subsir.
	int sem,i;
	struct sircomplex aux;
	do
		{sem=0;
		for(i=0;i<(n-1);i++)	
			if(v[i].c<v[i+1].c)
				{
				aux=v[i];
				v[i]=v[i+1];
				v[i+1]=aux;
				sem=1;
				}
			else
				if(v[i].c==v[i+1].c)
					if(strcmp(v[i].sir,v[i+1].sir)>0)
					{
		//Aici verific daca 2 elemente au aceeasi compelxitate.
		//Daca se intampla asta, le compar cu strcmp
		//Si le sortez lexicografic.
					aux=v[i];
					v[i]=v[i+1];
					v[i+1]=aux;
					sem=1;
					}
		
		}
	while(sem!=0);
}
void ataseaza_numar(int x,char *rezultat)
{//Aceasta functie ataseaza un numar primit ca parametru
//la sirul (*rezultat).
	char b;
	int aux=0,c;
	while(x!=0)
		{
//Aici fac inversul numarului pentru a il introduce corect.
//Fac asta deoarece am considerat ca
// era mai greu sa obtin cifrele in ordine inversa.
		c=x%10;
		aux=aux*10+c;
		x=x/10;
		}
	while(aux!=0)
		{
//Aici introduc numarul (inversat) in vectorul rezultat.
		b=aux%10+48;
//Acest b este codul ascii al numarului in sine,
//obtinut prin adunarea lui '0' la numarul in sine.
		rezultat[strlen(rezultat)]=b;
		aux=aux/10;
		}
	rezultat[strlen(rezultat)]=0;
//Ma asigur ca terminatorul de sir este pus.
}
void prelucrare_caractere(char *v,char *rezultat)
{//Aceasta functie prelucreaza caracterele dupa cum urmeaza sa detaliez:
	if(strlen(rezultat)==0)
		strcpy(rezultat,v);
//Am considerat ca este mai simplu sa adaug direct caracterul
//daca sirul (*rezultat) este nul.
	else if(strlen(rezultat)==1)
		{char d;
		d=rezultat[0];
		rezultat[1]=d;
		rezultat[2]=v[0];
		rezultat[3]=d;
		rezultat[4]=0;
//Similar cu mai sus, daca este un singur caracter in (*rezultat)
//Doar realizez manual prelucrarea pentru caracterul curent.
		}
	else
		{
		int x,max=0,min=10000,i,numaraparitii[150];
		char max2,min2;
		for(i=31;i<140;i++)
			numaraparitii[i]=0;
		for(i=0;i<strlen(rezultat);i++)
			{
			x=rezultat[i];
			numaraparitii[x]++;
			}
//Metoda pe care o folosesc aici ar fi urmatoarea:
//Folosesc un vector de intregi numit numaraparitii pentru a afla
//caracterele care apar de cele mai multe, respectiv putine ori.
//Aceste caractere le voi concatena manual la sfarsitul lui rezultat
//impreuna cu caracterul curent, in ordinea ceruta.
		for(i=0;i<strlen(rezultat);i++)
			{x=rezultat[i];
				if(numaraparitii[x]>0)
					{
					if(numaraparitii[x]>max)
						{max=numaraparitii[x];
						max2=rezultat[i];
						}
					if(numaraparitii[x]<min)
						{min=numaraparitii[x];
						min2=rezultat[i];
						}
					}
			}
		//Am aflat caracterele care apar de cele mai multe,
		//respectiv de cele mai putine ori in sirul rezultat.
		rezultat[strlen(rezultat)]=max2;
		rezultat[strlen(rezultat)]=0;
		strcat(rezultat,v);
		rezultat[strlen(rezultat)]=min2;
		rezultat[strlen(rezultat)+1]=0;
		//Adaug in sirul rezultat ceea ce mi se cere.
		}
}
int permutare_minima(int x,int k)
{//Functia aceasta calculeaza valoarea permutarii minime.
//Primeste ca argument si numarul de cifre al numarului pentru
//a sti numarul maxim de permutari posibile.
//Sunt puse toate cifrele numarului intr-un vector, apoi
//obtin toate permutarile circulare posibile si minimul este retinut in min.
//Minimul obtinut este apoi concatenat la (*rezultat) folosind
//functia definita mai sus.
	int putere,l,min=x,aux,n,j,v[100],c,i=0;
	while(x!=0)
		{
		c=x%10;
		v[i]=c;
		i++;
		x=x/10;
		}
	n=i;
	for(j=0;j<k-1;j++)
		{
		c=0;
		for(i=n-1;i>=0;i--)
		//Aici am pus si un for pentru obtinerea puterii lui 10.
			{putere=1;
				for(l=0;l<i;l++)
					putere=putere*10;
			c=c+v[i]*putere;
			}
		if(c<min)
			min=c;
		aux=v[n-1];
		for(i=(n-1);i>0;i--)
			v[i]=v[i-1];
		v[0]=aux;
		}
	return min;
}
int permutare_maxima(int x,int k)
{//Aceasta functie este similara cu permutare_minima de mai sus.
//Similar, obtin cifrele numarului, apoi toate permutarile circulare
//si memorez maximul intr-o variabila integer "max".
	int putere,l,max=0,aux,n,j,v[100],c,i=0;
	while(x!=0)
		{
		c=x%10;
		v[i]=c;
		i++;
		x=x/10;
		}
	n=i;
	for(j=0;j<k;j++)
		{
		c=0;
		for(i=n-1;i>=0;i--)
		//Din nou, un for pentru puterile lui 10.	
			{putere=1;
				for(l=0;l<i;l++)
					putere=putere*10;
			c=c+v[i]*putere;
			}
		if(c>max)
			max=c;
		aux=v[n-1];
		for(i=(n-1);i>0;i--)
			v[i]=v[i-1];
		v[0]=aux;
		}
	return max;
}
void intoarcere(char *s)
{//Aceasta functie obtine in (*intoarcere) inversul unui sir primit
//ca argument. Am scris aceasta functie pentru ca nu puteam folosi strrev.
//Din intoarcere, copiez inversul sirului in sirul initial.
	char *intoarcere;
	int i;
	intoarcere=(char*)malloc(100*sizeof(char));
	for(i=0;i<strlen(s);i++)
		intoarcere[strlen(s)-i-1]=s[i];
	intoarcere[strlen(s)]=0;
	strcpy(s,intoarcere);
	free(intoarcere);
}
void prelucrare_numere(char *v,char *rezultat)
{//Aceasta functie prelucreaza numerele conform cerintei.
//Numarul este obtinut din codul ascii asociat folosind functia atoi.
//Daca este negativ, acesta este trecut in modul si apoi se obtine
//permutarea minima, altfel se obtine cea maxima. Permutarea este apoi
//atasata sirului (*rezultat)
	int x,y,lungime;
	x=atoi(v);
	lungime=strlen(v);
	if(x<0)
		{
		x=-x;
		y=permutare_minima(x,lungime);
		}
	else y=permutare_maxima(x,lungime);
	ataseaza_numar(y,rezultat);
}
int divizor(int n)
{//Aceasta functie calculeaza cel mai mare divizor propriu
//al unui numar dat ca parametru.
	int i;
	for(i=n/2;i>1;i--)
		if(n%i==0)
			return i;
	return 1;
}
int citire(char **vector, char s[])
{//Aceasta functie citeste siruri pana la intalniarea lui "END"
	int i=0;
	fgets(s,100,stdin);
	while((strcmp(s,"END\n")!=0)&&(strcmp(s,"END")!=0)) 
		//Citesc pana la END
		{
		s[strlen(s)-1]=0;
//Fgets ia si \n asa ca il tai manual de la sfarsitul fiecarui sir.
		vector[i]=(char*)malloc((strlen(s)+1)*sizeof(char));
		strcpy(vector[i],s);
		i++;
		fgets(s,100,stdin);
		}
	return i;
}
int tip_sir(char *v)
{//Aceasta functie determina tipul de sir(cuvant, numar sau caracter)
	//Conventiile sunt: 0=caracter;1=numar;2=cuvant;
	char *litere;
	litere=(char*)malloc(100*sizeof(char));
strcpy(litere,"!\"#$%&'()*+`./:;<=>?@[]\\^_{|}~ABCDEFGHIJKLMNOPRSTUVWXYZ");
strcat(litere,"abcdefghijklmnopqrstuvwxyz");
	litere[strlen(litere)]=0;
	//Testez intai daca este caracter:
	if(strlen(v)==1)
		if(*v<48 || *v>57)
			{free(litere);
			return 0;}
		else
			{free(litere);
			return 1;}
			//Daca nu este caracter, atunci este numar.
	else
		if(strpbrk(v,litere)!=0) //Verific daca sirul contine litere*.
			{free(litere);
			return 2;}
		else 
			{free(litere);
			return 1;
			}
			//Daca nu contine litere* si nu este caracter,
			// este numar.
//*=impropriu spus litere
}
void prelucrare_cuvinte(char *v,char *rezultat)
{//Aceasta functie realizeaza prelucrarea cuvintelor conform cerintei.
//Afla divizorul, depunde primele d caractere intr-un auxiliar, apoi
//in auxiliarul 2 va depunde restul cuvantului, inversat la nevoie.
//Cele 2 auxiliare sunt apoi concatenate.
	char *aux,*aux2;
	aux=(char*)calloc(52,sizeof(char));
	aux2=(char*)calloc(52,sizeof(char));
	strcpy(aux2,v+divizor(strlen(v)));
	if(strpbrk(v,"0123456789")!=0)
		{
		strncpy(aux,v,divizor(strlen(v)));
		intoarcere(aux2);
		aux[strlen(aux)+1]=0;
		strcat(aux2,aux);
		strcat(rezultat,aux2);
		}
	else 
		{
		strncpy(aux,v,divizor(strlen(v)));
		aux[strlen(aux)+1]=0;
		strcat(aux2,aux);
		strcat(rezultat,aux2);
		}
	free(aux);
	free(aux2);
}
int main()
{
	char **vector,*rezultat,s[100];
	int x,j,k,r,n,i,cuvinte=0,caractere=0,numere=0;
	//Vector va fi un vector de pointeri, fiecare pointand
	//cate un sir. In s voi citi fiecare cuvant,
	//inainte de a il muta in vector.
	rezultat=(char*)malloc(5003*sizeof(char));
	vector=(char**)malloc(110*sizeof(char*));
	n=citire(vector,s);
	r=atoi(vector[n-1]); //Numarul citit inaintea lui END.
	n--; //Fac asta pentru a nu lua in considerare n-ul citit.
	for(i=0;i<n;i++)
		if(tip_sir(vector[i])==0)
			caractere++;
		else if(tip_sir(vector[i])==1)
			numere++;
			else cuvinte++;
	printf("%i %i %i\n",cuvinte,caractere,numere);
	//Printam numarul de cuvinte, caractere, respectiv numere.
	for(i=0;i<n;i++)
		if(tip_sir(vector[i])==2)
			prelucrare_cuvinte(vector[i],rezultat);
		else if(tip_sir(vector[i])==0)
			prelucrare_caractere(vector[i],rezultat);
		else prelucrare_numere(vector[i],rezultat);
	printf("%s\n",rezultat);
	//Prelucram fiecare sir in functie de tip.
	int lr;
	lr=(strlen(rezultat)/r);
	//Variabila lr imi va spune cate elemente pun in fiecare subsir.
	x=strlen(rezultat);
	struct sircomplex v[r+1];
	for(i=0;i<(r-1);i++)
			{
			v[i].sir=(char*)malloc((lr+1)*sizeof(char));
			strncpy(v[i].sir,(rezultat+i*lr),lr);
			v[i].sir[strlen(v[i].sir)]=0;
			//Pun terminator de sir    ^
			//rezultat=rezultat+lr;
			}
	v[i].sir=(char*)malloc((strlen(rezultat+i*lr)+1)*sizeof(char));
	strcpy(v[i].sir,rezultat+i*lr);
//Am obtinut astfel vectorul cu subsirurile cerute.
	for(j=0;j<=i;j++)
		{
		v[j].c=0;
			for(k=0;k<strlen(v[j].sir);k++)
				{
				x=v[j].sir[k];
				v[j].c+=x;
				}
		x=strlen(v[j].sir);
		v[j].c/=x;
		}
//Atasez fiecarui v[i].sir complexitatea v[i].c
	sortare(v,i+1);
	rearanjare(v,i+1);
//Sortare si rearanjare pentru realizarea cerintei 1.3.
//Mai departe eliberez toata memoria alocata:
	for(j=0;j<r;j++)
		free(v[j].sir);
	for(j=0;j<=n;j++)
		free(vector[j]);
	free(vector);
	free(rezultat);
	return 0;
}
