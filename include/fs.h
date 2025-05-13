#ifndef FS_H
#define FS_H

typedef struct FileNode {
    char name[32];
    int is_directory;
    char content[128];
    struct FileNode* parent;
    struct FileNode* children[10];
    int child_count;
} FileNode;

//global root and current directory pointers
extern FileNode* root;
extern FileNode* current_dir;

//file operations
void fs_list(FileNode* dir);
void fs_mkdir(const char* name);
void fs_create(const char* name);
void fs_write(const char* name, const char* text);
const char* fs_read(const char* name);
void fs_cd(const char* name);
void fs_tree(FileNode* dir, int depth);
FileNode* find_node(FileNode* dir, const char* name);
void get_path(FileNode* node, char* buffer);
void count_nodes(FileNode* node, int* file_count, int* dir_count);

#endif
