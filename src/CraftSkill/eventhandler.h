#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <stdint.h>
#include <stdarg.h>

typedef void(*event_callback)(const char *, va_list);
typedef struct HashLinkedItem HashLinkedItem;

struct HashLinkedItem {
    HashLinkedItem *prev;
    HashLinkedItem *next;
    event_callback item;
};

HashLinkedItem hashlinkeditem_new();

typedef struct {
    uint32_t hashLength;
    uint32_t itemCount;
    HashLinkedItem *items;
} EventHandler;

EventHandler eventhandler_alloc();
void eventhandler_cleanup(EventHandler *handler);
void event_subscribe(EventHandler *handler, const char *name, event_callback callback);
void event_subscribe_all(EventHandler *handler, event_callback callback);
void event_unsubscribe(EventHandler *handler, const char *name, event_callback callback);
void event_unsubscribe_all(EventHandler *handler, event_callback callback);
void event_emit(EventHandler *handler, const char *name, const char *message, ...);
void event_emit_all(EventHandler *handler);

uint32_t hash(const char *key, uint32_t hashLength);

#endif // EVENTHANDLER_H_
