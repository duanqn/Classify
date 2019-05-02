// FileIOtest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

const int bytes = 500000;
const int round = 1000;

int main()
{
    LARGE_INTEGER tick1, tick2, ticks_per_second;
    QueryPerformanceFrequency(&ticks_per_second);
    printf("High resolution clock: %lld ticks per second\n", ticks_per_second.QuadPart);

    QueryPerformanceCounter(&tick1);
    FILE *f_std = nullptr;
    char x = 'W';
    for (int i = 0; i < round; ++i) {
        fopen_s(&f_std, "test.txt", "w");
        for (int j = 0; j < bytes; ++j) {
            fprintf(f_std, "%c", x);
        }
        fclose(f_std);
    }
    
    QueryPerformanceCounter(&tick2);
    double time = (double)((tick2.QuadPart - tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Writing %d rounds of %d bytes data with fprintf: %lf seconds\n", round, bytes, time);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    char *buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        fopen_s(&f_std, "test.txt", "w");
        fwrite((void *)buff, sizeof(buff[0]), sizeof(buff), f_std);
        fclose(f_std);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Writing %d rounds of %d bytes data with fwrite: %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        fopen_s(&f_std, "test.txt", "r");
        fread(buff, sizeof(buff[0]), sizeof(buff), f_std);
        fclose(f_std);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Reading %d rounds of %d bytes data with fread: %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    DWORD ret;
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        HANDLE f_win = CreateFileA("test.txt", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, nullptr);
        // catch f_win = INVALID_HANDLE_VALUE
        WriteFile(f_win, buff, sizeof(buff), &ret, nullptr);
        CloseHandle(f_win);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Writing %d rounds of %d bytes data with WriteFile (system caching disabled): %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        HANDLE f_win = CreateFileA("test.txt", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, nullptr);
        // catch f_win = INVALID_HANDLE_VALUE
        WriteFile(f_win, buff, sizeof(buff), &ret, nullptr);
        CloseHandle(f_win);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Writing %d rounds of %d bytes data with WriteFile (system caching disabled, write through): %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        HANDLE f_win = CreateFileA("test.txt", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        // catch f_win = INVALID_HANDLE_VALUE
        WriteFile(f_win, buff, sizeof(buff), &ret, nullptr);
        CloseHandle(f_win);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Writing %d rounds of %d bytes data with WriteFile (system caching enabled): %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        HANDLE f_win = CreateFileA("test.txt", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        // catch f_win = INVALID_HANDLE_VALUE
        ReadFile(f_win, buff, sizeof(buff), &ret, nullptr);
        CloseHandle(f_win);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Reading %d rounds of %d bytes data with ReadFile (system caching enabled): %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);

    //---------------------------------
    buff = new char[bytes];
    QueryPerformanceCounter(&tick1);
    memset((void *)buff, 'c', sizeof(buff));
    for (int i = 0; i < round; ++i) {
        HANDLE f_win = CreateFileA("test.txt", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, nullptr);
        // catch f_win = INVALID_HANDLE_VALUE
        ReadFile(f_win, buff, sizeof(buff), &ret, nullptr);
        CloseHandle(f_win);
    }
    QueryPerformanceCounter(&tick2);
    delete[] buff;
    time = (double)(((double)tick2.QuadPart - (double)tick1.QuadPart) / ticks_per_second.QuadPart);
    printf("Reading %d rounds of %d bytes data with ReadFile (system caching disabled): %lf seconds\n", round, bytes, time);
    printf("%lld ticks elapsed\n", tick2.QuadPart - tick1.QuadPart);
    printf("Throughput: %lf Bytes/s\n", round * bytes / time);
    return 0;
}

