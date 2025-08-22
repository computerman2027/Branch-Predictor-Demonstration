# Branch Prediction Demonstration in C

This repository contains two simple C programs (`p1.c` and `p2.c`) that demonstrate the effect of **CPU branch prediction** on performance.  

## 📖 What is Branch Prediction?

Modern CPUs are *pipelined*: they execute multiple instructions simultaneously in different stages.  
When the CPU encounters a conditional branch (e.g., an `if` statement), it doesn’t know ahead of time whether the branch will be taken or not. To keep the pipeline full, the CPU **predicts** the outcome.  

- If the prediction is correct → execution continues smoothly.  
- If the prediction is wrong → the pipeline must be flushed and restarted, costing many CPU cycles (a *misprediction penalty*).  

Good branch prediction is essential for high performance in modern processors.

---

## 📝 Programs Overview

### `p1.c` – Random Unsorted Data
- Fills an array of size `N = 10000` with random numbers in the range `[0, 254]`.  
- Loops through the array **1,000,000 times**, adding elements `<= 100` to a sum.  
- Because the array is unsorted, the branch (`if (array[i] <= 100)`) is **hard to predict** — the outcome is almost random for each element.  
- This causes many branch mispredictions, slowing down the program.

### `p2.c` – Sorted Data
- Same setup as `p1.c`, but **the array is sorted** before looping.  
- Now all values `<= 100` appear first, followed by all values `> 100`.  
- The branch (`if (array[i] <= 100)`) becomes **very predictable**:
  - For the first part of the array: always true.  
  - For the rest: always false.  
- The CPU’s branch predictor quickly learns this pattern, greatly reducing mispredictions and improving performance.

---

## ⚡ Expected Results

When compiled with optimizations and branch conversions disabled:

- `p2` (sorted) should run **significantly faster** than `p1` (unsorted).  
- On typical modern hardware, you may see up to a **40% speed improvement**.  
- Example (measured on Linux with `gcc -O2 -fno-tree-vectorize -fno-if-conversion`):  

```
$ ./p1
Time: 8.17 sec sum = 626504384

$ ./p2
Time: 5.44 sec sum = 626504384
```

Both programs compute the same result, but the sorted case benefits from predictable branching.

---

## ⚙️ Compilation

### On Linux
```bash
gcc -O2 -fno-tree-vectorize -fno-if-conversion p1.c -o p1
gcc -O2 -fno-tree-vectorize -fno-if-conversion p2.c -o p2
```

### On Windows (MinGW)
```powershell
gcc -O2 p1.c -o p1.exe
gcc -O2 p2.c -o p2.exe
```

> ⚠️ Note: Modern GCC/Clang may optimize the branch away by replacing it with *branchless instructions* (e.g., `cmov` or vectorization). Disabling if-conversion ensures the branch is preserved for demonstration purposes.

---

## 🖥️ Key Takeaways
- **Branch prediction** allows CPUs to run conditionals faster when outcomes are consistent.  
- **Random branches** are costly because they cause frequent mispredictions.  
- **Sorting data** can improve performance *without changing the algorithm* — simply by making branches more predictable.  
- Compiler optimizations may change how code is executed, so experiment with flags for best demonstration.

---

## 📚 Further Reading

- [Wikipedia: Branch Predictor](https://en.wikipedia.org/wiki/Branch_predictor)  

---

✍️ **Author**: Imon Mallik  
📂 **Purpose**: Educational demonstration of branch prediction in C  
