-----------------------------------------------------------------------------------------------------

Course Name:- Advanced Database Organization
Course Number:- CS-525-04

-----------------------------------------------------------------------------------------------------

Assignment Number:- 03 - Record Manager

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

Aim:- Our aim is to develop a user-friendly Record Manager for efficient data management, enabling users to navigate through records seamlessly. With a focus on smooth record insertion and deletion functionalities, our goal is to provide a reliable solution that ensures data integrity and accessibility. By implementing intuitive navigation features and robust record handling mechanisms, our Record Manager aims to streamline data operations, offering a straightforward and effective solution for record management in various applications.

-----------------------------------------------------------------------------------------------------

Step-by-Step Installation and Execution Guide:-

a. Begin by downloading the repository.

b. Access the "assign3" folder.

c. Instructions for Running on Linux or Mac:
   i.   Ensure that "make" is installed to run the project.
   ii.  After confirming the installation, open the terminal from the folder.
   iii. Execute the command "make clean" to remove previous *.o files.
   iv.  Following successful execution of the above command, run "make" to recompile the project files and generate new *.o files.
   v.   Finally, run the test file by entering the command "make run".

d. Instructions for Running on Windows (Note: Modify the "Makefile" in the "assign3" folder as indicated):
   i.   Install MinGW to facilitate project execution.
   ii.  Be sure to edit line 18 in the "Makefile" to read "del test_assign3_1 *.o *.exe *.bin *~ test_assign3_1".
   iii. Once MinGW is installed, open PowerShell from the folder.
   iv.  Execute the command "mingw32-make clean" to remove previous *.o files.
   v.   Upon successful execution of the above command, run "mingw32-make" to recompile the project files and generate new *.o files.
   vi.  Finally, run the test file by using the command "mingw32-make run".

These steps guide you through the process of downloading, setting up, and executing the project on both Linux/Mac and Windows systems.

-----------------------------------------------------------------------------------------------------

Functions Used:

----------------------------
Initialization and Shutdown
----------------------------

1. initRecordManager() - Initialize the record manager, configuring resources and components like BufferPool and StorageManager for efficient storage and retrieval of records.

2. shutdownRecordManager() - Shutdown the record manager, releasing all accumulated resources, including memory and disk storage, to prevent memory leaks and ensure a clean exit.

----------------------------
Table Management
----------------------------

1. createTable(name, schema) - Create a new table with the specified name and schema, allocating necessary data structures and memory for future record storage.

2. openTable(name) - Open an existing table specified by its name, building a data structure to represent it for subsequent operations.

3. closeTable() - Close a previously opened table, releasing associated resources and flushing changes to disk if necessary.

4. deleteTable(name) - Delete an entire table permanently from the database, closing it first if still open, and removing all associated data and metadata.

5. getNumTuples() - Retrieve the total number of rows (tuples) currently stored in a given table for analysis and reporting.

----------------------------
Record Functions
----------------------------

1. insertRecord(bufferPool, recordData, tableSchema) - Add a new record to a specific table, providing pointers to the buffer pool manager, record data, and table schema.

2. deleteRecord(id) - Delete a record with the specified Record ID from the table.

3. updateRecord(rel) - Modify a record in the specified table.

4. getRecord(id, ...) - Retrieve a record from the table with the specified Record ID.

----------------------------
Scan Functions
----------------------------

1. startScan(...) - Initialize a scan operation for a table.

2. next(...) - Retrieve the subsequent table record that meets specified criteria during a scan.

3. closeScan(...) - Close an ongoing scan operation on a table.

----------------------------
Schema Functions
----------------------------

1. getRecordSize(schema) - Determine and return the record's size in bytes for the given schema.

2. freeSchema(...) - Deallocate memory allocated for the schema.

3. createSchema(...) - Create a new schema by allocating memory and setting attributes such as the number of attributes, names, datatypes, and lengths.

----------------------------
Attribute Functions
----------------------------

1. createRecord(schema) - Generate a new record for a specified schema with all fields initialized to NULL values.

2. getAttr(record, schema, ...) - Fetch the value of a specific attribute from a given record using the specified schema.

3. setAttr(record, schema, ...) - Change the value of a particular attribute in a record based on the provided schema.

4. attrOffset(...) - Set the offset with attrOffset.

5. freeRecord(...) - Free up memory allocated to a record.