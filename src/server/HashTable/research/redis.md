// Redis Research
// Since Redis is similar to this project, it's important to know what their mature system uses and why.

// Distributed Hash Slot Algo:
CRC16 (aka Cyclic Redundancy Check) (used by redis, doesent prevent collisions) (often implemented in hardware with CRC32c)

// Collision resolution technique:
Chaining hashing, but seems to have better latency on an update than probing solutions.
