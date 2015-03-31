#define LIMIT 500

int factor(unsigned long n)
{
    unsigned long k;
    int count = 2;

    for (k = 2; k < n; k++)
    {
        if (n % k == 0)
            count++;
    }

    return count;
}

int main(void)
{
    unsigned long trinum = 0, i;
    int count;

    for (i = 1; i < 1000000; i++)
    {
        trinum += i;

        /* triangle number is given by n(n+1)/2 */

        if (i & 1)
            count = factor(i) * factor((i+1)/2);
        else
            count = factor(i/2) * factor(i+1);

        if (count > LIMIT)
        {
            printf("%ld: %ld\n", i, trinum);
            return 0;
        }
        count = 0;
    }

    return 0;
}
