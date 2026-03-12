
CppCon 2017: Matt Kulukundis “Designing a Fast, Efficient, Cache-friendly Hash Table, Step by Step”: https://youtu.be/ncHmEUmJZf4?si=G5F_rA62ZPgKNDFg
// Whether a table is cold or hot
// hot means it fits in L1 cache, and you need to count in instructions executed
// cold, just count L1 cache misses
// benchmarks are the only source of truth. But you need crazy deep amounts of them that arent gamed.

// delete performance doesnt matter much, people only care about insert and find speed

typical unordered_sets use buckets which is basically just chaining hash
// hash node has a 64bit hash code, value, and next pointer.

A single bucket just seems to be a single node.

Load Factor: table size() / bucket count

keys in undorderd_set actually point to starting places in a linked list (in fact one node before, so key 1 points to head). And all the values are in one long concatenated linked list.

Iterating this set is literally traversing a single linked list.

probing might reduce find time because you dont have to look at the prev element in linked list, and the keys cache better in sequentially allocated memory vs traversing multiple links in dynamic memory.

// benchmarking
// how full is the table for performance
// is table hot all in l1 cache, or is it further than l3 cache in ram?
// did you actually find element, or is element in not in table?
// is insert succeeding or not?
// how large are keys, how large are your vals?
// time in nanos for graphs

sentinal with probing can speed up hashmap like 4x (dense_hash_set) (performance degrades with its size of keys)

keep a parallel array of metadata. Whether its empty, full, or deleted. Instead of 4 bits, can use 1 byte, 7 bits sotring hash code, and 1 bit for full or empty

positions: 1 byte metadata, and a slot that stores the value.

enum class Ctrl : ctrl_t {
  kEmpty = -128,
  kDeleted = -2,
  kSentinel = -1,
  // kFull = (this lets you stop scanning your table for a metascan)
};

iterator find(const K& key, size_t hash) const {
  size_t pos = H1(hash) % size_;
  while (true) {
    if (H2(hash) == ctrl_[pos] && key == slots[pos])
      return iterator_at(pos);
    if (ctrl_[pos] == kEmpty) return end();
    pos = (pos + 1) % size_;
  }
}


size_t H1(size_t hash) { return hash >> 7; }
ctrl_t H2(sizse_t hash) { return hash & 0x7F; }

// SSE instructions? machine code?
BitMask<uint32_t> Match(h2_t hash) const {
  auto match = _mm_set1_epi8(hash); // initialize 128 bit vector of 16 8 bit things
  return BitMask<uint32_t> (
    _mm_movemask_epi8(_mm_cmpeq_epi8(match, ctrl))); // Takes 2 128 bit things and gives you masks of 00 or FF where bytes line up. then movemask squishes it down to
    a 16 bit thing where there are 1's where they match, and 0's where they dont match (also telling us which 16 bits have the proper h2 hash)
}

16 control bytes, and 16 slots is a group, and the table contains n groups
(this looks in parallel at all of the control bytes, and then finds the slot instantly)

iterator find(const K& key, size_t hash) const {
  size_t group = H1(hash) % num_groups_;
  while (true) {
    Group g{ctrl_ + group * 16};
    for (int i : g.Match(H2(hash))) {
      if (key == slots_[group * 16 + i])
        return iterator_at(group * 16 + i);
    }
    if (g.MatchEmpty()) return end();
    group = (group + 1) % num_groups_;
  }
}

void erase(iterator it) {
  --size_;
  Group g{ (it.ctrl_ - ctrl_) / 16 * 16 + ctrl_};
  *it.ctrl_ = g.MatchEmpty() ? kEmpty : kDeleted;
  it.slot_.~K();
}

can use templates to more effeciently create keys instead of just allocating a node everytime?

experimental arbitrary group positions
vb

4 bytes is l1 cache line?

check if this is opensourced swiss table?

power of 2 size to resize table on full load factor

https://abseil.io/about/design/swisstables
absl::flat_hash_map
absl::flat_hash_set
absl::node_hash_map
absl::node_hash_set

flat is faster, but node guarentees pointer/refrernce stability on rehash/resizes

https://en.wikipedia.org/wiki/Avalanche_effect
Avalanch effect: idealy prevents collision attacks, length extension attacks, and preimage attacks. 
When one input bit is complemented, each of the output bits change with a 50% probability.

https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions (SIMD SSE instructions)

#include "absl/container/node_hash_map.h"

these are the fastest general maps and are also used as the default in the go programming language

/* Hash Slot Algo:
 * Determines which partition of the table a key goes to.
 *
 *
 * Most Secure:
 * - SHA-256 (more secure but slower)
 * - CRC16 (aka Cyclic Redundancy Check) (used by redis, doesent prevent collisions) (often implemented in hardware with CRC32c)
 * - MurmurHash3 (quickest and most modern, low collisions) (better on pure software) *uses 32 bits
 * Least Secure
 *
 *
 * Collision Resolution Algo:
 * Determines how to resolve hash collisions.
 * - Probing (linear, quadratic, exponential, random)
 * - Chaining
 *
 */
  
// redis uses chaning hashing, but seems to have better latency on an update.