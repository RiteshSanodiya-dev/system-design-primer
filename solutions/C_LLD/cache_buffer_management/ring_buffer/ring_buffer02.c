/*
 * File: ring_buffer02.c
 * Author: Ritesh Sanodiya
 * Date: 10 sep 2024
 * Description: contains code for ring buffer
 *
 * License: copyright
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFF_SIZE 5

typedef struct {
    int buffer[BUFF_SIZE];
    int start;
    int end;
    int size;
} circular_buff_t;

void init(circular_buff_t* cb)
{
    cb->start = 0;
    cb->end = 0;
    cb->size = 0;
}

bool is_empty(circular_buff_t* cb)
{
    if(cb->size == 0)
        return true;
    else
        return false;
}

bool is_full(circular_buff_t* cb)
{
    if(cb->size == BUFF_SIZE)
        return true;
    else
        return false;
}

void write_buff(circular_buff_t* cb, int item)
{
    printf("inserting item [%d]\n", item);
    if(is_full(cb)) {
        printf("buffer is already full\n");
    } else {
        cb->buffer[cb->end] = item;
        cb->end = (cb->end + 1) % BUFF_SIZE; 
        cb->size++;
    }
}

int read_buff(circular_buff_t* cb) {
    if(is_empty(cb)) {
        printf("buffer is empty\n");
        return -1;
    } else {
        int item = cb->buffer[cb->start];
        cb->start = (cb->start + 1) % BUFF_SIZE;
        cb->size--;
        return item;
    }
}

int main()
{
    circular_buff_t cb;
    init(&cb);

    write_buff(&cb, 10);
    write_buff(&cb, 20);
    write_buff(&cb, 30);
    write_buff(&cb, 40);
    write_buff(&cb, 50);
    write_buff(&cb, 60);

    printf("read : %d\n", read_buff(&cb));
    printf("read : %d\n", read_buff(&cb));

    write_buff(&cb, 70);
    write_buff(&cb, 80);

    while(!is_empty(&cb)) {
        printf("read : %d\n", read_buff(&cb));
    }
}
