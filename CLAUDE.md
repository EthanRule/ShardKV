# ShardKV - Claude Instructions

## How to collaborate with Ethan

Ethan is building this project to land a systems software engineering job. **Act as a mentor, not a code generator.** Push back, ask probing questions, and help him build deep understanding — especially on core systems topics (concurrency, memory layout, SIMD, hash table internals, protocol design).

- **Do NOT** hand Ethan finished implementations of core logic. Instead, explain concepts, point him to relevant source material (e.g. abseil source code, CppCon talks), ask him what he thinks the right approach is, and review his work critically.
- **DO** write boilerplate, tests, benchmarks, build system config, CLI glue, and docs — these are fine to produce directly.
- When reviewing Ethan's code, be honest about correctness and performance issues. Don't sugarcoat.

## Project overview

ShardKV is a Redis-like sharded KV store in C++23. The core differentiator is a Swiss table hash map using SIMD metadata probing (modeled after Abseil's `raw_hash_set.h`).

## Current task

Adapting the hash table to use Abseil's `ctrl_t` / `Group` design:
- `ctrl_t` is the control byte type (metadata per slot: empty, deleted, or H2 hash bits)
- `Group` should be a function/operation on `ctrl_t*` — loading 16 control bytes and doing SIMD match/empty checks
- Goal: align with how `raw_hash_set.h` structures its probing so the implementation is interview-defensible and performant

## Session tracking

After each hour of focused work, write a brief progress note below covering: what was accomplished, how much guidance was needed vs. independent work, and any concepts that need reinforcement.

### Hour 1 — Hash table memory layout and `ctrl_t` semantics (2026-03-23)

**Task:** Get `hash_table.h` compiling with the correct flat layout (`ctrl`, sentinel, clones, slots) and proper `ctrl_t` definition with special values.

**What Ethan did independently:**
- Fixed `ctrl_t` typedef from `uint8_t` to `int8_t` (after being told it should be signed, figured out the values himself)
- Made `capacity` `static constexpr` to solve the array-size compile error
- Changed `slot_type` from `std::string` to `std::pair<std::string, std::string>` after one prompt about what a slot needs to hold
- Correctly identified `kEmpty = -128`, `kDeleted = -2`, `kSentinel = -1`
- Noted that all special values share the high bit set — hasn't fully connected this to `_mm_movemask_epi8` yet but is asking the right question
- Fixed the `<ctypes>` include error on his own

**What needed correction/guidance:**
- `kWidth` was initially set to 128 (same as capacity) — needed a nudge that it's the SIMD register width (16 bytes), not the table size
- `ctrl_t` special values were wrong on first pass (sentinel=0, tombstone=0xFF) — needed explanation of the sign-bit convention
- `slot_type` was initially just `std::string` (value only, no key) — needed prompting

**Overall:** Solid hour. Ethan drove most of the fixes after getting directional feedback. Good instincts on the runtime-capacity TODO and recognizing Group as an operation. Main gap is the SIMD connection — understanding *why* the sign bit trick matters.

### Hour 2 — H1/H2 splitting and Group design (2026-03-23)

**Task:** Implement H1 and H2 helper functions to split the 64-bit hash, then begin designing Group.

**What Ethan did independently:**
- Wrote H2 implementation: first attempt was a manual bit-extraction loop (shifting and XORing one bit at a time) — functional but overcomplicated. After a hint about shifting, immediately rewrote to `hash >> 57`. Clean final version.
- Wrote H1 as `hash % capacity` — correct and simple
- Added proper declarations in the header (`size_t H1(uint64_t)`, `int8_t H2(uint64_t)`) as private members
- Updated `Insert` to call H2 and store the result
- Independently realized that `Group` should be an operation/function on `ctrl_t*` rather than a class holding data — this is a key conceptual step

**What needed guidance:**
- Needed help connecting "H2 must be 0–127" back to "top bit must be 0 to avoid colliding with special values" — understood the range but initially said bit 8 "has to be 1" (flipped the logic). Got it after seeing the binary representations.
- First H2 implementation was a manual bit loop instead of a single shift — needed prompting toward the simpler approach
- Hasn't yet written the H1 optimization (`& (capacity - 1)` vs `%`) — mentioned for interview awareness

**What to pick up next session:**
- Implement Group operations as methods in HashTable (or free functions on `ctrl_t*`):
  - `Match(ctrl_t* group, h2_t h2)` → bitmask of matching slots
  - `MatchEmpty(ctrl_t* group)` → bitmask of empty slots
  - Start with scalar (loop over 16 bytes), then optimize to SSE `_mm_cmpeq_epi8` + `_mm_movemask_epi8`
- This is where the sign-bit trick finally pays off — a good opportunity to close that conceptual gap from Hour 1
- Clean up old `Types/group.h` file since Group is moving into HashTable

**Overall:** Good progress. Ethan is building intuition for bit manipulation but tends to reach for loops before considering bitwise shortcuts — worth reinforcing that systems code favors single-instruction solutions. The Group-as-operation insight was unprompted and shows solid understanding of Abseil's design.
