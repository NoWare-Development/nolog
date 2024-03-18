#ifndef TYPES_H_
#define TYPES_H_

#define MAX_LOG_MESSAGE_SIZE 4096

typedef struct {
  int level;
  char message[MAX_LOG_MESSAGE_SIZE];
} LogMessage;

typedef struct _node {
  LogMessage message;
  struct _node *next;
} Node;

typedef struct {
  int valid;
  Node *head;
  Node *tail;
} Queue;

#endif // TYPES_H_
