#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define the structures
typedef struct{
    char roomName[50];
    char roomCode[3];
    char roomDesc[500];

}   Room;

// Removes whitespace from the beginning and end of the string
char *trim(char *str) {

    // Removes whitespace from the beginning
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') {
        str++;
    }

    char *end = str + strlen(str);

    // Removes whitespace from the end
    while (end > str && (*(end - 1) == ' ' || *(end - 1) == '\t' || *(end - 1) == '\n' || *(end - 1) == '\r')) {
        end--;
    }

    *end = '\0';

    return str;
}

int main(int argc, char *argv[]) {

    // Checks for the filename
    if (argc < 2) {
        printf("Missing filename.\n");
        return 1;
    }

    // Opens the file
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Create the room array
    int size = 4;
    int count = 0;

    Room *rooms = malloc(size * sizeof(Room));

    if (rooms == NULL) {
        printf("Error allocating memory.\n");
        fclose(fp);
        return 1;
    }

    char line[1500];
    Room room = {0};

    // Read each line of the file and checks when to NULL.
    while (fgets(line, sizeof(line), fp) != NULL) {

        char *value = strchr(line, ':');

        if (value == NULL) {
            continue;
        }

        value++;
        value = trim(value);

        // Save the room name
        if (strncmp(line, "Room Name:", 10) == 0) {
            strcpy(room.roomName, value);
        }

        // Save the room code
        else if (strncmp(line, "Room Code:", 10) == 0) {
            strcpy(room.roomCode, value);
        }

        // Save the room description
        else if (strncmp(line, "Room Description:", 17) == 0) {
            strcpy(room.roomDesc, value);

            if (count == size) {
                size = size * 2;

                Room *temp = realloc(rooms, size * sizeof(Room));

                if (temp == NULL) {
                    printf("Error expanding array.\n");
                    free(rooms);
                    fclose(fp);
                    return 1;
                }

                rooms = temp;
            }

            // Add the room to the array
            rooms[count] = room;
            count++;

            // Clear the room for the next one
            room = (Room){0};
        }
    }

    // Prints the room information
    for (int i = 0; i < count; i++) {
        printf("Room %s: %s\n", rooms[i].roomCode, rooms[i].roomName);
    }

    // Closes the file and frees memory
    fclose(fp);
    free(rooms);

    return 0;
}