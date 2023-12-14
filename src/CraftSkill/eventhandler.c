#include "eventhandler.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

EventHandler eventhandler_alloc()
{
    EventHandler handler;
    handler.hashLength = 1009;
    handler.itemCount = 0;
    handler.items = calloc(handler.hashLength, sizeof(HashLinkedItem));
    return handler;
}

void eventhandler_cleanup(EventHandler *handler)
{
    // Go through all the items and free linked items
    for (size_t i = 0; i < handler->hashLength; i++) {
        if (handler->items[i].item == NULL) continue;

        HashLinkedItem *prevItem = NULL;
        HashLinkedItem *currentItem = &handler->items[i];

        while (currentItem->item != NULL) {
            // Traverse to the last item in the linked list
            if (currentItem->next != NULL) {
                prevItem = currentItem;
                currentItem = currentItem->next;
                continue;
            }

            // Need to check that we don't try to free the first item in the linked list
            if (currentItem->prev == NULL) break;

            free(currentItem);
            prevItem->next = NULL;

            currentItem = prevItem;
            prevItem = currentItem->prev;
        }
    }
    free(handler->items);
}

void event_subscribe(EventHandler *handler, const char *name, event_callback callback)
{
    uint32_t index = hash(name, handler->hashLength);
    HashLinkedItem *prevItem = NULL;
    HashLinkedItem *currentItem = &handler->items[index];

    while (currentItem->item != NULL) {
        if (currentItem->next == NULL) {
            /* HashLinkedItem linkedItem = {0}; */
            HashLinkedItem *linkedItem = calloc(1, sizeof(HashLinkedItem));
            currentItem->next = linkedItem;
        }
        prevItem = currentItem;
        currentItem = currentItem->next;
    }

    currentItem->prev = prevItem;
    currentItem->item = callback;
    currentItem->next = NULL;
}

void event_subscribe_all(EventHandler *handler, event_callback callback)
{
    (void) handler;
    (void) callback;
    assert(1 == 0);
}

void event_unsubscribe(EventHandler *handler, const char *name, event_callback callback)
{
    (void) handler;
    (void) name;
    (void) callback;
    assert(1 == 0);
}

void event_unsubscribe_all(EventHandler *handler, event_callback callback)
{
    (void) handler;
    (void) callback;
    assert(1 == 0);
}

void event_emit(EventHandler *handler, const char *name, const char *message, ...)
{
    uint32_t index = hash(name, handler->hashLength);
    HashLinkedItem *currentItem = &handler->items[index];

    va_list args;
    va_start(args, message);

    while (currentItem->item != NULL) {
        /* char *msg = va_arg(args, char *); */
        currentItem->item(message, args);

        if (currentItem->next == NULL) break;
        currentItem = currentItem->next;
    }

    va_end(args);
}

void event_emit_all(EventHandler *handler)
{
    (void) handler;
    assert(1 == 0);
}

uint32_t hash(const char *key, uint32_t hashLength)
{
    uint32_t h = 0;
    uint32_t i = 0;

    unsigned int keyLen = strlen(key);
    while (i < keyLen) {
        int exponent = 1;
        for (uint32_t j = 0; (j < 4 && i < keyLen); j++) {
            h += key[i] * exponent;
            exponent *= 10;
            i++;
        }
    }

    return h % hashLength;
}
