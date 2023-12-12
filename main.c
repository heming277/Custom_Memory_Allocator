// main.c

#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_PATH 260

// Allowed file extensions
const char *allowed_media_extensions[] = { ".mp4", ".avi", ".mov", ".wmv", ".flv" };
const char *allowed_audio_extensions[] = { ".mp3", ".wav", ".aac", ".flac", ".ogg" };

// Check if the file extension is allowed
int is_allowed_extension(const char *file_path) {
    const char *dot = strrchr(file_path, '.');
    if (!dot) {
        return 0; // No file extension
    }

    for (int i = 0; i < sizeof(allowed_media_extensions) / sizeof(char *); i++) {
        if (strcasecmp(dot, allowed_media_extensions[i]) == 0) {
            return 1; // Match found in media extensions
        }
    }

    for (int i = 0; i < sizeof(allowed_audio_extensions) / sizeof(char *); i++) {
        if (strcasecmp(dot, allowed_audio_extensions[i]) == 0) {
            return 1; // Match found in audio extensions
        }
    }

    return 0; // No match found
}

// Process the media data
void process_media_data(void *buffer, size_t size) {
    printf("Processed %zu bytes of data.\n", size);

    // Compute the average byte value
    unsigned char *byte_buffer = (unsigned char *)buffer;
    uint64_t sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += byte_buffer[i];
    }
    double average = (double)sum / size;
    printf("Average byte value: %.2f\n", average);

    // Simple checksum calculation
    uint64_t checksum = sum % 256; // Simple modulo to keep it in byte range
    printf("Checksum: %llu\n", checksum);
}

int main() {
    char file_path[MAX_FILE_PATH];
    printf("Please enter the path of the media file to process:\n");
    printf("Supported media types: .mp4, .avi, .mov, .wmv, .flv\n");
    printf("Supported audio types: .mp3, .wav, .aac, .flac, .ogg\n");
    
    fgets(file_path, MAX_FILE_PATH, stdin); // Read the entire line, including spaces

    // Remove newline character if it was read by fgets
    size_t len = strlen(file_path);
    if (len > 0 && file_path[len - 1] == '\n') {
        file_path[len - 1] = '\0';
    }   

    if (!is_allowed_extension(file_path)) {
        fprintf(stderr, "Unsupported file type.\n");
        return 1;
    }

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    BufferPool bp;
    buffer_pool_init(&bp); // Initialize the buffer pool.
    printf("Buffer pool initialized.\n");

    // Read the file in chunks and process each chunk
    size_t bytes_read;
    do {
        void *buffer = buffer_allocate(&bp);
        if (buffer == NULL) {
            fprintf(stderr, "Failed to allocate buffer.\n");
            break;
        }

        bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read > 0) {
            process_media_data(buffer, bytes_read);
        }

        buffer_deallocate(&bp, buffer);
    } while (bytes_read == BUFFER_SIZE);

    // Close the file
    fclose(file);
    printf("Finished processing file.\n");

    // Clean up the pool when it's no longer needed
    buffer_pool_destroy(&bp);
    printf("Buffer pool destroyed.\n");

    return 0;
}