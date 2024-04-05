1. 二分查找
int binarySearch(vector<int> &nums, int target){
    int l = 0;
    int r = nums.size();

    while (l < r){
        int mid = l + (r-l)/2;
        if (nums[mid] == target){
            return mid;
        }
        else if (nums[mid] < target){
            l = mid+1;
        }
        else{
            r = mid;
        }
    }
    if (l < nums.size() && nums[l] == target){
        return l;
    }
    return -1;
}
1.1 二分查找 upper_bound
1.2 二分查找 lower_bound
2 滑动窗口
3 集合 排列
4 BFS DFS
5 循环数组
6 二叉树
7 图
7.1 最短路径
7.2 双色问题
8 双指针
8.1 