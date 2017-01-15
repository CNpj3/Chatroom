#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int id;
    char phone[10];
    float grade[4];
    int birth_year;
    int birth_month;
    int birth_day;
} Student;

int main()
{
    char in[32];
    char out[32];
    scanf("%s%s",in,out);

    FILE *fin = fopen(in, "rb");
    FILE *fout = fopen(out, "w");

    char table[] = "<table border=\"1\">";
    char table2[] = "</table>";
    char tbody[] = "<tbody>";
    char tbody2[]="</tbody>";
    char tr[] = "<tr>";
    char tr2[] = "</tr>";
    char td[] = "<td>";
    char td2[]="</td>";

    fwrite(table, sizeof(table), 1, fout);
    fwrite(tbody, sizeof(tbody), 1, fout);
    fwrite(tr, sizeof(tr), 1, fout);

    char buf[64];
    while (fread(buf, sizeof(buf), 1, fin) != NULL) {
        fwrite(td, sizeof(td), 1, fout);
        fwrite(buf, sizeof(buf), 1, fout);
        fwrite(td2, sizeof(td2), 1, fout);
        int bufInt;
        fwrite(td, sizeof(td), 1, fout);
        fread(bufInt, sizeof(int), 1, fin);
        fwrite(bufInt, sizeof(int), 1, fin);
        fwrite(td2, sizeof(td2), 1, fout);

        fread(buf, sizeof(buf), 1, fin);
        fwrite(td, sizeof(td), 1, fout);
        fwrite(buf, sizeof(buf), 1, fout);
        fwrite(td2, sizeof(td2), 1, fout);
        
        char blank[] = ", ";
        float bufFloat;
        fwrite(td, sizeof(td), 1, fout);
        fread(bufFloat, sizeof(float), 1, fin);
        fwrite(bufFloat, sizeof(float), 1, fout);
        fwrite(blank, sizeof(blank), 1, fout);
        
        fread(bufFloat, sizeof(float), 1, fin);
        fwrite(bufFloat, sizeof(float), 1, fout);
        fwrite(blank, sizeof(blank), 1, fout);
        
        fread(bufFloat, sizeof(float), 1, fin);
        fwrite(bufFloat, sizeof(float), 1, fout);
        fwrite(blank, sizeof(blank), 1, fout);
        
        fread(bufFloat, sizeof(float), 1, fin);
        fwrite(bufFloat, sizeof(float), 1, fout);
        fwrite(td2, sizeof(td2), 1, fout);

    return 0;
}
