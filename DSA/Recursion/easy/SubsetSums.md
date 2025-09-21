/*
https://www.naukri.com/code360/problems/subset-sum_3843086?leftPanelTabValue=SUBMISSION

You are given an array 'nums' of ‘n’ integers.
Return all subset sums of 'nums' in a non-decreasing order.
Note:
Here subset sum means sum of all elements of a subset of 'nums'. A subset of 'nums' is an array formed by removing some (possibly zero or all) elements of 'nums'.

For example
Input: 'nums' = [1,2]
Output: 0 1 2 3
Explanation:
Following are the subset sums:
0 (by considering empty subset)
1 
2
1+2 = 3
So, subset sum are [0,1,2,3].
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1 :
3
1 2 3
Sample output 1 :
0 1 2 3 3 4 5 6
Explanation For Sample Output 1:
For the first test case,
Following are the subset sums:
0 (by considering empty subset)
1
2
1+2 = 3
3
1+3 = 4
2+3 = 5
1+2+3 = 6
So, subset-sums are [0,1,2,3,3,4,5,6]
Sample Input 2 :
2 
4 5
Sample output 2 :
0 4 5 9
Expected Time Complexity:
Try to do this in O(n*2^n). 
Constraints:
1 <= n <= 15
0 <= nums[i] <= 5000
*/

void subsetSum(int ind, int currSum, vector<int> &num, vector<int> &sums){
	if(ind >= num.size()){
		sums.push_back(currSum);
		return;
	}
	subsetSum(ind + 1, currSum + num[ind], num, sums);
	subsetSum(ind + 1, currSum, num, sums);
}
vector<int> subsetSum(vector<int> &num){
	// Write your code here.
	vector<int> sums;
	subsetSum(0, 0, num, sums);
	sort(sums.begin(), sums.end());
	return sums;
}