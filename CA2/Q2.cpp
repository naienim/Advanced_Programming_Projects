#include <iostream>
#include <string>
#include <vector>
using namespace std;

int find_wayes(int n , int right = 0 , int down = 0)
{
    if (n <= 0)
    {
        return -1;
    }
    if (right >= n && down >= n)
    {
        return 1;
    }
    if ((down > right) && (down < n) && (right < n))
    {
        return find_wayes(n,right+1,down) + find_wayes(n,right,down+1);
    }
    if (down > right && right < n)
    {
        return find_wayes(n,right+1,down);
    }
    if (down < n )
    {
        return find_wayes(n,right,down+1);
    }
    return 1;
}


int main()
{
    int n=0;
    cin >> n;
    cout << find_wayes(n) << endl;

    return 0;
}
