#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print_i(vector<int> nums , int i=0 , int step=0 , int preNum=0)
{
    int j=0;

    if (i>=nums.size())
    {
        return;
    }

    if (step%2 == 0)
    {
        if (nums[i] >= preNum)
            j=nums[i];
        else
            j=preNum;
    }
    else
    {
        if (nums[i] <= preNum)
            j=nums[i];
        else
            j=preNum;
    }
    
    cout << nums[i] << " ";
    
    print_i(nums , i+j , step+1 , nums[i]);
} 


int main()
{
    vector<int> nums;
    int inputNumber = 0;
    int n = 0;

    cin >> n;  
    for (int i = 0 ; i < n ; i++)
    {
        cin >> inputNumber;
        nums.push_back(inputNumber);
    }
    
    print_i(nums);

    return 0;
}


