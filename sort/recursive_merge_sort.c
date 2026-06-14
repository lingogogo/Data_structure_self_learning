void Merge(int* arr, int front, int mid, int end){
    //init two temp temp array
    int len = end - front + 1;
    int tmp[len];
    
    //main
    int i = front, j = mid+1, k = 0; //i==left_idx, j==right_idx, k==tmp_idx;
    //start sort
    while(i<=mid && j<=end){
        if(arr[i] < arr[j]){
            tmp[k] = arr[i];
            i++;
        }else{
            tmp[k] = arr[j];
            j++;
        }
        k++;
    }
    // sort the rest
    while(i<=mid){
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while(j<=end){
        tmp[k] = arr[j];
        j++;
        k++;
    }
    
    //place the elements from tmp to arr
    for(int x=front, y=0; x<=end && y<len; x++, y++){
        arr[x] = tmp[y];
    }
}
void merge_sort(int* arr, int front, int end){
    //boundary
    if(!arr)
        return;
        
    //main
    if(front < end){
        //Divide
        int mid = (front+end)/2;
        merge_sort(arr, front, mid);
        merge_sort(arr, mid+1, end);
        //Merge
        Merge(arr, front, mid, end);
    }
}
