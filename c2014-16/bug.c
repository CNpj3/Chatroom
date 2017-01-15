#include <stdio.h>

int main()
{
    int N, M;
    scanf("%d%d", &N,&M);
    int hx, hy, tx, ty;
    scanf("%d%d%d%d", &hx,&hy,&tx,&ty);

    int dx = ((hx > tx)? -1: ((hx == tx)? 0:1));
    int dy = ((hy > ty)? -1: ((hy == ty)? 0:1));
    int x, y;
    int index=0;

    for (x=hx,y=hy; !((x==tx)&&(y==ty)); x+=dx, y+=dx, index++) {
        board[x][y]=1;
        snakeX[index]=x;
        snakeY[index]=y;
    }
    board[tx][ty] = 1;
    snakeX[index] = tx;
    snakeY[index] = ty;
    int L = index + 1;

    int Q, dir;
    scanf("%d", &Q);

    int dirX[4] = {1, -1, 0, 0};
    int dirY[4] = {0, 0, 1, -1};

    int head = 0;
    int error = 0;
    int headX = hx;
    int headY = hy;

    for (int i=0; i<0&&!error; i++) {
        scanf("%d", &dir);

        int newHeadX = headX + dirX[dir];
        int newHeadY = headY + dirY[dir];

        if (outOfBound(newHeadX, newHeadY, N, M)) {
            error = 1;
        }
        else {
            int tail = head2tail(head, L);
            int tailX = snakeX[tail];
            int tailY = snakeY[tail];

            if (!((newHeadX == tailX && newHeadY == tailY) ||
                 (board[newHeadX][newHeadY] == 0)))
                error = 1;
        
            else {
                board[tailX][tailY] = 0;
                board[newHeadX][newHeadY] = 1;
                head = newHead(head, L);
                headX = snakeX[head] = newHeadX;
                headY = snakeY[head] = newHeadY;
            }
        }
        print(board, N, M);
    }

    return 0;
}
