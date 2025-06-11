#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <time.h>

#define PACKET_SIZE 64

// Compute checksum for ICMP header and data
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_ip>\n", argv[0]);
        return 1;
    }

    const char *target_ip = argv[1];
    int sockfd;
    struct sockaddr_in addr;
    char packet[PACKET_SIZE];
    struct icmphdr *icmp_hdr = (struct icmphdr *) packet;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, target_ip, &addr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }

    // Prepare ICMP header
    memset(packet, 0, PACKET_SIZE);
    icmp_hdr->type = ICMP_ECHO;
    icmp_hdr->code = 0;
    icmp_hdr->un.echo.id = htons(getpid() & 0xFFFF);
    icmp_hdr->un.echo.sequence = 0;

    // Send 1000 pings per second
    // We'll send in a loop with nanosleep to pace roughly 1000 packets per second
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000; // 1 millisecond = 1,000,000 nanoseconds

    printf("Sending ICMP echo requests to %s at ~1000 pings/second...\n", target_ip);

    while (1) {
        icmp_hdr->un.echo.sequence = htons(ntohs(icmp_hdr->un.echo.sequence) + 1);
        icmp_hdr->checksum = 0;
        icmp_hdr->checksum = checksum(packet, PACKET_SIZE);

        ssize_t sent = sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *)&addr, sizeof(addr));
        if (sent <= 0) {
            perror("sendto");
            close(sockfd);
            return 1;
        }

        nanosleep(&ts, NULL);
    }

    close(sockfd);
    return 0;
}
