-----------------------------------------------------------------------------------------------------

Course Name:- Advanced Database Organization
Course Number:- CS-525-04

-----------------------------------------------------------------------------------------------------

Assignment Number:- 02 - Buffer Manager

-----------------------------------------------------------------------------------------------------

Group No:- 42

Group Members:
1.	Name: Vibhav Manoj Rane
	Hawk ID: vrane1@hawk.iit.edu
	CWID: A20548428

2.	Name: Atharva Vidyadhar Jadhav		
	Hawk ID: ajadhav16@hawk.iit.edu
	CWID: A20548559

-----------------------------------------------------------------------------------------------------

Aim:-

Our aim is to create a highly efficient Buffer Manager for our Database Management System, prioritizing responsible memory usage, optimized data organization, and effective disk space management. By offering diverse page replacement algorithms, we aim to provide a dependable solution that ensures data access optimization while preventing memory issues and enhancing system performance.

-----------------------------------------------------------------------------------------------------

Step-by-Step Installation and Execution Guide:-

a. Begin by downloading the repository.

b. Access the "assign2" folder.

c. Instructions for Running on Linux or Mac:
   i.   Ensure that "make" is installed to run the project.
   ii.  After confirming the installation, open the terminal from the folder.
   iii. Execute the command "make clean" to remove previous *.o files.
   iv.  Following successful execution of the above command, run "make" to recompile the project files and generate new *.o files.
   v.   Finally, run the test file by entering the command "./test1".

d. Instructions for Running on Windows (Note: Modify the "Makefile" in the "assign2" folder as indicated):
   i.   Install MinGW to facilitate project execution.
   ii.  Be sure to edit line 18 in the "Makefile" to read "del test_assign2_1 *.o *.exe *.bin *~ test_assign2_1".
   iii. Once MinGW is installed, open PowerShell from the folder.
   iv.  Execute the command "mingw32-make clean" to remove previous *.o files.
   v.   Upon successful execution of the above command, run "mingw32-make" to recompile the project files and generate new *.o files.
   vi.  Finally, run the test file by using the command "./test1".

These steps guide you through the process of downloading, setting up, and executing the project on both Linux/Mac and Windows systems.

-----------------------------------------------------------------------------------------------------

Functions Used:-

--------------------------
Page Management Functions
--------------------------

1. pinPage(...):
 
- This function retrieves a page from the disk, pins it to a specified page number, and checks for available space in the buffer pool. 
- If space is available, the page is added to the pool. 
- Four page replacement mechanisms (FIFO, LRU, LFU, CLOCK) are available. 
- When replacing a page, it checks if it's dirty (modified), writing it to disk if needed before placing a new page in the same location.

2. markDirty(...):

- This function marks a specified page frame as "dirty" by setting its flag to 1. 
- It locates the page with the specified `pageNumbersPgCnt` in the buffer pool and updates the flag to indicate content modifications since the last write to the disk.

3. forcePage(...):

- This function writes the contents of a specified page frame to the disk by locating the page with the specified `pageNumbersPgCnt` in the buffer pool. 
- After locating the page, it utilizes Storage Management functions to write its contents to the disk. 
- Subsequently, the dirty flag for the page is set to 0, indicating that its contents are now synchronized with the disk.

4. unpinPage(...):

- This function unpins a specified page, signaling that it's no longer actively used by the client. 
- It searches the buffer pool for the page using its `pageNumbersPgCnt` and decreases the client count by 1, signifying that the client has finished using the page. 
- This action opens the possibility for the page to be replaced by another when additional space is required.

--------------------------
Statistics Functions
--------------------------

1. getNumWriteIO(...):

- This function returns the total count of pages written to the disk by the buffer pool. 
- It's tracked through the `wordCntComplete` variable, initially set to 0 upon buffer pool creation and incremented for each page written to the disk.

2. getNumReadIO(...):

- This function provides the total count of pages read from the disk by the buffer pool, tracked via the `pageNumbersPgCnt` variable.

3. getDirtyFlags(...):

- This function returns an array of booleans, one for each page in the buffer pool, indicating whether each page is "dirty." 
- It iterates through all page frames, setting the corresponding array element to TRUE if the page in that frame is dirty.

4. getFrameContents(...):

- This function returns an array of frmeContntPgNum, matching the number of pages in the buffer pool. 
- It iterates through all page frames, setting each array element to the pageNum of the page saved in the corresponding frame.

5. getFixCounts(...):

- This function returns an array of integers, matching the number of pages in the buffer pool. 
- It iterates through all page frames, setting each array element to the countFinal of the page saved in the corresponding frame.

--------------------------
Buffer Pool Functions
--------------------------

1. initBufferPool(...):

- This function initializes the buffer pool, setting its size based on the `pageNumber` argument, and it tracks the page file via `fileNameOfPg`. 
- The page replacement strategy is specified using `->`, and any necessary parameters are passed via `strategyReplace`.

2. forceFlushPool(...):

- This function writes modified pages with the `badOrNot = True` attribute to disk. 
- It checks each page frame to ensure it meets the criteria of `badOrNot = True` and `countofClient = 0`, signifying that no clients are actively using the page frame. 
- If both conditions are satisfied, the page frame is written to the disk.

3. shutdownBufferPool(...):

- This function deallocates all memory and resources associated with the buffer pool. 
- Prior to removal, it invokes `forceFlushPool(...)` to write any modified pages to disk. 
- If any page is still in use by a client, the function raises an error with code RC_BUFFER_PIN_PG.

-----------------------------------------
Page Replacement Algorithm Functions
-----------------------------------------	

1. FIFO_Strategy(...):

- The FIFO page replacement algorithm employs a queue to manage the buffer pool. 
- It prioritizes replacing the page initially loaded into the buffer pool when required.

2. LRU_Strategy(...):

- The LRU page replacement algorithm replaces the page frame in the buffer pool that hasn't been accessed for the longest time. 
- It utilizes the `fileLstIndx` field to track access frequency, replacing the page frame with the lowest `fileLstIndx` value.

3. CLOCK_Strategy(...):

- The CLOCK page replacement algorithm replaces the most recently added page frame in the buffer pool. 
It utilizes a circular list with a "hand" that points to the next page frame to be replaced.