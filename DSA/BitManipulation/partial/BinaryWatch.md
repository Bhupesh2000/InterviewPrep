/* Assignment Q3
https://leetcode.com/problems/binary-watch/description/

A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6 LEDs on the bottom to represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.

For example, the below binary watch reads "4:51". (check out the question)

Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the PM), return all possible times the watch could represent. You may return the answer in any order.

The hour must not contain a leading zero.

For example, "01:00" is not valid. It should be "1:00".
The minute must consist of two digits and may contain a leading zero.

For example, "10:2" is not valid. It should be "10:02".
 
Example 1:
Input: turnedOn = 1
Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]

Example 2:
Input: turnedOn = 9
Output: []
 
Constraints:
0 <= turnedOn <= 10

*/

Backtracking Approach
    void generateTimes(int index, int turnedOn, int hrsValue, int minsValue, vector<string>& ans){
        if(hrsValue > 11 || minsValue > 59) return;
        if(turnedOn == 0){
            string time = to_string(hrsValue) + ":";
            time += ((minsValue <= 9) ? "0" : "") + to_string(minsValue);
            ans.push_back(time);
            return;
        }

        for(int i = index; i < 10; i++){
            if(i < 4) generateTimes(i + 1, turnedOn - 1, hrsValue + hrs[i], minsValue, ans);
            else generateTimes(i + 1, turnedOn - 1, hrsValue, minsValue + mins[i - 4], ans);
        }
    }

    vector<string> readBinaryWatch(int turnedOn) {

        vector<string> ans;
        generateTimes(0, turnedOn, 0, 0, ans);

        return ans;
    }

--------------------------------------------------------------------------------------------------------------------------------------------

Popcount Approach

    vector<string> readBinaryWatch(int turnedOn){
        vector<string> ans;
        for(int h = 0; h < 12; h ++){
            int left = turnedOn - __builtin_popcount(h);
            if(left < 0) continue;
            string hour = to_string(h);
            for(int m = 0; m < 60; m++){
                if(__builtin_popcount(m) == left){
                    string mins = ((m < 10) ? "0" : "") + to_string(m);
                    ans.push_back(hour + ":" + mins);
                }
            }
        }
        return ans;

    }

--------------------------------------------------------------------------------------------------------------------------------------------

| Aspect                        | **Popcount Approach**                                         | **Recursive (Backtracking) Approach**                               |
| ----------------------------- | ------------------------------------------------------------- | ------------------------------------------------------------------- |
| **Time Complexity**           | **O(720)**  = O(12 × 60)<br>(constant, bounded by time range) | **O(C(10, turnedOn))** <br>Choosing `turnedOn` LEDs from 10 = ≤ 252 |
| **Time Complexity Class**     | **O(1)** (constant upper bound)                               | **O(1)** (bounded — max 1024 combinations from 10 bits)             |
| **Space Complexity (Stack)**  | **O(1)** — No recursion stack                                 | **O(turnedOn)** — recursive depth (max 10)                          |
| **Space Complexity (Output)** | **O(k)** — where `k` is number of valid times                 | **O(k)** — same                                                     |
| **Total Space**               | **O(k)**                                                      | **O(k + turnedOn)**                                                 |
| **Code Simplicity**           | ✅ Very simple and readable                                    | ❌ More verbose and complex                                          |
| **Generalizability**          | ❌ Limited to fixed hour/minute domain                         | ✅ Generalizes better to arbitrary combinatorial problems            |
| **Performance**               | ✅ Fastest possible for this problem                           | ❌ Slightly slower due to recursion                                  |
| **Best Use Case**             | ✅ Practical coding/interviews                                 | ✅ Learning recursion, more flexible                                 |



