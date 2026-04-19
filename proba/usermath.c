
int iabs(int x)
{
	return (x > 0) ? x : -x;
}

int eu_mod(int x, int y)
{
	int res = x%y;
	if(res < 0)
		res+=iabs(y);

	return res;
}


int gcd(int x, int y)
{
	while(0 != y){
		int tmp = x;
		x = y;
		y = eu_mod(tmp, y);
	}
	
	return iabs(x);
}
