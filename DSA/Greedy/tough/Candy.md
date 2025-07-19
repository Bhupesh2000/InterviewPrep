/*
Assignement 8 Q15
https://leetcode.com/problems/candy/

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:
Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 
Constraints:
n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4
*/

Approach 1 - using 2 vectors
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1) return n;
        vector<int> left(n), right(n);
        left[0] = 1;
        for(int i = 1; i < n; i++){
            if(ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
            else left[i] = 1; 
        }
        right[n - 1] = 1;
        for(int i = n - 2; i >= 0; i--){
            if(ratings[i] > ratings[i + 1]) right[i] = right[i + 1] + 1;
            else right[i] = 1; 
        }
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += max(left[i], right[i]);
        }
        return sum;
    }
};
TC - O(3N), SC - O(2N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using 1 vector

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1) return n;
        vector<int> left(n);
        left[0] = 1;
        for(int i = 1; i < n; i++){
            if(ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
            else left[i] = 1; 
        }
        int sum = left[n - 1];
        int prev = 1;
        for(int i = n - 2; i >= 0; i--){
            int curr = 1;
            if(ratings[i] > ratings[i + 1]) curr = prev + 1;
            prev = curr;
            sum += max(left[i], curr);
        }
        return sum;
    }
};

TC - O(3N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Slope Approach

class Solution {
public:
    int candy(vector<int>& ratings) {
        int sum = 1, n = ratings.size();
        int i = 1;
        while(i < n){
            if(ratings[i] == ratings[i - 1]){
                sum += 1;
                i ++;
                continue;
            }
            int peak = 1;
            while(i < n && ratings[i] > ratings[i - 1]){
                peak ++;
                sum += peak;
                i ++;
            }
            int down = 1;
            while(i < n && ratings[i] < ratings[i - 1]){
                sum += down;
                down ++;
                i ++;
            }
            if(down > peak) sum += (down - peak);
        }
        return sum;
    }
};

TC - O(N), SC - O(1)