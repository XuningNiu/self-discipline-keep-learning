// 295. Find Median from Data Stream
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

// For example, for arr = [2,3,4], the median is 3.
// For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
// Implement the MedianFinder class:

// MedianFinder() initializes the MedianFinder object.
// void addNum(int num) adds the integer num from the data stream to the data structure.
// double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

// Example 1:

// Input
// ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
// [[], [1], [2], [], [3], []]
// Output
// [null, null, null, 1.5, null, 2.0]

// Explanation
// MedianFinder medianFinder = new MedianFinder();
// medianFinder.addNum(1);    // arr = [1]
// medianFinder.addNum(2);    // arr = [1, 2]
// medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
// medianFinder.addNum(3);    // arr[1, 2, 3]
// medianFinder.findMedian(); // return 2.0
 

// Constraints:

// -105 <= num <= 105
// There will be at least one element in the data structure before calling findMedian.
// At most 5 * 104 calls will be made to addNum and findMedian.
 

// Follow up:

// If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
// If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?

// 方法一：使用双priority_queue,一个是大顶堆，一个是小顶堆。 top就是middle

// class MedianFinder {
//     priority_queue<int> large;
//     priority_queue<int, vector<int>, greater<int>> small;
// public:
//     MedianFinder() {
        
//     }
    
//     void addNum(int num) {
//         if (large.size() > small.size()){
//             large.push(num);
//             small.push(large.top());
//             large.pop();
//         }
//         else{
//             small.push(num);
//             large.push(small.top());
//             small.pop();
//         }
//     }
    
//     double findMedian() {
//         if (large.size() < small.size()){
//             return small.top();
//         }
//         else if (large.size() > small.size()){
//             return large.top();
//         }
//         return (large.top() + small.top())*0.5;
//     }
// };




// 方法二： 使用multi_set，并且维护一个mid iterator. 保持左侧mid
// 1 2 3
//   ^
// 1 2 3 4
//   ^

class MedianFinder {
private:
    multiset<double> data;
    multiset<double>::iterator mid;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        data.insert(num);

        if (data.size() == 1){    
            mid = data.begin();
            return;
        }
        
        if (num < *mid && data.size()%2==0){
            mid--;
        }
        if (num >= *mid && data.size()%2 == 1){
            mid++;
        }
    }
    
    double findMedian() {
        if (data.size()%2 == 0){
            return (*mid + *next(mid, 1))*0.5;
        }
        return *mid;
    }
};
