# C++ PostgreSQL ODBC Example

[Korean](README.ko.md)

This is a simple C++ example that demonstrates how to connect to a PostgreSQL database using ODBC on Windows.

## Prerequisites

Before you begin, ensure you have the following tools and drivers installed for your respective operating system.

### Windows

1. **Visual C++ Build Tools**: You need the compiler (`cl.exe`) and build utility (`nmake.exe`). These are included when you install the "Desktop development with C++" workload in the Visual Studio Installer.
2. **PostgreSQL ODBC Driver (psqlODBC)**: You must install the correct version (32-bit or 64-bit) of the psqlODBC driver that matches the architecture of your compiled application. You can download it from the [PostgreSQL official website](https://www.postgresql.org/ftp/odbc/versions/msi/).

### Linux

1. **g++ Compiler and build-essential**: Tools for compiling C++ code.

    ```sh
    sudo apt-get update
    sudo apt-get install build-essential
    ```

2. **unixODBC Development Libraries**: Provides the ODBC API.

    ```sh
    sudo apt-get install unixodbc-dev
    ```

3. **PostgreSQL ODBC Driver**:

    ```sh
    sudo apt-get install odbc-postgresql
    ```

### macOS

1. **Xcode Command Line Tools**: Includes the `g++` compiler and `make` utility.

    ```sh
    xcode-select --install
    ```

2. **unixODBC**: Can be installed using Homebrew.

    ```sh
    brew install unixodbc
    ```

3. **PostgreSQL ODBC Driver**: Can be installed using Homebrew.

    ```sh
    brew install psqlodbc
    ```

## Setup

1. Open the `main.cpp` file.
2. Find the line with the connection string:

    ```cpp
    SQLCHAR connStr[] = "DRIVER={PostgreSQL Unicode};SERVER=localhost;PORT=5432;DATABASE=your_database;UID=your_username;PWD=your_password;";
    ```

3. Modify the following values to match your actual PostgreSQL database settings:
    * `your_database`: The name of your database.
    * `your_username`: Your PostgreSQL username.
    * `your_password`: Your PostgreSQL password.

    **Note:** On Linux or macOS, the installed driver name might be different. Use the `odbcinst -q -d` command to check the list of drivers installed on your system and modify the `DRIVER={...}` part accordingly.

## How to Build

This project includes `Makefile`s configured to build on Windows, Linux, and macOS. Here are the build instructions for each operating system.

### Windows

To compile the project on Windows, you must use a **Developer Command Prompt for Visual Studio** (e.g., "x64 Native Tools Command Prompt for VS"). A regular Command Prompt or PowerShell will not work because they do not have the necessary environment variables set for the compiler.

1. Open the Developer Command Prompt for your target architecture (x64 or x86).
2. Navigate to the project directory:

    ```sh
    cd D:\0.Project\cpp\cpp_odbc
    ```

3. Run the `nmake` command to build the executable:

    ```sh
    nmake -f Makefile.win
    ```

    This command will compile `main.cpp` and create `main.exe`.

### Linux and macOS

In a Linux or macOS environment, use the `make` command to build the project.

1. Open a terminal.
2. Navigate to the project directory.
3. Run the `make` command to build the executable:

    ```sh
    make
    ```

    This command will compile `main.cpp` and create an executable named `main`.

## Running the Application

Once the build is successful, you can run the application from the same command prompt:

```sh
.\main.exe
```

If the connection is successful, it will print a success message and the PostgreSQL version.

## Troubleshooting

### "Data source name not found and no default driver specified"

This is the most common error and means the application could not find the ODBC driver specified in the connection string.

1. **Check Driver Installation**: Make sure you have installed the psqlODBC driver. The architecture (32-bit/64-bit) must match the architecture of your application.
2. **Check Driver Name**: The driver name in your code (`DRIVER={...}`) must exactly match the name of the installed driver.
    * Open the **ODBC Data Sources** application from the Start Menu.
    * Go to the **Drivers** tab.
    * Find the exact name of the installed PostgreSQL driver (e.g., `PostgreSQL ODBC Driver(UNICODE)`).
    * Update the `connStr` in `main.cpp` with the correct name, then rebuild the project with `nmake`.
