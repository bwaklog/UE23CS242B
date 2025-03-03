#ifndef MSG_H
#define MSG_H

typedef struct msg_t {
  int is_write;
  char content[1024];
  int req_id;
} msg_t;

#endif // !MSG_H
