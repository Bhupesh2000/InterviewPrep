/*
Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
You must write an algorithm that runs in linear time and uses linear extra space.

Example 1:
Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.

Example 2:
Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.

Constraints:
1 <= nums.length <= 105
0 <= nums[i] <= 109
*/

// Using pigenhole principal

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0; // No gap possible

        // Step 1: Find minimum and maximum value in the array
        int minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());

        if (minVal == maxVal) return 0; // All elements are equal

        // Step 2: Calculate bucket size using pigeonhole principle
        int bucketSize = ceil((double)(maxVal - minVal) / (n - 1)); // Minimum possible max gap
        int bucketCount = (maxVal - minVal) / bucketSize + 1;       // Total number of buckets

        // Step 3: Initialize buckets
        vector<int> bucketMin(bucketCount, INT_MAX);
        vector<int> bucketMax(bucketCount, INT_MIN);
        vector<bool> bucketUsed(bucketCount, false);

        // Step 4: Place each number in its appropriate bucket
        for (int num : nums) {
            int idx = (num - minVal) / bucketSize;
            bucketMin[idx] = min(bucketMin[idx], num);
            bucketMax[idx] = max(bucketMax[idx], num);
            bucketUsed[idx] = true;
        }

        // Step 5: Find the maximum gap between buckets
        int maxGap = 0;
        int prevBucketMax = minVal;

        for (int i = 0; i < bucketCount; ++i) {
            if (!bucketUsed[i]) continue; // Skip empty buckets

            // Gap is current bucket's min - previous bucket's max
            maxGap = max(maxGap, bucketMin[i] - prevBucketMax);
            prevBucketMax = bucketMax[i]; // Update previous bucket's max
        }

        return maxGap;
    }
};