# Papers Citation Project

CSC 114 Algorithms Analysis and Design, Egypt-Japan University of Science and Technology.

Finds the most cited paper, then the next most cited, and so on, from a dataset of 82,937 papers and 148,116 citations. Bonus: given a paper id or exact title, it lists the papers that share at least 2 cited papers with it.

## Approach
- A hash map (`unordered_map`) counts citations per paper while reading `edges.csv`.
- A max-heap (`priority_queue`) of (count, id) returns the next most cited paper on demand.
- Two maps store who each paper cites and who cites it, which power the bonus.

## Complexity
V = number of papers, E = number of citations, k = number of papers retrieved.

| Step | Cost |
|---|---|
| Read titles | O(V) |
| Count citations | O(E) average |
| Build heap | O(V) |
| Next most cited paper | O(log V) |
| Top k papers | O(k log V) |

Total: O(V + E + k log V)

A naive approach that scans for the maximum each time costs O(V) per query, so the heap is much faster when retrieving many papers.

## Bonus: closest papers
For a paper p, each paper it cites is looked up in the cited-by map, and every other paper citing the same one gets a shared-citation count. Papers with at least 2 shared citations are listed, sorted by count. A threshold of 2 is used because a single shared citation is often a coincidence, such as both papers citing a very famous paper.

## Measured timings
| Stage | Time |
|---|---|
| Load titles | 242 ms |
| Count citations | 172 ms |
| Build heap | 2.7 ms |
| Average extract-max | about 1.1 microseconds |

## How to run
The dataset files (`nodes.csv`, `edges.csv`) are not included in this repo. Put them in the same folder as the code, then:

```
g++ -O2 -std=c++17 papersproject.cpp -o papersproject
./papersproject
```

On Windows PowerShell, run `.\papersproject.exe` instead.
Press Enter to see the next most cited paper, type `q` to move on to the bonus, and `q` again to exit.