#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

typedef struct room {
    char *name;
    linked_list_t doors;
} room_t;

static room_t * find_room(linked_list_t rooms, char *name) {
    ll_iterator_t it = ll_iterator_new(rooms);
    while(ll_has_next(it)) {
        room_t * room = ll_next(it);
        if (!strcmp(name, room->name)) {
            return room;
        }
    }
    return NULL;
}


int main() {
    linked_list_t rooms = ll_new();
    char buffer[20];

    while(scanf("%19s", buffer) == 1 && strcmp(buffer, "END") != 0) {
        room_t *room = calloc(1, sizeof(room_t));
        assert(room);

        room->name = strdup(buffer);
        assert(room->name);

        room->doors = ll_new();
        assert(room->doors);

        ll_add_back(rooms, room);
    }

    while(scanf("%19s", buffer) == 1 && strcmp(buffer, "END") != 0) {
        room_t * src = find_room(rooms, buffer);
        if (!src) {
            printf("Oops: Cannot find room %s.\n", buffer);
        }

        scanf("%19s", buffer);
        room_t * dst = find_room(rooms, buffer);
        if (!dst) {
            printf("Oops: Cannot find room %s.\n", buffer);
        }

        if (src && dst) {
            ll_add_back(src->doors, dst);
        }
    }

    room_t *curr = NULL;
    while(scanf("%19s", buffer) == 1 && strcmp(buffer, "END") != 0) {
        room_t * next = find_room(rooms, buffer);

        if (!next) {
            printf("Oops: Cannot find room %s.\n", buffer);
            return 0;
        } else if (curr != NULL && find_room(curr->doors, buffer) == NULL){
            printf("Oops: Room %s does not connect to room %s.\n", curr->name, buffer);
            return 0;
        }
        printf("Entering room %s.\n", buffer);
        curr = next;
    }
    printf("Ended in room %s.\n", curr->name);
    return 0;
}
