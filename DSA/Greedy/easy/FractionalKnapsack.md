/*
https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1

Given two arrays, val[] and wt[], representing the values and weights of items, and an integer capacity representing the maximum weight a knapsack can hold, determine the maximum total value that can be achieved by putting items in the knapsack. You are allowed to break items into fractions if necessary.
Return the maximum value as a double, rounded to 6 decimal places.

Examples :
Input: val[] = [60, 100, 120], wt[] = [10, 20, 30], capacity = 50
Output: 240.000000
Explanation: Take the item with value 60 and weight 10, value 100 and weight 20 and split the third item with value 120 and weight 30, to fit it into weight 20. so it becomes (120/30)*20=80, so the total value becomes 60+100+80.0=240.0 Thus, total maximum value of item we can have is 240.00 from the given capacity of sack. 
Input: val[] = [60, 100], wt[] = [10, 20], capacity = 50
Output: 160.000000
Explanation: Take both the items completely, without breaking. Total maximum value of item we can have is 160.00 from the given capacity of sack.
Input: val[] = [10, 20, 30], wt[] = [5, 10, 15], capacity = 100
Output: 60.000000
Explanation: In this case, the knapsack capacity exceeds the combined weight of all items (5 + 10 + 15 = 30). Therefore, we can take all items completely, yielding a total maximum value of 10 + 20 + 30 = 60.000000.
Constraints:
1 <= val.size=wt.size <= 10^5
1 <= capacity <= 10^9
1 <= val[i], wt[i] <= 10^4
*/

class Solution {
  public:
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        int n = val.size();
        vector<pair<double, int>> valPerUnit;
        for(int i = 0; i < n; i++){
            double vpu = (double) val[i] / (double) wt[i];
            valPerUnit.push_back({vpu, wt[i]});
        }
        sort(valPerUnit.begin(), valPerUnit.end());
        double ans = 0;
        for(int i = n - 1; i >= 0; i--){
            double vpu = valPerUnit[i].first;
            int weight = valPerUnit[i].second;
            if(weight <= capacity){
                ans += (vpu * (double) weight);
                capacity -= weight;
            }
            else{
                ans += (vpu * (double) capacity);
                break;
            }
        }
        return ans;
    }
};

TC - O(NlogN) -> because of sorting
SC - O(N) -> valPerUnit