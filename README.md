A simple media buffer allocator written in C with a thread-safe buffer pool and efficient memory management.
Currently supports Audio and Media file formats like mp3, mp4, wave, aac, flac, ogg, wmv, flv, etc.
It can be used for media processing and currently computes the average byte value and checksum for each chunk of data for further usage to be implemented.

#Features

Custom buffer tool for efficient memory manageemtn with thread-safe buffer allocation and deallocation APIs. 
Buffers are pre-allocated to reduceo overhead during runtime, locked and unlocked with mutexes for thread safety. 

#How to Use

Compile in your local environment


gcc -o media_processor main.c allocator.c -lpthread
./media_processor

It will prompt you for a filepath, enter the full path 

#Dependencies

-C standard library
-POSIX Threads(pthread)

Feel free to contribute by forking and submitting pull requests, ask me if anything unsure
