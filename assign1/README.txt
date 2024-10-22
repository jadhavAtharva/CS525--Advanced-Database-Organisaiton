-----------------------------------------------------------------------------------------------------

Course Name: Advanced Database Organization
Course Number: CS-525-04

-----------------------------------------------------------------------------------------------------

Assignment Number: 01 - Storage Manager

-----------------------------------------------------------------------------------------------------

Group No: 42

Group Members:
1.	Name: Vibhav Manoj Rane
	Hawk ID: vrane1@hawk.iit.edu
	CWID: A20548428

2.	Name: Atharva Vidyadhar Jadhav		
	Hawk ID: ajadhav16@hawk.iit.edu
	CWID: A20548559

-----------------------------------------------------------------------------------------------------

Aim:

Our goal is to create a Storage Manager for the Database Management System that excels in memory management. We're implementing strategies like closing files and freeing up memory as needed to responsibly use resources. We're also prioritizing efficient data organization, disk space management, and data access while considering memory limitations to prevent memory issues and boost system performance. By integrating reliable memory management techniques, we aim to ensure responsible memory usage, ultimately resulting in a stable and dependable system.

-----------------------------------------------------------------------------------------------------

Step-by-Step Installation and Execution Guide:

a. Begin by downloading the repository.

b. Access the "assign1" folder.

c. Instructions for Running on Linux or Mac:
   i.   Ensure that "make" is installed to run the project.
   ii.  After confirming the installation, open the terminal from the folder.
   iii. Execute the command "make clean" to remove previous *.o files.
   iv.  Following successful execution of the above command, run "make" to recompile the project files and generate new *.o files.
   v.   Finally, run the test file by entering the command "./test1".

d. Instructions for Running on Windows (Note: Modify the "Makefile" in the "assign1" folder as indicated):
   i.   Install MinGW to facilitate project execution.
   ii.  Be sure to edit line 18 in the "Makefile" to read "del test1 *.o *.exe *.bin *~ test1".
   iii. Once MinGW is installed, open PowerShell from the folder.
   iv.  Execute the command "mingw32-make clean" to remove previous *.o files.
   v.   Upon successful execution of the above command, run "mingw32-make" to recompile the project files and generate new *.o files.
   vi.  Finally, run the test file by using the command "./test1".

These steps guide you through the process of downloading, setting up, and executing the project on both Linux/Mac and Windows systems.

-----------------------------------------------------------------------------------------------------

Functions used:

1. Void initStorageManager (void):

This function initializes the storage manager by resetting the PagePointer to NULL, ensuring a clean starting point for the storage manager.


2.  RC createPageFile(char *newPageName):

The createPageFile function generates a new page file. It does so by opening the file in write mode, writing an initial page to it, and handling memory properly. It returns a success code upon successful completion.


3. RC openPageFile(char *newPageName, SM_FileHandle *StructFHptr):

This function opens an existing file and assigns it a handler (SM_FileHandle) that contains essential information about the file, such as fileName, totalNumPages, CurPagePos (initialized to 0), and mgmtInfo (a reference pointer for the file).


4. RC closePageFile(SM_FileHandle *StructFHptr):

The closePageFile function closes a file associated with the provided SM_FileHandle, sets PagePointer to NULL, and returns a success code. It also handles cases where the file handler is not found, returning an error code for file not found.


5. RC destroyPageFile(char *PgFlName):

This function deletes a page file specified by PgFlName and returns a success code if the deletion is successful, or an error code for a destroy error.


6. readblock:

Reads a block of data from the specified page position in the file, updates the current page position, and returns a success code. It also handles error cases, such as a non-existing page or a file not found, by returning the appropriate error codes.


7. getBlockPos:

Retrieves the current block position from the provided SM_FileHandle and returns it. Returns 0 if currentFile is NULL.


8. readFirstBlock:

Reads the first block of data from the file (page position 0) and returns the result.


9. readPreviousBlock:

Calculates the page position of the previous block based on the current page position in SM_Filehandle, calls the readBlock function with the calculated position, and returns the result.


10. readCurrentBlock:

Retrieves the current page position from SM_Filehandle, calls the readBlock function with the current position, and assigns a value to the checkpoint variable.


11. readNextBlock:

Calculates the page position of the next block based on the current page position in SM_Filehandle. Calls the readBlock function with the calculated position and returns the result. Assigns a value to the lastPage variable if nextTgt is 0.


12. readLastBlock:

Calculates the page position of the last block by subtracting 1 from the total number of pages in SM_Filehandle. Calls the readBlock function with the calculated position and returns the result.


13. writeblock:

Writes the content of memHandle to the specified block index in the file represented by fileHand. Performs necessary checks, returns error codes if applicable, and updates the current page position. Closes the file upon success.


14. writeCurrentBlock:

Checks for a page error, writes memHandle's content to the current page position in the file.


15. appendEmptyBlock:

Checks for file existence, creates an empty block, and appends it as a new block to the file.


16. ensureCapacity:

Checks for file existence and appends empty blocks to meet the required number of pages. 

