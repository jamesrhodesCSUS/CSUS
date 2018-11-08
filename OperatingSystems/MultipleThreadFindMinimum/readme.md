This C program creates an array of 100 million items and searches for the minimum in this array.

It does so using basic sequantial searches, using multiple threads that alert the parent process and also wait for every child thread to complete, and using semephores to have the parent process wait until one of the threads found the minimum.
