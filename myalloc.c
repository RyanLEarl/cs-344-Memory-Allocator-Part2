// * Understand 
// * Plan

// myalloc
//     if this is the first run:
//         do sbrk
//         do first linked list node setup

    // cur = front of the list 
    // while cur is != NULL 
    //     if this node is big enough and not in use:
    //     mark it in use 
    //     return pointer to node data

    // return NULL

#include "myalloc.h"

struct block *head = NULL;

void print_data(void) {
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

void *myalloc(size_t size) {

	if (head == NULL) { 
    	head = sbrk(1024);
    	head->next = NULL;
    	head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    	head->in_use = 0;
    }

    (void)size;

    int padded_size = PADDED_SIZE(size);
    int block_padded_size = PADDED_SIZE(sizeof(struct block));

    struct block *cur = head;
    while (cur != NULL) {
        // if this node is big enough and not in use:
        if (!cur->in_use && cur->size >= padded_size) {
            //  # vvv splitting code ^^^

            // if the space is big enough to split:
            //     Split_Space(current, size) into current and new
            // Split_Space(current_node, requested_size):
            // If current_node big enough to split:
            //     Add a new struct block with the remaining unused space
            //     Wire it into the linked list

            // # ^^^ splitting code ^^^
            // mark it in use
            cur->in_use = 1;
            printf("Found one!\n");

            // return pointer to node data
            return PTR_OFFSET(cur, block_padded_size);
        }
        cur = cur->next;
    }
    return NULL;
}

int main(void) {
    print_data();
    char *p = myalloc(60);
    printf("%p\n", p);
    print_data();
}