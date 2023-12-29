# Author 
Annabelle Huang
ah2489 

# Estimate of time to complete assignment 
20 hours 

# Actual time to complete assignment 
| Date | Time Started | Time Spent |               Work completed              |
|______|______________|____________|___________________________________________|
| 3/08 |    1:00pm    |    0:30    | read and understand assignment, write     |
|      |              |            | pseudocode                                |
| 3/09 |    12:00am   |    2:30    | understand assignment more, start coding  |
| 3/08 |    2:00pm    |    1:00    | completed setting up the general          |
|      |              |            | structures and write pseudocode           |
| 3/09 |    3:00pm    |    4:00    | worked on figuring out if I should use    |
|      |              |            | dynamic or static arrays and tried to     |
|      |              |            | understand the relationship between the   |
|      |              |            | pirate_list struct and the pirate type    |
|      |              |            | contained in the arrays of pirates_list   |
| 3/10 |    11:00am   |    1:00    | continued trying to figure out the        |
|      |              |            | relationship between the structs and how  |
|      |              |            | to form an array in the struct. Also began|
|      |              |            | to write list_create, expand_if_necessary |
|      |              |            | andcontract_if_necessary functions        |
| 3/11 |    2:00pm    |    3:00    | was on the train home and wrote the       |
|      |              |            | alphasbetical sort and tested with name   |
|      |              |            | files I created myself and debugged all   |
|      |              |            | the segmentation faults it was giving     |
| 3/12 |    9:00pm    |    3:00    | degbugged segmentation faults, rearranged |
|      |              |            | makefile and reorganized the #include in  |
|      |              |            | each file and clearly understood the      |
|      |              |            | relationship                              |
| 3/13 |    12:00pm   |    3:00    | included the contract/expand if necesary  |
|      |              |            | functions                                 |
|      |              |   18:00    |            total time spent               |


# Collaboration 
None

# Discussion
I had difficulty understanding the relationship between files using 
#include and adjusting the makefile accordingly. I also kept receiving 
segmentation faults for mallocing my pirates. Initially, I was stuck on 
why setting pirates->arr[i].name equal to the name read from the file 
was not working, then I realized I needed to use strcpy() to copy the 
source string to my destination, and it worked. I also learned alot of 
file managing functions through this assignment, such as fgets() and 
fopen(), and some useful pre-implemented string functions such as strspn(),
which helped alot with omitting the trailing new-line character that's 
included at the end of the line when using fgets(). I learned that a 
buffer is used to hold the string read using fgets() and discovered 
fflush() though I didn't use it. Overall, this assignment was really 
useful in helping me understand how to handle files with C.