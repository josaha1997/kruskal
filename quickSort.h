
// To partition the array
int partition (int **array, int low, int high) 
{ 
    int temp;
    int pivot = array[high][2];    // pivot 
    int i = (low - 1),j;  // Index of smaller element 
  
    for (j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or equal to pivot 
        if (array[j][2] <= pivot) 
        { 
		// increment index of smaller element 
            i++; 
            //Swaping array elements
            temp= array[i][0];
            array[i][0]=array[j][0];
            array[j][0]=temp; 
            temp= array[i][1];
            array[i][1]=array[j][1];
            array[j][1]=temp; 
            temp= array[i][2];
            array[i][2]=array[j][2];
            array[j][2]=temp; 
           
        } 
    } 
    //Swaping last element
    temp= array[i+1][0];
    array[i+1][0]=array[high][0];
    array[high][0]=temp; 
    temp= array[i+1][1];
    array[i+1][1]=array[high][1];
    array[high][1]=temp; 
    temp= array[i+1][2];
    array[i+1][2]=array[high][2];
    array[high][2]=temp; 
    return (i + 1); 
} 

//TO quick sort the array
extern void quickSort(int **array, int low, int high)
{
    if (low < high)
    {
		//Partitioning Index
        int partitionIndex = partition(array, low, high);
        quickSort(array, low,partitionIndex - 1);  // Before partitionIndex
        quickSort(array, partitionIndex + 1, high); // After partitionIndex
    }
}
