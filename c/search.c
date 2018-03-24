int binarySearch(int a[],int len,int key)
{
    int low=0,high = len -1,mid;
    while(low <= high) {
        mid = (low + high)/2;
        if(key == a[mid]) {
            return mid;
        } else if(key > a[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}


