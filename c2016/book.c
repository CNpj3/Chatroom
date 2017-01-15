#include "book.h"
#include <stdio.h>
#include <string.h>

int cmp(const void *p, const void *q)
{
    BookInfo info_p = *(BookInfo*) p, info_q = *(BookInfo*)q;
    int x = strcmp(info_p.book_title, info_q.book_title);
    return x == 0 ? info_p.date > info_q.data : x;
}

BookInfoList merge(int N, int M, BookAuthor authorArr[], BookSelling sellingArr[])
{
    BookInfoList infoList;
    int n =0;

    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            if (strcmp(authorArr[j].book_title, sellingArr[i].book_title) == 0) {
                strcpy(infoList.books[n].book_title, authorArr[j].book_title);
                strcpy(infoList.books[n].author, authorArr[j].author);
                infoList.books[n].selling = sellingArr[i].selling;
                infoList.books[n].date = sellingArr[i].date;
                n++;
                break;  // find author, go and find another book
            }
        }
    }
    qsort(infoList.books, n, sizeof(infoList.books[0]), cmp);
    infoList.num = n;
    return infoList;
}
