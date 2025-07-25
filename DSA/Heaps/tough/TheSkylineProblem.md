/*
Assignment 8 Q17
https://leetcode.com/problems/the-skyline-problem/

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:
lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]

Example 1:
Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]

Example 2:
Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]

Constraints:
1 <= buildings.length <= 10^4
0 <= lefti < righti <= 2^31 - 1
1 <= heighti <= 2^31 - 1
buildings is sorted by lefti in non-decreasing order.
*/

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int n = buildings.size();
        vector<pair<int,int>> lines;

        // Convert buildings into 'critical points' (start and end)
        for(int i = 0; i < n; i++){
            // Start point: negative height to indicate a building starts
            lines.push_back({buildings[i][0], -buildings[i][2]});
            // End point: positive height to indicate a building ends
            lines.push_back({buildings[i][1], buildings[i][2]});
        }

        // Sort points: by x-coordinate;
        // If x is same, smaller height first (start before end)
        sort(lines.begin(), lines.end());

        // Multiset to maintain current building heights (sorted automatically)
        multiset<int> heights = {0};  // initialize with ground level
        vector<vector<int>> result;
        int prevMax = 0;  // previous max height

        // Process each event point
        for (auto& [x, h] : lines) {
            if (h < 0) {
                // Building starts: insert height into multiset
                heights.insert(-h);
            } else {
                // Building ends: remove one instance of the height
                heights.erase(heights.find(h));
            }

            // Get current max height from multiset
            int currMax = *heights.rbegin();

            // If max height changed, record the x and new height
            if (currMax != prevMax) {
                result.push_back({x, currMax});
                prevMax = currMax;
            }
        }

        return result;
    }
};

TC - O(nlogn)
| Step                             | Time Complexity | Explanation                       |
| -------------------------------- | --------------- | --------------------------------- |
| Creating `lines` vector          | **O(n)**        | 2 entries per building            |
| Sorting `lines`                  | **O(n log n)**  | Sorting 2n elements               |
| Inserting/removing from multiset | **O(n log n)**  | Each insert/erase is log k; k ≤ n |
| Building the result vector       | **O(n)**        | At most 2n critical points        |

Sc - O(n)
| Component                  | Description                                                        | Space Complexity |
| -------------------------- | ------------------------------------------------------------------ | ---------------- |
| `lines` vector             | Stores 2 entries (start and end) for each building → `2 * n` pairs | O(n)             |
| `multiset heights`         | Stores active building heights, at most `n` in worst case          | O(n)             |
| `result` vector            | Stores at most `2 * n` critical points (skyline key points)        | O(n)             |

