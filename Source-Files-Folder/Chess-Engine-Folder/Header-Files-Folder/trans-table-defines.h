
#ifndef TRANS_TABLE_DEFINES_H
#define TRANS_TABLE_DEFINES_H

typedef enum EFlag
{
  ENTRY_FLAG_EXACT, ENTRY_FLAG_LOWER, ENTRY_FLAG_UPPER
} EFlag;

typedef struct Entry
{
  uint64_t hash;
  int depth;
  int score;
  EFlag flag;
} Entry;

extern const int HASH_TABLE_SIZE;

#define HASH_TABLE_INDEX(ZOBRIST_HASH) (ZOBRIST_HASH % HASH_TABLE_SIZE)

#endif
