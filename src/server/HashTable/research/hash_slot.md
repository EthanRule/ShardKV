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
 * - Probing (linear, quadratic, exponential, random, sentinals, metadata)
 * - Chaining
 */
