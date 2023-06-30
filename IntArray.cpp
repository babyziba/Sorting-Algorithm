#include <iostream>
#include "IntArray.h"


//ask the professor, making sure 1 one is righg const why is bool sorted passed in, second, copy assingmetn that linked to that,destrucgor thinks right, ask about clear, for asc by default so sould it be true orf false, what to do if binsry searc is not sorted write the function then questions ask. the last three ittle functions at th ene d

//constructors and destructors`
IntArray::IntArray(bool sorted)
{
    //std::cout << "1st overloaded constructor\n";

    _sorted = false;                                // array is not sorted in the beginning
    _memsize = 0;                                    // array does not have a size in the beginning
    _data = nullptr;                                // array does not point to anything in the beginning

}


// NEED HELP is item supposed to be the array size or what we are looking for? also if sorted is true or false do we call the sort function or update _sorted? confused about item
IntArray::IntArray(int item, bool sorted )
{
    //std::cout << "2nd overloaded constructor\n";
    _memsize = item;
    int* temp = _data;
    _data = new int[_memsize];
    std::copy(&temp[0], &temp[_memsize], _data);
    delete[] temp;
    temp = nullptr;

}

// NEED HELP.......................................................................................................................................
IntArray::IntArray(const IntArray& arr)
{
    //std::cout << "copy constructor\n";

    _memsize = arr._memsize;
    int* temp = _data;
    _data = new int[arr._memsize];
    std::copy(&temp[0], &temp[arr._memsize], _data);
    delete[] temp;
    temp = nullptr;
}

IntArray::IntArray::~IntArray()
{
    //std::cout << "destructor\n";

    delete[] _data;
}

//Member functions

//delete all elements, set _memsize to 0
void IntArray::clear()
{
    //for (int i = 0; i < _memsize; i++)    // loop through entire array
    //{
        //_data[i] = 0;                    // delete all elements
        
    //}

    _memsize = 0;                        // back to starting values as in constructor
    _sorted = false;
    _data = nullptr;

}

// insert an item
// removed -> bool sorted = true);
void IntArray::insert(int item)
{
    if (_memsize == 0)                                    // if size is 0
    {
        _data = new int[_memsize + 1];                    // create a dynamic array of size 1 for 1st insertion
        _data[_memsize] = item;                            // set 1st element of array to item
        _memsize++;                                        // increase size by 1 for the next insertion
        //return;
    }
    else                                                // if size is greater than 0
    {
        int* temp = _data;                                // create temp pointer variable for old _data
        _data = new int[_memsize+1];                    // increase size by 1 for next insertion
        std::copy(&temp[0], &temp[_memsize+1], _data);  // copy old _data to new _data
        _data[_memsize] = item;                            // set the second to last element ( which is last item in our case ) to item
        delete[] temp;                                    // delete temp....not sure if necessary since I did not call new on temp
        temp = nullptr;                                    // set temp to nullptr so it is not dangling
        _memsize++;                                        // increase size by 1 for the next insertion
        //return;
    }
}

//recursive array reverse
void IntArray::reverse()
{
    int start = 0;                                // first index of array
    int last = _memsize - 1;                    // last index of array

    while (start <= last)                        // while start and last don't overlap keep looping
    {
        std::swap(_data[start], _data[last]);    // swap first and last element
        start++;                                // increment start
        last--;                                    // decrement last
    }

}

//implement a n^2 sorting algorithm     //Ch 3.1 Goodrich
//optional: allow descending sort
//ascending by default
void IntArray::sort(bool asc)
{
    // chose iterative approach over recurssive
    // bubblesort algorithm with worst case n^2

    if (asc == true)                                            // ascending by default
    {
        for (int i = 1;i < _memsize;i++)                        // outer sorting
        {
            for (int j = 0;j < _memsize - 1;j++)                // inner sorting
            {
                if (_data[j] > _data[j + 1])                    // for ascending
                {
                    std::swap(_data[j], _data[j + 1]);            // swap current element with next if greater

                }
            }

        }
        _sorted = true;                                            // update _sorted to true since array is sorted
    }



    if (asc == false)                                            //optional: allow descending sort
    {
        for (int i = 1;i < _memsize;i++)                        // outer loop sorting the array again after inner loop is done
        {
            for (int j = 0;j < _memsize - 1;j++)                // inner sorting
            {
                if (_data[j] < _data[j + 1])                    // for descending
                {
                    std::swap(_data[j], _data[j + 1]);            // swap current element with next if smaller

                }
            }

        }
        _sorted = true;                                            // update _sorted to true since array is sorted
    }

}


