#include <stdio.h>
#include <string.h>

static int denomination[] = {50, 10, 5, 1};
#define DENOMINATION (sizeof(denomination) / sizeof(int)) 
//how many kinds of coins
#define WORDMAX 4
#define DENMAX 10

enum DENINDEX {FIFTY, TEN, FIVE, ONE};

typedef struct wallet{
	int num[DENOMINATION];
} Wallet;

void init(Wallet *wallet)
{
	for (int i = 0; i < DENOMINATION; i++)
		wallet->num[i] = 0;
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

void pay(Wallet *wallet, int amount)
{
    for (int i = 0; i < DENOMINATION; i++) {
        int coinNum = min(amount / denomination[i], wallet->num[i]);
        (wallet->num[i]) -= coinNum;
        amount -= coinNum * denomination[i];
    }
    return;
}

void add(Wallet *wallet)
{
    char den[DENMAX]; int n;
    printf("... ");
    scanf("%s", den);
    while (strcmp(den, "end") != 0) {
        scanf("%d", &n);
        if (strcmp(den, "fifty") == 0){
            printf("50 should has %d\n", n);
            wallet->num[FIFTY] += n;
            printf("50 has %d\n", wallet->num[FIFTY]);

        }
        else if (strcmp(den, "ten") == 0)
            wallet->num[TEN] += n;
        else if (strcmp(den, "five") == 0)
            wallet->num[FIVE] += n;
        else if (strcmp(den, "one") == 0)
            wallet->num[ONE] += n;
        else    printf("wrong denomination.\n");

        
        printf("... ");
        scanf("%s", den);
    }
    return;
}

void purge(Wallet *wallet)
{
    int sum = 0;
    /* get whole money first */
    for (int i = 0; i < DENOMINATION; i++)
        sum += denomination[i] * wallet->num[i];

    for (int i = 0; i < DENOMINATION; i++) {
        int coinNum = sum / denomination[i];
        wallet->num[i] = coinNum;
        sum -= coinNum * denomination[i];
    }
    return;
}

void show(Wallet *wallet)
{
    printf("\n");
    for (int i = 0; i < DENOMINATION; i++) 
        printf("%d coin %d\n", denomination[i], wallet->num[i]);
    printf("\n");
    return;
}

int main()
{
    Wallet wallet;
    char input[WORDMAX];

    printf(">>> ");
    scanf("%s", input);
    while (strcmp(input, "quit") != 0) {
        if (strcmp(input, "init") == 0)
            init(&wallet);
        else if (strcmp(input, "show") == 0)
            show(&wallet);
        else if (strcmp(input, "add") == 0)
            add(&wallet);
        else if (strcmp(input, "pay") == 0) {
            int amount;
            printf("... ");
            scanf("%d", &amount);
            pay(&wallet, amount);
        }
        else if (strcmp(input, "purge") == 0)   
            purge(&wallet);
        else printf("wrong operations.\n");

        printf(">>> ");
        scanf("%s", input);
    }


/*    init(&wallet);
    show(&wallet);
    add(&wallet, 20, 0, 2, 10);
    show(&wallet);
    pay(&wallet, 506);
    show(&wallet);
    add(&wallet, 0, 6, 2, 9);
    purge(&wallet);
    show(&wallet);
*/


    return 0;
}
