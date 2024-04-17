https://leetcode.com/problems/minimum-adjacent-swaps-to-make-a-valid-array/description/

// You are given a 0-indexed integer array nums.

// Swaps of adjacent elements are able to be performed on nums.

// A valid array meets the following conditions:

// The largest element (any of the largest elements if there are multiple) is at the rightmost position in the array.
// The smallest element (any of the smallest elements if there are multiple) is at the leftmost position in the array.
// Return the minimum swaps required to make nums a valid array.

 

// Example 1:

// Input: nums = [3,4,5,5,3,1]
// Output: 6
// Explanation: Perform the following swaps:
// - Swap 1: Swap the 3rd and 4th elements, nums is then [3,4,5,3,5,1].
// - Swap 2: Swap the 4th and 5th elements, nums is then [3,4,5,3,1,5].
// - Swap 3: Swap the 3rd and 4th elements, nums is then [3,4,5,1,3,5].
// - Swap 4: Swap the 2nd and 3rd elements, nums is then [3,4,1,5,3,5].
// - Swap 5: Swap the 1st and 2nd elements, nums is then [3,1,4,5,3,5].
// - Swap 6: Swap the 0th and 1st elements, nums is then [1,3,4,5,3,5].
// It can be shown that 6 swaps is the minimum swaps required to make a valid array.
// Example 2:
// Input: nums = [9]
// Output: 0
// Explanation: The array is already valid, so we return 0.
 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 105

// 由于只需要把最小值和最大值放在两端，那么需要找到最大值和最小值所在的index，然后分别向两端swap。计算swap的个数。
// 如果最小值在最大值的右侧，会节省一个swap挪向最终位置
class Solution {
public:
    int minimumSwaps(vector<int>& nums) {
        int min_index = 0;
        int max_index = 0;
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] < nums[min_index]){
                min_index = i;
            }
            if (nums[i] >= nums[max_index]){
                max_index = i;
            }
        }
        int ret = min_index + (nums.size()-1-max_index);
        if (min_index > max_index){
            ret--;
        }
        return ret;
    }
};