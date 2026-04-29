# **COP3530 Project 2 Proposal**

**Team Name:** GeoPulse | **Team Member:** Guilherme Armin Da Silva Anton  
**Project Title:** GeoPulse: Geospatial Incident Explorer

### **Problem**

Searching massive geospatial datasets with a basic linear scan is prohibitively slow. People expect instant answers to location-based questions, like finding the closest accident to their current coordinates or listing all incidents within a specific radius. Standard linear data structures run in linear time, meaning the CPU must check every single database row sequentially. This project tackles that computational bottleneck by implementing and comparing two non-trivial spatial data structures from first principles, specifically a k-d tree and a quadtree.

### **Motivation**

Spatial querying represents a major real-world challenge in urban planning, mapping, and traffic analysis. While highly optimized algorithms exist for this, a naive scanning approach breaks down entirely when dealing with millions of data points, making interactive analysis impossible. This project applies advanced data structures to a highly practical task, creating a controlled environment to measure performance tradeoffs. It also offers a great opportunity to see exactly when a structure built for nearest-neighbor searches, like the k-d tree, outperforms one built for regional partitioning, like the quadtree.

### **Features**

I will consider this project a success if the program can rapidly and accurately run spatial queries against a massive collision database. To achieve this, the application must load and validate a public dataset containing well over 100,000 rows. It will build a custom k-d tree and a custom quadtree from scratch using the incident coordinates. The system must then locate the nearest incident to any user-provided coordinate, retrieve all incidents within a given radius, and identify all incidents bounded by a user-defined rectangle. Finally, it must benchmark the query speeds of a brute-force linear scan against both trees and present the results through a clear command-line interface.

### **Data**

I am using the Motor Vehicle Collisions dataset from NYC OpenData. A confirmed local download yielded 2,246,476 data rows across 29 columns. Exactly 2,005,851 of these rows have valid latitude and longitude values, making them suitable for our spatial structures. The remaining 240,625 rows lack at least one coordinate and will be dropped. Only records with valid coordinates will go into the spatial indexes. I downloaded this locally as a static CSV file, bypassing the need for subscriptions or rate-limited API calls.

**Link:** [https://data.cityofnewyork.us/Public-Safety/Motor-Vehicle-Collisions-Crashes/h9gi-nx95](https://data.cityofnewyork.us/Public-Safety/Motor-Vehicle-Collisions-Crashes/h9gi-nx95)  
**Indexed Fields:** collision\_id, latitude, longitude.   
**Metadata:** crash\_date, crash\_time, borough, number\_of\_persons\_injured.

### **Tools**

I chose C++14 for the programming language because it grants fine-grained control over memory management and enables highly efficient algorithm implementations.

| Category | Selection Details |
| :---- | :---- |
| **Language & Compiler** | C++14 (relying heavily on RAII and std::unique\_ptr), GCC or Clang. |
| **Build, Test, & VC** | CMake, Catch2 (using COP3530 template), Git, and GitHub. |
| **Benchmarking & UI** | Standard C++ \<chrono\> library; simple menu-driven CLI application. |

### **Strategy**

**Data Representation:** I will store each incident in a custom Point struct containing the unique ID alongside the geographical coordinates. I plan to initially load the valid records into a flat std::vector. This flat array will act as the brute-force baseline for all performance benchmarking.

**Preliminary Data Structures:** I will optimize the spatial queries by building two non-trivial spatial trees. A k-d tree partitions data by alternating latitude and longitude splits, and it should perform exceptionally well for nearest-neighbor searches. A quadtree recursively divides two-dimensional space into four quadrants, and it should excel at radius and rectangular range queries.

**Expected Complexity:** The brute-force linear scan carries a time complexity of O(N) per query. I expect both the k-d tree and quadtree to drastically improve average-case query times through spatial partitioning. I will evaluate these structures based on build time, query time, and the impact of data distribution, forming a solid basis for the final Big-O analysis.

### **Distribution of Responsibility and Roles**

I am handling all project tasks myself. Guilherme Armin Da Silva Anton will complete project planning, dataset selection, data preprocessing, algorithmic implementations of the k-d tree and quadtree, memory management, empirical benchmarking, GitHub repository management, report documentation, and the final video presentation.

### **References**

*(Note: Per assignment instructions, references are excluded from the 2-page limit).*

1. NYC OpenData. *Motor Vehicle Collisions \- Crashes dataset*. Retrieved from https://data.cityofnewyork.us/Public-Safety/Motor-Vehicle-Collisions-Crashes/h9gi-nx95  
2. Bentley, J. L. (1975). *Multidimensional binary search trees used for associative searching*. Communications of the ACM, 18(9), 509-517.  
3. Finkel, R. A., & Bentley, J. L. (1974). *Quad trees: A data structure for retrieval on composite keys*. Acta Informatica, 4(1), 1-9.  
4. University of Florida. *COP3530 Project 2 Template Repository*. Retrieved from https://github.com/arminanton/project-2

### **(Visuals on the next page)**

### **Visuals: Wireframes**

*(Note: Per assignment instructions, wireframes are excluded from the 2-page limit).*

The application uses a clear, menu-driven command-line interface to interact with the user and display benchmark results.

GeoPulse: Geospatial Incident Explorer       

1\. Load Dataset  
2\. Build K-D Tree  
3\. Build Quadtree  
4\. Nearest-Neighbor Search  
5\. Radius Query  
6\. Rectangular Range Query  
7\. Run Performance Benchmarks  
8\. Exit

Select an operation: \[user input\]  
Enter latitude: \[user input\]  
Enter longitude: \[user input\]  
Enter radius in miles: \[user input\]

Results:  
Algorithm       | Matches Found | Execution Time   
Brute Force     | \[count\]       | \[time\] ms  
K-D Tree        | \[count\]       | \[time\] ms  
Quadtree        | \[count\]       | \[time\] ms
