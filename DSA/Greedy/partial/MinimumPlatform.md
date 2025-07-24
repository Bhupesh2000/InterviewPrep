/*
https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

You are given the arrival times arr[] and departure times dep[] of all trains that arrive at a railway station on the same day. Your task is to determine the minimum number of platforms required at the station to ensure that no train is kept waiting.

At any given time, the same platform cannot be used for both the arrival of one train and the departure of another. Therefore, when two trains arrive at the same time, or when one arrives before another departs, additional platforms are required to accommodate both trains.

Examples:
Input: arr[] = [900, 940, 950, 1100, 1500, 1800], dep[] = [910, 1200, 1120, 1130, 1900, 2000]
Output: 3
Explanation: There are three trains during the time 9:40 to 12:00. So we need a minimum of 3 platforms.
Input: arr[] = [900, 1235, 1100], dep[] = [1000, 1240, 1200]
Output: 1
Explanation: All train times are mutually exclusive. So we need only one platform
Input: arr[] = [1000, 935, 1100], dep[] = [1200, 1240, 1130]
Output: 3
Explanation: All 3 trains have to be there from 11:00 to 11:30
Constraints:
1≤ number of trains ≤ 50000
0000 ≤ arr[i] ≤ dep[i] ≤ 2359
Note: Time intervals are in the 24-hour format(HHMM) , where the first two characters represent hour (between 00 to 23 ) and the last two characters represent minutes (this will be <= 59 and >= 0).

*/

Approach 1 - Using brute force - O(N^2). find the max no. of intersections at any give time range

Approach 2 - Increase the count for each interval and decrease for each departure
class Solution {
  public:
    // Function to find the minimum number of platforms required at the
    // railway station such that no train waits.
    int findPlatform(vector<int>& arr, vector<int>& dep) {
        // Your code here
        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());
        
        int n = arr.size(), i = 0, j = 0, cnt = 0, maxCnt = 0;
        
        while(i < n && j < n){
            if(arr[i] <= dep[j]){
                cnt ++;
                i ++;
            }
            else{
                cnt --;
                j ++;
            }
            maxCnt = max(maxCnt, cnt);
        }
        
        return maxCnt;
    }
};

TC - O(NlogN), SC - O(1);

Approach 3 - The above can be also solved using extra space where each time from both arr and dep vectors are pushed in a new vector and then sort it.
NewVector = [{900, A}, {910, D}, {940, A}, {950, A}, {1100, A}, {1120, D}, {1130, D}, {1200, D}, {1500, A}, {1800, A}, {1900, D}, {2000, D}]

This is how the sorted array will look like. For each A cnt ++, for each D cnt --. Return max value of cnt

TC - O(NlogN), SC - O(N)