
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