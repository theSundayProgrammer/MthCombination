

#include <vector>
#include <algorithm>

using std::transform;
typedef std::vector<int> TCombo;
#include <stdio.h>
int factorial(int n)
{
	return n==0? 1: n*factorial(n-1);
}
int CC(int k, int n)
{
	int val =1;
	if (k==0)
		return 1;
	for(int i=1; i<=k; ++i, --n)
	{
		val= val*n/i;
	}
	return val;
}
TCombo M_th_Combo(int M, int k,int n)
{
    using namespace std;
	if(k==0) 
		return TCombo();
	else if (k==n)
	{
		TCombo ret;
		for (int i=0; i<n; ++i)
		   ret.push_back(i);
		return ret;
	}
	if (M < CC(k-1, n-1))
	{
		TCombo ret;
		TCombo sub = M_th_Combo(M, k-1,n-1);
		ret.push_back(0);
		transform(sub.begin(),sub.end(), std::back_inserter(ret), [] (int n) {return n+1;} );
		return ret;
	}
	else
	{
		TCombo ret = M_th_Combo(M-CC(k-1,n-1), k,n-1);
		transform(ret.begin(),ret.end(),ret.begin(),[] (int n) {return n+1;});
		return ret;
	}
}

TCombo M_th_Permut(int M, int k,int n)
{
	if(k==0)
		return TCombo();
    int m0 =  M / factorial(k-1)/CC(k-1, n-1);
	int m1 =  M % (factorial(k-1)*CC(k-1, n-1));
	TCombo ret;
	ret.push_back(m0);
	TCombo sub = M_th_Permut(m1, k-1, n-1);
	transform(sub.begin(),sub.end(), back_inserter(ret), 
				[m0] (int n) { return n<m0 ? n : n+1;} );
	return ret;
	
}

int RankCombo(TCombo& combo, int k, int n)
{
	if (k==0 || k == n) 
	    return 0;
	else if(*combo.begin() == 0)
	{
		TCombo sub;
		transform(combo.begin() + 1, combo.end(), back_inserter(sub),
		   [](int n) { return n-1;});
		return RankCombo(sub,k-1,n-1);
	}
	else
	{
		TCombo sub;
		transform(combo.begin(), combo.end(), back_inserter(sub),
		   [](int n) { return n-1;});
		return CC(k-1,n-1) + RankCombo(sub, k, n-1);
	}
}

int RankPermut(TCombo& combo, int k, int n)
{
	if (combo.size()==0) 
		return 0;
	int m0 = combo[0];
	TCombo sub;
	transform(combo.begin() +1, combo.end(), back_inserter(sub),
		   [m0](int n) {return n<m0 ? n : n-1;});
	return m0*factorial(k-1)*CC(k-1, n-1) + RankPermut(sub, k-1, n-1);
}

int main()
{
    int m=10,
		k=3,
		n=6;
	TCombo combo=M_th_Combo(m,k,n);
	std::for_each (combo.begin(), combo.end(),
	[](int k)
	{	
		printf("%d ",k);
	});
	printf("\n%d %d %d", k, n, CC(k,n));

	printf("\n%d %d\n", m, RankCombo(combo,k,n));
	
	combo = M_th_Permut(m,k,n);
	std::for_each (combo.begin(), combo.end(),
	[](int k)
	{	
		printf("%d ",k);
	});
	printf("\n%d %d\n", m, RankPermut(combo,k,n));
	printf("\nWow!\n");
}

