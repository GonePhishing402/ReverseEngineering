#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netdb.h>
    #include <unistd.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR   -1
    #define closesocket close
#endif

#define TARGET_HOST "evil.com"
#define TARGET_PORT 80
#define HTTP_REQUEST "GET / HTTP/1.1\r\nHost: evil.com\r\nConnection: close\r\n\r\n"

int main(void) {
    SOCKET sock;
    struct addrinfo hints, *res;
    char buffer[1024];
    int bytes_received;

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
#endif

    printf("[*] Attempting to connect to %s:%d\n", TARGET_HOST, TARGET_PORT);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(TARGET_HOST, "80", &hints, &res) != 0) {
        fprintf(stderr, "[-] DNS resolution failed for %s\n", TARGET_HOST);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "[-] Failed to create socket\n");
        freeaddrinfo(res);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    if (connect(sock, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR) {
        fprintf(stderr, "[-] Connection to %s failed\n", TARGET_HOST);
        closesocket(sock);
        freeaddrinfo(res);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    printf("[+] Connected to %s\n", TARGET_HOST);

    send(sock, HTTP_REQUEST, (int)strlen(HTTP_REQUEST), 0);
    printf("[*] Sent HTTP GET request\n");

    printf("[*] Response:\n");
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    printf("\n[*] Connection closed\n");

    closesocket(sock);
    freeaddrinfo(res);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
