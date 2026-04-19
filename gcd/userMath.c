
int iabs(int x)
{
    return (x > 0) ? x : -x;
}

int eu_mod(int x, int y)
{
    int res = 0;

    if( (res = x % y) < 0 )
        res += iabs(y);

    return res;
}

int gcd(int x, int y)
{
    int temp = 0;

    while( (temp = x % y) != 0 ){
        x = y;
        y = temp;
    }

    return iabs(y);
}

int lcm(int x, int y)
{
    int result;

    result = (x * y) / gcd(x, y);

    return result;
}
