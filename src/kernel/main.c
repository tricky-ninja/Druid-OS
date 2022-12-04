void _start() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'L';
    *(video_memory + 2) = 'O';
    *(video_memory + 4) = 'L';
    *(video_memory + 6) = ' ';
    *(video_memory + 8) = 'O';
    *(video_memory + 10) = 'S';
    *(video_memory + 12) = ' ';
}