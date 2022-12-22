#include <stdio.h>
#include <string.h>

int loadInputFile();
int nextLine(char *dst);

char line[200];

// Precomputed: min: 0, max: 19;
#define MAXN 20
int space[MAXN][MAXN][MAXN];

int main()
{
    if (loadInputFile() < 0)
    {
        fprintf(stderr, "Can't open: input.txt\n");
        return 1;
    }

    int x, y, z;
    int ndrops = 0;
    while (nextLine(line))
    {
        if (sscanf(line, "%d,%d,%d", &x, &y, &z) != 3)
            break;
        space[x][y][z] = 1;
        ndrops++;
    }

    int commonSides = 0;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            for (int k = 0; k < MAXN; k++)
            {
                if (space[i][j][k])
                {
                    if (i - 1 >= 0 && space[i - 1][j][k])
                        commonSides++;

                    if (i + 1 < MAXN && space[i + 1][j][k])
                        commonSides++;

                    if (j - 1 >= 0 && space[i][j - 1][k])
                        commonSides++;

                    if (j + 1 < MAXN && space[i][j + 1][k])
                        commonSides++;

                    if (k - 1 >= 0 && space[i][j][k - 1])
                        commonSides++;

                    if (k + 1 < MAXN && space[i][j][k + 1])
                        commonSides++;
                }
            }
        }
    }

    int answer = 6*ndrops - commonSides;
    printf("%d\n", answer);
}

#define BUFSIZE 35000

char fileBuf[BUFSIZE];
char *pbuf = fileBuf;
char *pbufend = fileBuf;

int loadInputFile()
{
    FILE *pf = fopen("input.txt", "r");
    if (!pf)
        return -1;
    pbuf = fileBuf;
    pbufend = fileBuf + fread(fileBuf, 1, BUFSIZE, pf);
    fclose(pf);

    return 0;
}

int nextLine(char *dst)
{
    char c;
    char *orig = dst;

    // read line:
    while (pbuf < pbufend && (c = *(pbuf++)) != '\n')
    {
        *(dst++) = c;
    }
    *dst = '\0';
    // return line length
    return dst - orig;
}