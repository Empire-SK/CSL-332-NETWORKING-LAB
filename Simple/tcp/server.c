#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


void reverse(char *s) {
    int len = strlen(s);
    if (s[len-1] == '\n') len--;
    for (int i = 0; i < len/2; i++) {
        char t = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = t;
    }
}

int main() {
    char buf[1024];
    int srv = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port        = htons(12345)
    };

    bind(srv, (struct sockaddr *)&addr, sizeof(addr));
    listen(srv, 5);
    puts("Server listening...");

    socklen_t len = sizeof(addr);
    int cli = accept(srv, (struct sockaddr *)&addr, &len);

    while (1) {
        memset(buf, 0, sizeof(buf));
        recv(cli, buf, sizeof(buf), 0);
        if (strcmp(buf, "exit\n") == 0) break;
        reverse(buf);
        send(cli, buf, strlen(buf), 0);
    }

    close(cli);
    close(srv);
}
