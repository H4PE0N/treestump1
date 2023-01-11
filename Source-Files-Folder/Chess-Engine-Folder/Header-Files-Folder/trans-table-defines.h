
#ifndef TRANS_TABLE_DEFINES_H
#define TRANS_TABLE_DEFINES_H

typedef struct Entry
{
  uint64_t hash;
  int depth;
  int score;
  int flag;
} Entry;

extern const uint8_t ENTRY_FLAG_EXACT;
extern const uint8_t ENTRY_FLAG_LOWER;
extern const uint8_t ENTRY_FLAG_UPPER;

extern const int HASH_TABLE_SIZE;

#endif
