#include <iostream>

//--------------------------------------------------------------
// MATHS
//--------------------------------------------------------------
// this algorithm takes a width and a height and returns
// the length of the side of the biggest square that can be repeated
// in order to fill up the width x height rectangle evenly
// 
//  __ __ __
// |__|__|__|
// |__|__|LL| <-- this 1x1 square is the biggest one able to fill this 3x2 rectangle evenly
 
int find_max_square_to_evenly_fit_rect(int w, int h){

    // DIVIDE AND CONQUER! this took me a while to figure out..
    // 1. we do this only at the start: get the smallest side of our 2 sides.
    // 2. we create a new side equal to the modulo of the biggest side by the smallest side.
    //    is this new side a multiple of the biggest one?
    //       yes -> this one is the side of the square we're looking for!
    //       no  -> we start again: the biggest side will be the current smallest side
    //              and the smallest side will be our new side

    std::cout << "starting... " << w << "x" << h << std::endl;

    int target_side;
    int smallest_side = (w > h) ? h : w;
    int previous_smallest_side = (w > h) ? w : h;

    // recursion is nice for the programmer but evil for the memory (can lead to stack overflow)
    // since I don't know c++ so well, I prefer to use a while loop
    while (true){
        
        target_side = previous_smallest_side % smallest_side;

        // cout << "smallest side:          " << smallest_side << endl;
        // cout << "previous smallest side: " << previous_smallest_side << endl;
        // cout << "target side:            " << target_side << endl;

        if (previous_smallest_side % target_side == 0){
            std::cout << "found target side: " << target_side << "!" << std::endl;
            return target_side;
        }
        previous_smallest_side = smallest_side;
        smallest_side = target_side;

        if (target_side == 0){
            return -1;
        }
    }
}