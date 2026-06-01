# Bitcoin Exchange

## Exercise

Build a program `btc` that takes an input file of `date | amount` pairs and outputs the value of each bitcoin amount at the closest earlier date, using a CSV price database.

```
$ ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

## Aim

To understand ordered associative containers — specifically why `std::map` is the right tool when you need O(log n) key lookup *and* range semantics (nearest key below a target). A plain array or hash map won't do.

## Problem

Two data sources must be parsed, validated, and joined on a fuzzy date key — with no exact match guaranteed. Every line in both files is potentially malformed: bad delimiters, invalid dates (including impossible days like Feb 30), negative values, values out of range, or simply missing fields.

## Solution

**Database parsing** — The CSV is read into a `std::map<std::string, double>`. ISO `YYYY-MM-DD` strings sort lexicographically, so no date-to-integer conversion is needed — string comparison is sufficient and correct. Duplicates are silently discarded with a warning.

**String manipulation** — A dedicated module handles delimiter splitting and whitespace trimming on both sides of each token, keeping the parsing logic clean and reusable across both the database and the input file.

**Fuzzy date lookup** — `map::lower_bound` locates the insertion point in O(log n). A single decrement then yields the closest earlier rate. Edge cases covered: date before the entire database range, exact match, and date beyond the last entry.

**Input validation** — Every line goes through a strict pipeline before any computation:
- Date format enforced (length, separator positions, digit-only fields)
- Calendar correctness validated, including leap years
- Value parsed with `strtod` — rejects non-numeric input, negatives, and anything above 1000
- Delimiter presence and non-empty fields required

Any failure at any stage produces a specific error and skips the line — the program never silently produces a wrong result.
