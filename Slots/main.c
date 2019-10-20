#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

float multiplier, cash, castig_temp=0;
int bet, okfinal, slot[3], nr_slots_castig=0, carte;
char char_input[20], fruct[3][20], char_carte[20], ghicire[20];

void start() //cash initial
{
    cash=1000;
    printf("Suma initiala este de 1000.00 credite.\nDoriti sa schimbati? ");
    scanf("%s", char_input);
    if(char_input[0]=='n')
        printf("Suma initiala nu a fost schimbata!\n");
    else if(char_input[0]=='y' || char_input[0]=='d')
    {
        printf("Va rog sa introduceti o noua suma: ");
        scanf("%f", &cash);
        printf("Suma initiala este acum de %.2f credite.\n", cash);
    }
    else
    {
        printf("Eroare de input! Suma initiala nu a fost schimbata.\n");
        start();
    }
}

void generare_slots(int slot[])
{
    int r, i;
    srand(time(NULL));
    for(i=0; i<3; i++)
    {
        r=rand()*rand();
        r=1+r%130;
        slot[i]=r;
    }
}

int generare_carte()
{
    int r;
    srand(time(NULL));
    r=rand()*rand();
    r=1+r%100;
    return r;
}

void identificare_carte(int x)
{
    if(x>=1 && x<=50)
        strcpy(char_carte, "ROSIE");
    else if(x>=51 && x<=100)
        strcpy(char_carte, "NEAGRA");
}

void afisare_carte(int carte)
{
    printf("%s", char_carte);
}

void gamble(float castig_temp)
{
    char carte_input[20];
    printf("Gamble? ");
    scanf("%s", carte_input);
    if(carte_input[0]=='d' || carte_input[0]=='y')
    {
        carte=generare_carte();
        printf("ROSIE/NEAGRA?  ");
        scanf("%s", ghicire);
        identificare_carte(carte);
        printf("Cartea afisata: ");
        afisare_carte(carte);
        printf("\n");
        if((ghicire[0]=='r' && char_carte[0]=='R') || (ghicire[0]=='n' && char_carte[0]=='N'))
        {
            castig_temp*=2;
            printf("Felicitari! Castigul este acum de %.2lf credite.\n", castig_temp);
            gamble(castig_temp);
        }
        else
        {
            printf("Ai pierdut!\n");
        }
    }
    else
    {
        printf("No gamble.\n");
        cash+=castig_temp;
    }
}

void void_bet() //bet initial
{
    int ok=1;
    while(ok)
    {
        printf("Introduceti betul: ");
        scanf("%d", &bet);
        ok=0;
        if(bet>cash)
        {
            printf("\nBetul este mai mare decat suma de credite!\n");
            ok=1;
        }
    }
    printf("Betul este acum de %d credite.\n", bet);
}

void schimbate_bet()
{
    printf("\nDoriti sa schimbati betul? ");
    scanf("%s", char_input);
    if(char_input[0]=='y' || char_input[0]=='d')
        void_bet();
    else if(char_input[0]=='n')
        printf("Betul nu a fost schimbat.\n");
    else
    {
        printf("Eroare de mesaj!\n");
        schimbate_bet();
    }
}

void afisare_credit(float cash)
{
    printf("Suma credite: %.2f\n", cash);
}

void afisare_bet(int bet)
{
    printf("Bet: %.d\n", bet);
}

void identificare(int x, int j) //ce fruct ii
{
    if(x>=1 && x<=10)
        strcpy(fruct[j], "SEVEN");
    else if(x>=11 && x<=25)
        strcpy(fruct[j], "WMLON");
    else if(x>=26 && x<=40)
        strcpy(fruct[j], "GRAPE");
    else if(x>=41 && x<=65)
        strcpy(fruct[j], "ORANG");
    else if(x>=66 && x<=95)
        strcpy(fruct[j], "LEMON");
    else if(x>=96 && x<=130)
        strcpy(fruct[j], "CHERY");
}

void afisare_slots(int i)
{
    printf("|%s",fruct[i]);
}

void castig_fruct(int nr_slots_castig) //fmm alex
{
    if(strcmp(fruct[0],"SEVEN")==0)
        if(nr_slots_castig==2)
            multiplier=5;
        else
            multiplier=15;
    else if(strcmp(fruct[0],"WMLON")==0)
        if(nr_slots_castig==2)
            multiplier=3;
        else
            multiplier=7.5;
    else if(strcmp(fruct[0],"GRAPE")==0)
        if(nr_slots_castig==2)
            multiplier=3;
        else
            multiplier=7.5;
    else if(strcmp(fruct[0],"LEMON")==0)
        if(nr_slots_castig==2)
            multiplier=2;
        else
            multiplier=4;
    else if(strcmp(fruct[0],"ORANG")==0)
        if(nr_slots_castig==2)
            multiplier=2;
        else
            multiplier=4;
    else if(strcmp(fruct[0],"CHERY")==0)
        if(nr_slots_castig==2)
            multiplier=1;
        else
            multiplier=2.5;
}

float castig(int nr_slots_castig) //exista castig
{
    castig_fruct(nr_slots_castig);
    return bet*multiplier;
}

void verificare_castig()
{
    if(strcmp(fruct[0],fruct[1])==0 && strcmp(fruct[1],fruct[2])==0)
    {
        nr_slots_castig=3;
        castig_temp=castig(nr_slots_castig);
        printf("Ai castigat suma de %.2lf credite!\n", castig_temp);
        cash-=bet;
        gamble(castig_temp);
    }
    else if(strcmp(fruct[0],fruct[1])==0 && strcmp(fruct[1],fruct[2])!=0)
    {
        nr_slots_castig=2;
        castig_temp=castig(nr_slots_castig);
        printf("Ai castigat suma de %.2lf credite!\n", castig_temp);
        cash-=bet;
        gamble(castig_temp);
    }
    else
    {
        printf("Nu ai castigat.\n");
        cash=cash-(float)bet;
        printf("Suma curenta de credite: %.2lf\n", cash);
    }
}

void play() //optiunea 1
{
    if(cash>0)
    {
        if(bet>cash)
            bet=cash;
        int i;
        for(i=0; i<3; i++)
        {
            generare_slots(slot);
            identificare(slot[i],i);
            afisare_slots(i);
        }
        printf("|\n");
        verificare_castig();
    }
}

void meniu_principal()
{
    int optiune;
    okfinal=1;
    while(okfinal)
    {
        printf("====================================\n");
        printf("[1]Joaca\n[2]Credite si bet\n[3]Schimbare bet\n[4]Cashout\nSelectare optiune: ");
        scanf("%d", &optiune);
        printf("====================================\n");
        if(cash<=0)
            optiune=4;
        if(optiune==1)
            play();
        else if(optiune==2)
        {
            afisare_credit(cash);
            afisare_bet(bet);
        }
        else if(optiune==3)
            schimbate_bet(bet);
        else if(optiune==4)
            okfinal=0;
        else
        {
            printf("Numar incorect!\n");
            meniu_principal();
        }
    }
}

int main()
{
    start();
    void_bet();
    meniu_principal();
    printf("Multumim ca ati jucat!\nSuma finala: %.2f\n", cash);
    printf("====================================\n");
    return 0;
}
