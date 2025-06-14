/*
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Example 1:
Input: n = 3, k = 3
Output: "213"

Example 2:
Input: n = 4, k = 9
Output: "2314"

Example 3:
Input: n = 3, k = 1
Output: "123"
 
Constraints:
1 <= n <= 9
1 <= k <= n!
*/

string getPermutation(int n, int k) {
    vector<int> nums;
    // Fill nums with 1 to n
    for (int i = 1; i <= n; i++) {
        nums.push_back(i);
    }

    // Convert to 0-based index
    k--;

    // Precompute factorials
    int fact = 1;
    for (int i = 1; i < n; i++) {
        fact *= i;
    }

    string result = "";

    for (int i = n; i >= 1; i--) {
        int index = k / fact;             // Determine the index in nums
        result += to_string(nums[index]); // Pick and append digit
        nums.erase(nums.begin() + index); // Remove used digit

        k %= fact;                        // Update k
        if (i > 1)
            fact /= (i - 1);              // Update factorial for next position
    }

    return result;
}