// Binary search: either recursive or iterative
// input: requires a sorted array
//page 395 Goodrich
int IntArray::binary_search(int key)                // WHAT SHOULD I DO IF THE ARRAY IS NOT SORTED... SORT IT OR RETURN A NEGATIVE VALUE?
{
    // chose iterative approach over recurssive

    if (_sorted == true)
    {
        int start = 0;                            // first index of array
        int last = _memsize - 1;                // last index of array
        int middle;                                // average of the two

        while (start <= last)                    // loop as long start and last do not overlap
        {
            middle = (start + last) / 2;        // updating middle after each loop call

            if (key == _data[middle])            // base case
            {
                return middle;                    // if key is found return the index of array
            }
            else if (key > _data[middle])        // it is on the right side increment start
            {
                start++;
                //or start[midlle + 1]
            }
            else
            {                                    // it is on the left side decrement last
                last--;
                //last = midlle - 1
            }
        }
        return -1;                                // return a negative if key is not found error code -1
    }




    if ( _sorted==false)                                    // WHAT SHOULD I DO IF THE ARRAY IS NOT SORTED... SORT IT OR RETURN A NEGATIVE VALUE?
    {
        /*
            //std::cout << "sort called inside binarysearch\n";
            sort();
            return binary_search(key);
        */

        return -1;                                            // WHAT SHOULD I DO IF THE ARRAY IS NOT SORTED... SORT IT OR RETURN A NEGATIVE VALUE?

    }
    return -1;
}

// iterative linear search
// input: sorted or unsorted array ???
int IntArray::search(int key)
{
    //if (_sorted == false || _sorted == true)    // is this if statement needed needed?
                                                // input: sorted or unsorted array...
    {
        for (int i = 0;i < _memsize;i++)        // loop through entire array
        {
            if (_data[i] == key)                // search for key by checking all the elements
            {
                return i;                        // return the array index which key was found on
            }
        }
        return -1;                                // return a negative if key is not found
    }
}

//delete an item, create a new array _memsize-1
//if sorted use binary search, otherwise use linear search
void IntArray::remove(int item)
{

    if (_sorted == true)                                    //if sorted use binary search
    {
        //std::cout << "binarysearch called\n";

         int i = binary_search(item);                        // i is the index of found item

         for (i;i < _memsize;i++)                            // loop through right end of array
         {
             _data[i] = _data[i + 1];                        // move the item to the end of array
         }
         int* temp = _data;                                    // temp pointer variable for old _data
         _data = new int[_memsize - 1];                        //create a new array _memsize-1
         std::copy(&temp[0], &temp[_memsize - 1], _data);   // copy old _data to new _data
         delete[] temp;                                        // delete temp pointer variable...not sure if this is needed since I never called new on temp
         temp = nullptr;                                    // point to nothing so it is not dangling
         _memsize--;                                        // decrease size of array by 1
    }

    else
    {
        //std::cout << "search algorithm called\n";

        int i = search(item);                                //otherwise use linear search...
        
        for (i;i < _memsize;i++)
        {
            _data[i] = _data[i + 1];
        }
        int* temp = _data;
        _data = new int[_memsize - 1];
        std::copy(&temp[0], &temp[_memsize - 1], _data);
        delete[] temp;
        temp = nullptr;
        _memsize--;
        
    }

    /*
    // testing remove
    for (int i = 0;i < _memsize;i++)
    {
        if (_data[i] == item)
        {

            for (i;i < _memsize;i++)
            {
                _data[i] = _data[i + 1];
            }
            int* temp = _data;
            _data = new int[_memsize - 1];
            std::copy(&temp[0], &temp[_memsize - 1], _data);
            delete[] temp;
            temp = nullptr;
            _memsize--;

            break;
        }
    }
    */

}

//A1 & A2 member functions
int IntArray::size()
{
    return _memsize;
}

int* IntArray::begin()
{
    return _data;
}

int* IntArray::end()
{
    return _data + _memsize;
}

int& IntArray::front()
{
    return *begin();
}

int& IntArray::back()
{
    return *end();
}

int* IntArray::data()
{
    return _data;
}
const int* IntArray::data() const
{
    return data();
}

int& IntArray::at(int position)
{
    return _data[position];
}

int& IntArray::operator[](int position)
{
    return at(position);
}

//new A3
// NEED HELP..............................................................................................................
const int& IntArray::operator[](int position) const
{
    return _data[0];
}

//copy assignment
// NEED HELP..............................................................................................................
IntArray& IntArray::operator=(const IntArray& rhs)
{
    _memsize = rhs._memsize;

    return *this;
}
