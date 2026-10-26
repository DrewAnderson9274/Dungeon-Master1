#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define the structures
typedef struct{
    char roomName[50];
    char roomCode[3];
    char roomDesc[500];

}   Room;

void printRoom(Room *theRoom){
    printf("you entered the %s room \n", theRoom->roomName);
    printf("%s\n", theRoom->roomDesc);
}

int main(){
    Room testRoom;
    strcopy(testRoom.roomName, "Classroom");
    strcopy(testRoom.roomCode, "CR");
    strcopy(testRoom.roomDesc, "It's square!");

    printRoom(&testRoom); // give adress location of the room

    FILE *fp = ("dungeonRoomList_large.txt", "r");

    char roomName[50];
    fgets(roomName, sizeof(roomName), fp);
    fgets(roomName, sizeof(roomName), fp);
    fclose(fp);

   
    return 0;
}