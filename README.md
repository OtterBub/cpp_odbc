# C++ PostgreSQL ODBC 예제

이것은 Windows에서 ODBC를 사용하여 PostgreSQL 데이터베이스에 연결하는 방법을 보여주는 간단한 C++ 예제입니다.

## 사전 준비 사항

시작하기 전에 각 운영체제에 맞는 다음 도구와 드라이버가 설치되어 있는지 확인하세요.

### Windows

1. **Visual C++ 빌드 도구**: 컴파일러(`cl.exe`)와 빌드 유틸리티(`nmake.exe`)가 필요합니다. Visual Studio 설치 프로그램에서 "C++를 사용한 데스크톱 개발" 워크로드를 설치하면 포함됩니다.
2. **PostgreSQL ODBC 드라이버 (psqlODBC)**: 컴파일된 애플리케이션의 아키텍처와 일치하는 올바른 버전(32비트 또는 64비트)의 psqlODBC 드라이버를 설치해야 합니다. [PostgreSQL 공식 웹사이트](https://www.postgresql.org/ftp/odbc/versions/msi/)에서 다운로드할 수 있습니다.

### Linux

1. **g++ 컴파일러 및 build-essential**: C++ 코드를 컴파일하기 위한 도구입니다.

   ```sh
   sudo apt-get update
   sudo apt-get install build-essential
   ```

2. **unixODBC 개발 라이브러리**: ODBC API를 제공합니다.

   ```sh
   sudo apt-get install unixodbc-dev
   ```

3. **PostgreSQL ODBC 드라이버**:

   ```sh
   sudo apt-get install odbc-postgresql
   ```

### macOS

1. **Xcode Command Line Tools**: `g++` 컴파일러와 `make` 유틸리티를 포함합니다.

   ```sh
   xcode-select --install
   ```

2. **unixODBC**: Homebrew를 사용하여 설치할 수 있습니다.

   ```sh
   brew install unixodbc
   ```

3. **PostgreSQL ODBC 드라이버**: Homebrew를 사용하여 설치할 수 있습니다.

   ```sh
   brew install psqlodbc
   ```

## 설정

1. `main.cpp` 파일을 엽니다.
2. 연결 문자열이 있는 줄을 찾습니다:

    ```cpp
    SQLCHAR connStr[] = "DRIVER={PostgreSQL Unicode};SERVER=localhost;PORT=5432;DATABASE=your_database;UID=your_username;PWD=your_password;";
    ```

3. 다음 값을 실제 PostgreSQL 데이터베이스 설정과 일치하도록 수정합니다:
    * `your_database`: 데이터베이스 이름.
    * `your_username`: PostgreSQL 사용자 이름.
    * `your_password`: PostgreSQL 비밀번호.

    **참고:** Linux 또는 macOS에서는 설치된 드라이버 이름이 다를 수 있습니다. `odbcinst -q -d` 명령을 사용하여 시스템에 설치된 드라이버 목록을 확인하고 `DRIVER={...}` 부분을 적절하게 수정하세요.

## 빌드 방법

이 프로젝트는 Windows, Linux 및 macOS에서 빌드할 수 있도록 구성된 `Makefile`을 포함하고 있습니다. 각 운영체제에 맞는 빌드 방법은 다음과 같습니다.

### Windows

Windows에서 프로젝트를 컴파일하려면 **Visual Studio용 개발자 명령 프롬프트**(예: "x64 Native Tools Command Prompt for VS")를 사용해야 합니다. 일반 명령 프롬프트나 PowerShell은 컴파일러에 필요한 환경 변수가 설정되어 있지 않기 때문에 작동하지 않습니다.

1. 대상 아키텍처(x64 또는 x86)에 맞는 개발자 명령 프롬프트를 엽니다.
2. 프로젝트 디렉토리로 이동합니다:

    ```sh
    cd D:\0. Project\cpp\cpp_odbc
    ```

3. `nmake` 명령을 실행하여 실행 파일을 빌드합니다:

    ```sh
    nmake
    ```

    이 명령은 `main.cpp`를 컴파일하고 `main.exe`를 생성합니다.

### Linux 및 macOS

Linux 또는 macOS 환경에서는 `make` 명령어를 사용하여 프로젝트를 빌드합니다.

1. 터미널을 엽니다.
2. 프로젝트 디렉토리로 이동합니다.
3. `make` 명령을 실행하여 실행 파일을 빌드합니다:

    ```sh
    make
    ```

    이 명령은 `main.cpp`를 컴파일하고 `main`이라는 실행 파일을 생성합니다.

## 애플리케이션 실행

빌드가 성공하면 동일한 명령 프롬프트에서 애플리케이션을 실행할 수 있습니다:

```sh
.\main.exe
```

연결에 성공하면 성공 메시지와 PostgreSQL 버전이 출력됩니다.

## 문제 해결

### "Data source name not found and no default driver specified"

이 오류는 가장 흔하게 발생하는 문제로, 애플리케이션이 연결 문자열에 지정된 ODBC 드라이버를 찾지 못했음을 의미합니다.

1. **드라이버 설치 확인**: psqlODBC 드라이버를 설치했는지 확인하세요. 아키텍처(32비트/64비트)는 애플리케이션의 아키텍처와 일치해야 합니다.
2. **드라이버 이름 확인**: 코드의 드라이버 이름(`DRIVER={...}`)이 설치된 드라이버의 이름과 정확히 일치해야 합니다.
    * 시작 메뉴에서 **ODBC 데이터 원본** 애플리케이션을 엽니다.
    * **드라이버** 탭으로 이동합니다.
    * 설치된 PostgreSQL 드라이버의 정확한 이름을 찾습니다(예: `PostgreSQL ODBC Driver(UNICODE)`).
    * `main.cpp`의 `connStr`을 올바른 이름으로 업데이트한 다음, `nmake`로 프로젝트를 다시 빌드하세요.
