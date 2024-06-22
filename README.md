<h1>Secondary Memory Techniques</h1>
    <p>This project contains several C files explaining and implementing different techniques for secondary memory management. The main techniques covered are Direct Organization and Hashing (Dispersion).</p>

  <h2>Direct Organization</h2>
    <p>The Direct Organization technique involves managing records in a straightforward manner where each record has a fixed position. This project includes the implementation of a file structure that directly organizes student records based on their identifiers.</p>
    <p>Key functions implemented:</p>
    <ul>
        <li><strong>creaHash</strong>: Creates a hash file from the input data file, organizing records into primary and overflow buckets.</li>
        <li><strong>creaHvacio</strong>: Initializes the hash file with empty buckets based on the given configuration.</li>
        <li><strong>desborde</strong>: Handles overflow records by placing them in the appropriate overflow buckets.</li>
    </ul>

  <h2>Hashing (Dispersion)</h2>
    <p>Hashing, or dispersion, is used to efficiently locate a record within a file. This method uses a hash function to compute an index into an array of buckets or slots, from which the desired record can be found.</p>
    <p>Key functions implemented:</p>
    <ul>
        <li><strong>busquedaHash</strong>: Searches for a record in the hash file using the hash function and provides details about its location.</li>
        <li><strong>modificarReg</strong>: Modifies a specific field (province) of a record identified by its key (DNI) within the hash file.</li>
    </ul>

   <h2>Configuration and Structure</h2>
    <p>The project uses specific configurations and structures defined in <em>dispersion.h</em>:</p>
    <ul>
        <li><strong>regConfig</strong>: Contains the configuration parameters for the hash file, including the number of primary and overflow buckets, and density thresholds.</li>
        <li><strong>tipoCubo</strong>: Represents a bucket that can hold a fixed number of records, with fields to track the number of assigned records and overflow status.</li>
    </ul>

  <h2>Usage</h2>
    <p>To compile and run the project, a makefile is provided. Ensure all the necessary files are included in the same directory:</p>
    <ul>
        <li><em>dispersion.c</em>: Contains the implementation of the core functions.</li>
        <li><em>dispersion.h</em>: Contains the type definitions and function prototypes.</li>
        <li><em>alumnos.dat</em>: Input data file with student records.</li>
        <li><em>resultado10_4.txt</em>: Example output showing the organization using 10 primary buckets and 4 overflow buckets.</li>
    </ul>
    <p>Execute the following command to compile:</p>
    <pre><code>make</code></pre>
    <p>Run the program with the appropriate arguments to create and manipulate the hash file:</p>
    <pre><code>./program_name</code></pre>

  <h2>Conclusion</h2>
    <p>This project demonstrates the implementation of secondary memory management techniques using C. By understanding and utilizing direct organization and hashing, efficient data storage and retrieval can be achieved.</p>
