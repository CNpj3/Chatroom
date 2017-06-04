#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

int a,b,c;

DWORD WINAPI FirstThread(PVOID pvParam){
    srand(time(NULL));
    while(1) {
        a=rand()%10;
        b=rand()%10;
        c=rand()%10;
        printf("[%d][%d][%d]",a,b,c);
        Sleep(100);
        printf("\b\b\b\b\b\b\b\b\b");
    }
    return 0;
}




int main(){

    DWORD dwThreadID;


    while(true){
        HANDLE hThread=CreateThread(NULL,0,FirstThread,NULL,0,&dwThreadID);


        getch();


        TerminateThread(hThread,INFINITE);


        if(a==b&&b==c){
             printf("\n恭喜中獎！\n");
        }else{
             printf("\n沒有中獎..\n");
        }


        system("pause");
        system("cls");


        CloseHandle(hThread);
    }

