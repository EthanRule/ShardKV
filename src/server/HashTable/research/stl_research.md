unordered_{set, map}:
- Each key holds a pointer to the head of a linked list.
- Iterating values iterates through each linked list.
- Collisions append to a keys linked list.

dense_hash_set
- sentinals and probing can speed up the normal hashtable by 4x.
