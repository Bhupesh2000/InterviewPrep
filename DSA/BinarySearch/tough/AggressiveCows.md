/*
Assignment-2 Q12
https://www.geeksforgeeks.org/problems/aggressive-cows/0

You are given an array with unique elements of stalls[], which denote the positions of stalls. You are also given an integer k which denotes the number of aggressive cows. The task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.

Examples:
Input: stalls[] = [1, 2, 4, 8, 9], k = 3
Output: 3
Explanation: The first cow can be placed at stalls[0], 
the second cow can be placed at stalls[2] and 
the third cow can be placed at stalls[3]. 
The minimum distance between cows in this case is 3, which is the largest among all possible ways.
Input: stalls[] = [10, 1, 2, 7, 5], k = 3
Output: 4
Explanation: The first cow can be placed at stalls[0],
the second cow can be placed at stalls[1] and
the third cow can be placed at stalls[4].
The minimum distance between cows in this case is 4, which is the largest among all possible ways.
Input: stalls[] = [2, 12, 11, 3, 26, 7], k = 5
Output: 1
Explanation: Each cow can be placed in any of the stalls, as the no. of stalls are exactly equal to the number of cows.
The minimum distance between cows in this case is 1, which is the largest among all possible ways.
Constraints:
2 ≤ stalls.size() ≤ 10^6
0 ≤ stalls[i] ≤ 10^8
2 ≤ k ≤ stalls.size()
*/

// User function Template for C++

class Solution {
    bool canCowsBePlacedGreedy(vector<int> &stalls, int k, int d){
        int i = 1, n = stalls.size();
        int prev = 0;
        while(i < n){
            if(stalls[i] - stalls[prev] >= d){
                k --;
                prev = i;
            }
            if(k == 1) break;
            i ++;
        }
        return k == 1;
    }
  public:

    int aggressiveCows(vector<int> &stalls, int k) {

        // Write your code here
        sort(stalls.begin(), stalls.end());
        int n = stalls.size();
        int low = 1, high = stalls[n - 1] - stalls[0];
        int ans = 0;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(canCowsBePlacedGreedy(stalls, k, mid)){
                ans = mid;
                low = mid + 1; // if can be placed with minium distance mid, check for higher distance
            }
            else high = mid - 1;// if cannot be placed with minium distance mid, check for lower distance
        }
        return ans;
    }
};