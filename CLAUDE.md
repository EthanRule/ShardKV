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
