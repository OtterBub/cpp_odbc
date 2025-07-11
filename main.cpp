
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
#include <string>

void show_error(unsigned int handleType, const SQLHANDLE& handle) {
    SQLCHAR sqlState[1024];
    SQLCHAR message[1024];
    SQLINTEGER nativeError;
    SQLSMALLINT textLength;

    if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, sqlState, &nativeError, message, 1024, &textLength)) {
        std::cerr << "SQLSTATE: " << sqlState << ", Native error: " << nativeError << ", Message: " << message << std::endl;
    }
}

int main() {
    SQLHENV hEnv = SQL_NULL_HENV;
    SQLHDBC hDbc = SQL_NULL_HDBC;
    SQLHSTMT hStmt = SQL_NULL_HSTMT;
    SQLRETURN ret;

    // 1. 환경 핸들 할당
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to allocate environment handle" << std::endl;
        return -1;
    }

    // 2. ODBC 버전 설정
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to set ODBC version" << std::endl;
        show_error(SQL_HANDLE_ENV, hEnv);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return -1;
    }

    // 3. 연결 핸들 할당
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to allocate connection handle" << std::endl;
        show_error(SQL_HANDLE_ENV, hEnv);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return -1;
    }

    // 4. 데이터베이스 연결
    // 중요: 아래 연결 문자열을 실제 환경에 맞게 수정하세요.
    SQLCHAR connStr[] = "DRIVER={PostgreSQL Unicode};SERVER=localhost;PORT=5432;DATABASE=your_database;UID=your_username;PWD=your_password;";
    
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to connect to the database" << std::endl;
        show_error(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return -1;
    }

    std::cout << "Successfully connected to the database." << std::endl;

    // 5. 구문 핸들 할당
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to allocate statement handle" << std::endl;
        show_error(SQL_HANDLE_DBC, hDbc);
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return -1;
    }

    // 6. 쿼리 실행
    SQLCHAR query[] = "SELECT version()";
    ret = SQLExecDirect(hStmt, query, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Failed to execute query" << std::endl;
        show_error(SQL_HANDLE_STMT, hStmt);
    } else {
        // 7. 결과 가져오기
        ret = SQLFetch(hStmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLCHAR versionStr[256];
            SQLLEN indicator;
            SQLGetData(hStmt, 1, SQL_C_CHAR, versionStr, sizeof(versionStr), &indicator);
            std::cout << "PostgreSQL Version: " << versionStr << std::endl;
        }
    }

    // 8. 핸들 해제 및 연결 종료
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
