
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
long allocate_singles();
long allocate_blocks();

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(int argc, char* argv[])
{
    puts("-----------------");
    puts("| codedrome.com |");
    puts("| Block Malloc  |");
    puts("-----------------\n");

    const long test_count = 64;
    long total_ticks_singles = 0;
    long total_ticks_blocks = 0;

    // singles
    for(int i = 1; i <= test_count; i++)
    {
        total_ticks_singles += allocate_singles();
    }

    printf("mean ticks of %ld calls to allocate_singles: %ld\n", test_count, total_ticks_singles / test_count);

    // blocks
    for(int i = 1; i <= test_count; i++)
    {
        total_ticks_blocks += allocate_blocks();
    }

    printf("mean ticks of %ld calls to allocate_blocks: %ld\n", test_count, total_ticks_blocks / test_count);

    return EXIT_SUCCESS;
}

//--------------------------------------------------------
// FUNCTION allocate_singles
//--------------------------------------------------------
long allocate_singles()
{
    double* data = NULL;
    clock_t StartTicks;
    clock_t FinishTicks;

    StartTicks = clock();

    for(int i = 0; i < 10000; i++)
    {
        data = realloc(data, sizeof(double) * (i + 1));
    }

    FinishTicks = clock();

    free(data);

    return FinishTicks - StartTicks;
}

//--------------------------------------------------------
// FUNCTION allocate_blocks
//--------------------------------------------------------
long allocate_blocks()
{
    double* data = NULL;
    clock_t StartTicks;
    clock_t FinishTicks;
    int unused_memory = 0;
    int allocated_memory = 0;
    int block_size = 1000;

    StartTicks = clock();

    for(int i = 0; i < 10000; i++)
    {
        if(unused_memory == 0)
        {
            allocated_memory+= block_size;

            data = realloc(data, allocated_memory * sizeof(double));

            unused_memory = block_size;
        }

        unused_memory--;
    }

    FinishTicks = clock();

    free(data);

    return FinishTicks - StartTicks;
}
